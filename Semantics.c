#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include "CodeGen.h"
#include "Semantics.h"
#include "SymTab.h"
#include "IOMngr.h"

extern SymTab * table;
SymTab * functTable;//used for function creation
char * currentFunct;//the function that is currently being created

/* Semantics support routines */
extern void enterSize(int type, int mode){
	//this method should only be called immediately after declaring a variable.
	//This method assumes this is the case so that the current entry in the symbol 
	//table is the new variable. This method will then be able to enter a type for 
	//the variable. If the mode is 0, we will set the type to tyoe to indicate an 
	//int or boolean. This method assumes that 0 or 1 will be passed for type if 
	//the mode is 0. If the mode is not zero, then we will determine if the type 
	//is a valid array size, and then use mode to indicate an int or boolean array. 
	//The mips notation for the size will also be calculated and stored. Currently, 
	//there is no attribute for the entry, so we need to make one.
	struct Attribute * attr;
	if(getCurrentAttr(table) == NULL){//there is no current entry here
		attr = (struct Attribute *) malloc(sizeof(struct Attribute));
		attr->functType = -1;//indicate no function
	}else{
		attr = getCurrentAttr(table);//overwrite variable data, or combine with function data
	}
	if(mode == 0){//the variable is an int or boolean
		//we only need to hold "0" to tell mips to set one word space to the value 0
		attr->notation = (char *) malloc(2 * sizeof(char));//space for "0" and terminating char
		sprintf(attr->notation, "0");
		attr->type = type;
	}else if(type < 1){//input size for an array must be positive
		writeIndicator(getCurrentColumnNum());
		writeMessage("Array size must be positive.");
		attr->notation = (char *) malloc(2 * sizeof(char));//space for "0" and terminating char
		sprintf(attr->notation, "0");
		if(mode == 1){//int array
			attr->type = -1;
		}else{//is boolean array
			attr->type = -2;
		}
	}else{//size is greater than or equal to 1, so the size is valid for an array
		//the largest 32 bit number is 10 digits. We need the format "0:size"
		attr->notation = (char *) malloc(13 * sizeof(char));//10 digits plus 2 for "0:" plus a terminating char
		sprintf(attr->notation, "0:%d", type);
		if(mode == 1){//int array
			attr->type = -1;
		}else{//is boolean array
			attr->type = -2;
		}
	}
	setCurrentAttr(table, attr);
	return;
}

extern void makeFunction(int type){
	//Since we have the possibility of recursive functions, we will have a few
	//steps. We must generate a label for code to jump to when calling this 
	//function. It will be added to the front of the body and stored in the 
	//attribute to make it easier for code generation. This method will not enter 
	//code body for the function. This must be done after the code body is 
	//recognized. However, if the function is recursive, we will need the 
	//attribute to already have the label. If the type is 0, we will set the 
	//functType to 0 to indicate a void function. A type of 1 indicates an int 
	//function. Currently, there is no attribute for the entry, so we need to make 
	//one.
	struct Attribute * attr;
	if(getCurrentAttr(table) == NULL){//there is no current entry here
		attr = (struct Attribute *) malloc(sizeof(struct Attribute));
		attr->type = -3;//indicate no variable
		for(int i = 0; i < 127; i++){
			attr->argTypes[i] = -3;//start with no parameters
		}
	}else{
		attr = getCurrentAttr(table);//overwrite function data, or combine with variable data
		for(int i = 0; i < 127; i++){
			attr->argTypes[i] = -3;//start with no parameters
		}
	}
	char * label = GenLabel();
	struct InstrSeq * body;
	body = GenInstr(label, NULL, NULL, NULL, NULL);//the start of the function
	attr->funct = body;
	attr->functType = type;
	attr->functLabel = label;
	setCurrentAttr(table, attr);
	return;
}

extern void makeTable(struct varList * param, struct varList * local, char * name){
	//after recognizing all of the parameters and local variables for a function, we will 
	//create a symbol table to store the names and locations of the variables on the stack.
	//The order and type of parameters will be added to the function attribute. It is 
	//assumed that this method will be called before recognizing the body of the function. 
	//This means that the function entry is the current entry of the main symbol table.
	//Int array parameters will have type -1 and will contain the address of the array. Int 
	//parameters have type 0. Boolean array parameters will have type -2 and contain the 
	//address of the array. Booleans will have type 1.
	findName(table, name);
	struct Attribute * attr = getCurrentAttr(table);
	struct functAttr * fAttr;
	//parameters are put on the stack before a function call, so we will add them last
	struct varList * next;
	functTable = createSymTab(7);
	currentFunct = strdup(name);
	//size of all previous variables added. Used for calculating stack location
	//includes space for the return address
	int stack = 1;
	int params = 0;
	char addr[8];//the address of the variable on the stack
	while(local){
		next = local->Next;
		enterName(functTable, local->Id);
		fAttr = (struct functAttr *) malloc(sizeof(struct functAttr));
		//if this is user input, use isBoolean to determine the type of the array
		if(local->user){//this is a user input array size
			if(local->type < 1){
				writeIndicator(getCurrentColumnNum());
				writeMessage("Array size must be positive.");
				local->type = 1;//treat as an array of size 1 for the rest of the compilation
			}//else the array size is acceptable
			sprintf(addr, "%d($sp)", stack * 4);
			stack += local->type;//increment by array size
			fAttr->addr = strdup(addr);
			if(!local->isBoolean){//int array
				fAttr->type = -1;
			}else{//boolean array
				fAttr->type = -2;
			}
		}else{//this is an int or boolean
			sprintf(addr, "%d($sp)", stack * 4);
			stack += 1;//increment by one word
			fAttr->addr = strdup(addr);
			fAttr->type = local->type;//copy variable type
		}
		fAttr->isParam = 0;//this is not a parameter
		setCurrentAttr(functTable, fAttr);
		free(local);
		local = next;
	}
	//at this point, stack has the word space that local variables take up
	sprintf(addr, "%d", stack * 4);//local vars plus space for return address
	attr->localVars = stack;
	AppendSeq(attr->funct, GenInstr(NULL, "subu", "$sp", "$sp", addr));//space for return address and local variables
	AppendSeq(attr->funct, GenInstr(NULL, "sw", "$ra", "0($sp)", NULL));//in case of function call in body
	while(param){
		next = param->Next;
		enterName(functTable, param->Id);
		fAttr = (struct functAttr *) malloc(sizeof(struct functAttr));
		fAttr->type = param->type;//type is input in grammar, not set by user
		sprintf(addr, "%d($sp)", stack * 4);
		stack++;//we only add ints, booleans, or array addresses to the stack
		params++;
		if(params - 1 < 127){//functions can have 127 parameters at most
			attr->argTypes[params-1] = param->type;
		}else{
			writeIndicator(getCurrentColumnNum());
			writeMessage("Exceeded parameter cap of 127.");
		}
		fAttr->addr = strdup(addr);
		fAttr->isParam = 1;//this is a parameter
		setCurrentAttr(functTable, fAttr);
		free(param);
		param = next;
	}
}

extern void addBody(char * name, struct InstrSeq * body){
	//this method is called after the body of a declared function is
	//recognized. At this point, a label has been generated for the function, 
	//so we just need to add it to the front of the code provided and store 
	//that in the existing attribute. Since we are done processing function 
	//body code, we can destroy the functTable
	findName(table, name);//make sure we have the correct entry
	struct Attribute * attr = getCurrentAttr(table);//we are guaranteed a function entry
	AppendSeq(attr->funct, body);
	//returns will handle storing results, popping the return address and jumping back
	int hasMore = startIterator(functTable);
	while(hasMore){//free up string space associated with variable addresses
		struct functAttr * fAttr = getCurrentAttr(functTable);
		free(fAttr->addr);
		hasMore = nextEntry(functTable);
	}
	destroySymTab(functTable);
	functTable = NULL;
	free(currentFunct);
	currentFunct = NULL;
	return;
}

struct ExprRes * doIntLit(char * digits){
	struct ExprRes *res;
	res = (struct ExprRes *) malloc(sizeof(struct ExprRes));
	res->Reg = AvailTmpReg();
	res->Instrs = GenInstr(NULL, "li", TmpRegName(res->Reg), digits, NULL);
	return res;
}

struct ExprRes * doRval(char * name, struct ExprRes * index, int expectedType){
	//if the index is NULL, then we are loading an int or boolean into a register.
	//expectedType is the type of the varaible or array that we are requesting a value from.
	struct ExprRes * res;
	res = (struct ExprRes *) malloc(sizeof(struct ExprRes));
	res->Reg = AvailTmpReg();
	if(functTable){//we are in a function, so check local variables first
		if(!findName(functTable, name)){//variable is not local
			if(!findName(table, name) || ((struct Attribute *) getCurrentAttr(table))->type == -3){//variable does not exist
				writeIndicator(getCurrentColumnNum());
				writeMessage("Undeclared variable.");
				res->Instrs = NULL;
				if(index){
					ReleaseTmpReg(index->Reg);
					free(index);
				}
				return res;
			}else{//variable is global
				if(getType(name) != expectedType){
					writeIndicator(getCurrentColumnNum());
					writeMessage("Types do not match");
					res->Instrs = NULL;
					if(index){
						ReleaseTmpReg(index->Reg);
						free(index);
					}
					return res;
				}
				if(index){//index is not NULL, so this should be an array value
					if(((struct Attribute *) getCurrentAttr(table))->type >= 0){//an index was provided for a non-array
						writeIndicator(getCurrentColumnNum());
						writeMessage("Index provided for non-array.");
						res->Instrs = GenInstr(NULL, "lw", TmpRegName(res->Reg), name, NULL);
						ReleaseTmpReg(index->Reg);
						free(index);
						return res;
					}
					int reg;
					reg = AvailTmpReg();
					res->Instrs = index->Instrs;//add the code to generate the index
					AppendSeq(res->Instrs, GenInstr(NULL, "la", TmpRegName(reg), name, NULL));//get address of the start of the array
					//multiply the index by 4 to get the byte offset of the location to modify
					AppendSeq(res->Instrs, GenInstr(NULL, "sll", TmpRegName(index->Reg), TmpRegName(index->Reg), "2"));
					AppendSeq(res->Instrs, GenInstr(NULL, "add", TmpRegName(reg), TmpRegName(reg), TmpRegName(index->Reg)));//add offset to array address
					AppendSeq(res->Instrs, GenInstr(NULL, "lw", TmpRegName(res->Reg), RegOff(0,TmpRegName(reg)), NULL));
					ReleaseTmpReg(reg);
					ReleaseTmpReg(index->Reg);
					free(index);
				}else{//this should be an int or boolean.
					if(((struct Attribute *) getCurrentAttr(table))->type < 0){//array without index
						writeIndicator(getCurrentColumnNum());
						writeMessage("No index provided for array.");
					}
					//in the case of no array index, the first element is returned
					res->Instrs = GenInstr(NULL, "lw", TmpRegName(res->Reg), name, NULL);
				}
				return res;
			}
		}else{//variable is local
			if(getType(name) != expectedType){
				writeIndicator(getCurrentColumnNum());
				writeMessage("Types do not match");
				res->Instrs = NULL;
				if(index){
					ReleaseTmpReg(index->Reg);
					free(index);
				}
				return res;
			}
			struct functAttr * fAttr = (struct functAttr *) getCurrentAttr(functTable);
			if(index){//this should be an array
				if(fAttr->type >= 0){//an index was provided for a non-array
					writeIndicator(getCurrentColumnNum());
					writeMessage("Index provided for non-array.");
					res->Instrs = GenInstr(NULL, "lw", TmpRegName(res->Reg), fAttr->addr, NULL);
					ReleaseTmpReg(index->Reg);
					free(index);
					return res;
				}else{//the types match, so get the array element
					int reg;
					reg = AvailTmpReg();
					res->Instrs = index->Instrs;//add the code to generate the index
					if(fAttr->isParam){//what we find in the stack is an address pointing to the array
						//load the address that points to the start of the array
						res->Instrs = AppendSeq(res->Instrs, GenInstr(NULL, "lw", TmpRegName(reg), fAttr->addr, NULL));
						AppendSeq(res->Instrs, GenInstr(NULL, "la", TmpRegName(reg), RegOff(0,TmpRegName(reg)), NULL));
					}else{//what we find in the stack is the first element of the array
						//get the address of the start of the array
						res->Instrs = AppendSeq(res->Instrs, GenInstr(NULL, "la", TmpRegName(reg), fAttr->addr, NULL));
					}
					//at this point, we have the start address of the array
					AppendSeq(res->Instrs, GenInstr(NULL, "sll", TmpRegName(index->Reg), TmpRegName(index->Reg), "2"));
					AppendSeq(res->Instrs, GenInstr(NULL, "add", TmpRegName(reg), TmpRegName(reg), TmpRegName(index->Reg)));//add offset to array address
					AppendSeq(res->Instrs, GenInstr(NULL, "lw", TmpRegName(res->Reg), RegOff(0,TmpRegName(reg)), NULL));
					ReleaseTmpReg(reg);
					ReleaseTmpReg(index->Reg);
					free(index);
					return res;
				}
			}else{//this should be an int or boolean
				if(fAttr->type < 0){//array without index
					writeIndicator(getCurrentColumnNum());
					writeMessage("No index provided for array.");
					int reg;
					reg = AvailTmpReg();
					res->Instrs = GenInstr(NULL, "lw", TmpRegName(res->Reg), fAttr->addr, NULL);
					if(fAttr->isParam){//we have loaded the address of an array
						if(fAttr->isParam){//what we find in the stack is an address pointing to the array
						//load the address that points to the start of the array
						res->Instrs = AppendSeq(res->Instrs, GenInstr(NULL, "lw", TmpRegName(reg), fAttr->addr, NULL));
						AppendSeq(res->Instrs, GenInstr(NULL, "la", TmpRegName(reg), RegOff(0,TmpRegName(reg)), NULL));
					}else{//what we find in the stack is the first element of the array
						//get the address of the start of the array
						res->Instrs = AppendSeq(res->Instrs, GenInstr(NULL, "la", TmpRegName(reg), fAttr->addr, NULL));
					}
					AppendSeq(res->Instrs, GenInstr(NULL, "lw", TmpRegName(res->Reg), RegOff(0,TmpRegName(reg)), NULL));
					ReleaseTmpReg(reg);
					return res;
					}
				}//else this is an int or boolean
				res->Instrs = GenInstr(NULL, "lw", TmpRegName(res->Reg), fAttr->addr, NULL);
				return res;
			}
		}
	}else{//we are not in a function
		if(!findName(table, name) || ((struct Attribute *) getCurrentAttr(table))->type == -3){//variable does not exist
			writeIndicator(getCurrentColumnNum());
			writeMessage("Undeclared variable.");
			res->Instrs = NULL;
			if(index){
				ReleaseTmpReg(index->Reg);
				free(index);
			}
			return res;
		}else{//variable is global
			if(getType(name) != expectedType){
				writeIndicator(getCurrentColumnNum());
				writeMessage("Types do not match");
				res->Instrs = NULL;
				if(index){
					ReleaseTmpReg(index->Reg);
					free(index);
				}
				return res;
			}
			if(index){//index is not NULL, so this should be an array value
				if(((struct Attribute *) getCurrentAttr(table))->type >= 0){//the requested array is actually an int
					writeIndicator(getCurrentColumnNum());
					writeMessage("Index provided for non-array.");
					res->Instrs = GenInstr(NULL, "lw", TmpRegName(res->Reg), name, NULL);
					ReleaseTmpReg(index->Reg);
					free(index);
					return res;
				}
				int reg;
				reg = AvailTmpReg();
				res->Instrs = index->Instrs;//add the code to generate the index
				AppendSeq(res->Instrs, GenInstr(NULL, "la", TmpRegName(reg), name, NULL));//get address of the start of the array
				//multiply the index by 4 to get the byte offset of the location to modify
				AppendSeq(res->Instrs, GenInstr(NULL, "sll", TmpRegName(index->Reg), TmpRegName(index->Reg), "2"));
				AppendSeq(res->Instrs, GenInstr(NULL, "add", TmpRegName(reg), TmpRegName(reg), TmpRegName(index->Reg)));//add offset to array address
				AppendSeq(res->Instrs, GenInstr(NULL, "lw", TmpRegName(res->Reg), RegOff(0,TmpRegName(reg)), NULL));
				ReleaseTmpReg(reg);
				ReleaseTmpReg(index->Reg);
				free(index);
			}else{//this should be an int or boolean
				if(((struct Attribute *) getCurrentAttr(table))->type < 0){//int array without index
					writeIndicator(getCurrentColumnNum());
					writeMessage("No index provided for array.");
				}
				//in the case of no array index, the first element is returned
				res->Instrs = GenInstr(NULL, "lw", TmpRegName(res->Reg), name, NULL);
			}
			return res;
		}
	}
}

extern struct BExprResList * AppendExpr(struct BExprRes * BExpr, struct BExprResList * list){
	if(!BExpr){
		return list;
	}
	struct BExprResList * start;
	start = (struct BExprResList *) malloc(sizeof(struct BExprResList));//the tail of the list we are returning
	start->BExpr = BExpr;
	start->Next = list;//the grammar adds items in reverse, so the most recent added should be earlier than everything in the list
	return start;
}

extern struct IdentList * AppendRead(char * Id, struct ExprRes * index, struct IdentList * list){
	//id can never be a NULL char *
	struct IdentList * start;
	start = (struct IdentList *) malloc(sizeof(struct IdentList));//the tail of the list we are returning
	start->Id = Id;
	start->index = index;
	start->Next = list;//the grammar adds items in reverse, so the most recent added should be earlier than everything in the list
	return start;
}

extern struct varList * AppendVar(char * Id, int type, struct varList * list, int user, int isBoolean){
	///this method adds to a collection of local variables or function parameters. Since these are 
	//declarations of variables, there is no need to check the symbol table. If user = 1, then the 
	//size is from user input.
	struct varList * start;
	start = (struct varList *) malloc(sizeof(struct varList));//the tail of the list we are returning
	start->Id = Id;
	start->type = type;
	start->user = user;
	start->isBoolean = isBoolean;
	start->Next = list;//the grammar adds items in reverse, so the most recent added should be earlier than everything in the list
	return start;
}

struct ParamList * newPList(struct ExprRes * value, struct BExprRes * boolean, int type){
	struct ParamList * entry = (struct ParamList *) malloc(sizeof(struct ParamList));
	entry->value = value;
	entry->boolean = boolean;
	entry->type = type;
	entry->Next = NULL;
	return entry;
}

struct ExprRes * getArg(char * Id){
	//generate an ExprRes that contains the value of a variable, or 
	//if the variable is an array, the address of the array
	struct ExprRes * res;
	char addr [8];
	res = (struct ExprRes *) malloc(sizeof(struct ExprRes));
	res->Reg = AvailTmpReg();
	if(functTable){//we are in a function, so check local variables first
		if(!findName(functTable, Id)){//variable is not local
			if(!findName(table, Id) || ((struct Attribute *) getCurrentAttr(table))->type == -3){//variable does not exist
				writeIndicator(getCurrentColumnNum());
				writeMessage("Uneclared variable.");
				res->Instrs = NULL;
			}else{//variable is global
				struct Attribute * attr = (struct Attribute *) getCurrentAttr(table);
				if(attr->type >= 0){//this is an int or boolean, so get its value
					res->Instrs = GenInstr(NULL, "lw", TmpRegName(res->Reg), Id, NULL);
				}else{//this is an array, so get its starting address
					res->Instrs = GenInstr(NULL, "la", TmpRegName(res->Reg), Id, NULL);
				}
			}
		}else{//variable is local
			//get the stack address of the variable
			struct functAttr * attr = (struct functAttr *) getCurrentAttr(functTable);
			sprintf(addr, "%s", attr->addr);
			if(attr->type >= 0){//this is an int or boolean, so get its value
				res->Instrs = GenInstr(NULL, "lw", TmpRegName(res->Reg), addr, NULL);
			}else{//this is an array, so get its starting address
				if(attr->isParam){//the array we want to pass was given to us as an address
					//get the address passed to the calling method
					res->Instrs = GenInstr(NULL, "lw", TmpRegName(res->Reg), addr, NULL);
				}else{//the array we want to pass was declared locally
					//load the address created in the calling method
					res->Instrs = GenInstr(NULL, "la", TmpRegName(res->Reg), addr, NULL);
				}
			}
		}
	}else{//we are not in a function
		if(!findName(table, Id) || ((struct Attribute *) getCurrentAttr(table))->type == -3){//variable does not exist
			writeIndicator(getCurrentColumnNum());
			writeMessage("Undeclared variable.");
			res->Instrs = NULL;
		}else{//variable is global
			struct Attribute * attr = (struct Attribute *) getCurrentAttr(table);
			if(attr->type >= 0){//this is an int or boolean, so get its value
				res->Instrs = GenInstr(NULL, "lw", TmpRegName(res->Reg), Id, NULL);
			}else{//this is an array, so get its starting address
				res->Instrs = GenInstr(NULL, "la", TmpRegName(res->Reg), Id, NULL);
			}
		}
	}
	return res;
}

int getType(char * Id){
	//get the type of the variable stored
	int type;
	if(functTable){//we are in a function, so check local variables first
		if(!findName(functTable, Id)){//variable is not local
			if(!findName(table, Id) || ((struct Attribute *) getCurrentAttr(table))->type == -3){//variable does not exist
				//we will have already output an error in getArg
				type = -3;
			}else{//variable is global
				//determine if varaible is an int or array
				struct Attribute * attr = (struct Attribute *) getCurrentAttr(table);
				type = attr->type;//types for local and global variables are the same
			}
		}else{//variable is local
			struct functAttr * attr = (struct functAttr *) getCurrentAttr(functTable);
			type = attr->type;//types for local and global variables are the same
		}
	}else{//we are not in a function
		if(!findName(table, Id) || ((struct Attribute *) getCurrentAttr(table))->type == -3){//variable does not exist
			//we will have already output an error in getArg
			type = -3;
		}else{//variable is global
			//load the address of the int or start of the array
			struct Attribute * attr = (struct Attribute *) getCurrentAttr(table);
			type = attr->type;//types for local and global variables are the same
		}
	}
	return type;
}

extern struct InstrSeq * getVoidFunction(char * name, struct ParamList * params){
	//we must save registers, call the function, and then restore the registers.
	struct InstrSeq * code;
	struct Attribute * attr;
	code = NULL;
	if(!findName(table, name) || ((struct Attribute *) getCurrentAttr(table))->functType == -1){
		writeIndicator(getCurrentColumnNum());
		writeMessage("Undeclared function.");
		return code;//we won't append any code for the statement sequence
	}
	attr = (struct Attribute *) getCurrentAttr(table);
	//if the function we get is an int or boolean function, $v0's value will be ignored
	//we have a function. Now we must check to see if we have the correct parameters.
	int index = 0;//index of function parameter type array
	struct ParamList * current;
	struct ParamList * nextEntry;
	current = params;
	while(1){
		if(current){//there is a parameter
			nextEntry = current->Next;
			if(!current->value){//boolean needs to be converted
				current->value = getBooleanVal(current->boolean);
				//the BExprRes and its label will be freed in getBooleanVal()
			}
			ReleaseTmpReg(current->value->Reg);//we need to free all registers before calling SaveSeq
			if(index >= 127){//exceeded arg limit
				writeIndicator(getCurrentColumnNum());
				writeMessage("Exceeded argument limit of 127.");
			}else if(current->type != attr->argTypes[index]){
				writeIndicator(getCurrentColumnNum());
				writeMessage("Incorrect parameter type.");
			}else{
				//the argument is of the correct type
			}
			code = AppendSeq(code, current->value->Instrs);//add code to create parameter
			index++;
			current = nextEntry;
		}else{//there is not a parameter
			if(index < 127 && attr->argTypes[index] == -3 || index == 127){//all parameters were correct
				break;
			}else if(index > 127){//too many arguments. This error was already output
				break;
			}
			else{//too few arguments
				writeIndicator(getCurrentColumnNum());
				writeMessage("Too few arguments.");
				break;
			}
		}
	}
	code = AppendSeq(code, SaveSeq());//save currently used registers on the stack
	//we will add all arguments to the stack regardless if they were valid
	//add space on the stack for all of the provided parameters
	int paramSpace = index * 4;
	if(paramSpace > 0){
		code = AppendSeq(code, GenInstr(NULL, "subu", "$sp", "$sp", Imm(paramSpace)));
	}
	current = params;
	index = 0;//use for index on stack
	char addr[12];
	while(current){
		nextEntry = current->Next;
		sprintf(addr, "%d($sp)", index * 4);//create address
		code = AppendSeq(code, GenInstr(NULL, "sw", TmpRegName(current->value->Reg), addr, NULL));//add parameter to stack
		index++;
		ReleaseTmpReg(current->value->Reg);
		free(current->value);//the register was already freed
		free(current);
		current = nextEntry;
	}//at this point, all provided parameters are on the stack
	//in case there is nothing to save
	code = AppendSeq(code, GenInstr(NULL, "jal", (((struct Attribute *) getCurrentAttr(table))->functLabel), NULL, NULL));//jump to function
	if(paramSpace > 0){
		code = AppendSeq(code, GenInstr(NULL, "addu", "$sp", "$sp", Imm(paramSpace)));//clear parameters from stack
	}
	code = AppendSeq(code, RestoreSeq());//restore registers
	return code;
}

extern struct ExprRes * getIntFunction(char * name, struct ParamList * params){
	//we must save registers, call the function, and then restore the registers.
	//Here, the return value of the function is saved as well
	struct ExprRes * code;
	struct Attribute * attr;
	code = (struct ExprRes *) malloc(sizeof(struct ExprRes));
	code->Instrs = NULL;
	if(!findName(table, name) || ((struct Attribute *) getCurrentAttr(table))->functType == -1){
		writeIndicator(getCurrentColumnNum());
		writeMessage("Undeclared function.");
		code->Reg = AvailTmpReg();
		//no code will be added, but the register must be freed
		return code;
	}
	attr = (struct Attribute *) getCurrentAttr(table);
	if(attr->functType == 0){
		writeIndicator(getCurrentColumnNum());
		writeMessage("Void value not ignored as it ought to be.");
		return code;//we won't append any code for the statement sequence
	}
	//we have a function. Now we must check to see if we have the correct parameters.
	int index = 0;//index of function parameter type array
	struct ParamList * current;
	struct ParamList * nextEntry;
	current = params;
	while(1){
		if(current){//there is a parameter
			nextEntry = current->Next;
			if(!current->value){//boolean needs to be converted
				current->value = getBooleanVal(current->boolean);
				//the BExprRes and its label will be freed in getBooleanVal()
			}
			ReleaseTmpReg(current->value->Reg);//we need to free all registers before calling SaveSeq
			if(index >= 127){//exceeded arg limit
				writeIndicator(getCurrentColumnNum());
				writeMessage("Exceeded argument limit of 127.");
			}else if(current->type != attr->argTypes[index]){
				writeIndicator(getCurrentColumnNum());
				writeMessage("Incorrect parameter type.");
			}else{
				//the argument is of the correct type
			}
			code->Instrs = AppendSeq(code->Instrs, current->value->Instrs);//add code to create parameter
			index ++;
			current = nextEntry;
		}else{//there is not a parameter
			if(index < 127 && attr->argTypes[index] == -3 || index == 127){//all parameters were correct
				break;
			}else if(index > 127){//too many arguments. This error was already output
				break;
			}
			else{//too few arguments
				writeIndicator(getCurrentColumnNum());
				writeMessage("Too few arguments.");
				break;
			}
		}
	}
	code->Instrs = AppendSeq(code->Instrs, SaveSeq());//save currently used registers on the stack
	//we will add all arguments to the stack regardless if they were valid
	//add space on the stack for all of the provided parameters
	int paramSpace = index * 4;
	if(paramSpace > 0){
		code->Instrs = AppendSeq(code->Instrs, GenInstr(NULL, "subu", "$sp", "$sp", Imm(paramSpace)));
	}
	current = params;
	index = 0;//use for index on stack
	char addr[12];
	while(current){
		nextEntry = current->Next;
		sprintf(addr, "%d($sp)", index * 4);//create address
		code->Instrs = AppendSeq(code->Instrs, GenInstr(NULL, "sw", TmpRegName(current->value->Reg), addr, NULL));//add parameter to stack
		index++;
		ReleaseTmpReg(current->value->Reg);
		free(current->value);//the register was already freed
		free(current);
		current = nextEntry;
	}//at this point, all provided parameters are on the stack
	//in case there is nothing to save
	code->Instrs = AppendSeq(code->Instrs, GenInstr(NULL, "jal", ((struct Attribute *) getCurrentAttr(table))->functLabel, NULL, NULL));//jump to function
	if(paramSpace > 0){
		code->Instrs = AppendSeq(code->Instrs, GenInstr(NULL, "addu", "$sp", "$sp", Imm(paramSpace)));//clear parameters from stack
	}
	//$v0 will have the return value
	AppendSeq(code->Instrs, RestoreSeq());//restore registers
	code->Reg = AvailTmpReg();
	AppendSeq(code->Instrs, GenInstr(NULL, "addi", TmpRegName(code->Reg), "$v0", "0"));//get the return value
	return code;
}

extern struct InstrSeq * doVoidReturn(){
	//we will need to pop any local variables along with the return 
	//address before we can jump back.
	struct InstrSeq * code;
	code = NULL;
	if(currentFunct == NULL || !findName(table, currentFunct) || ((struct Attribute *) getCurrentAttr(table))->functType == -1){
		writeIndicator(getCurrentColumnNum());
		writeMessage("Return called outside of a function.");
		return code;
	}
	//get the size of the stack added by the function call
	int vars = ((struct Attribute *) getCurrentAttr(table))->localVars;
	vars *= 4;//convert to word size
	char addr[8];
	sprintf(addr, "%d", vars);
	code = GenInstr(NULL, "lw", "$ra", "($sp)", NULL);//peek
	AppendSeq(code, GenInstr(NULL, "addi", "$sp", "$sp", addr));//pop
	AppendSeq(code, GenInstr(NULL, "jr", "$ra", NULL, NULL));
	return code;
}

extern struct InstrSeq * doIntReturn(struct ExprRes * Expr){
	//we must push the return value and pop the return address from the 
	//stack. This will result in the return value being at -4($sp). 
	//Finally, we must free the expression register and struct.
	struct InstrSeq * code;
	code = NULL;
	if(currentFunct == NULL || !findName(table, currentFunct) || ((struct Attribute *) getCurrentAttr(table))->functType == -1){
		writeIndicator(getCurrentColumnNum());
		writeMessage("Return called outside of a function.");
		ReleaseTmpReg(Expr->Reg);
		free(Expr);
		return code;
	}
	//get the size of the stack added by the function call
	int vars = ((struct Attribute *) getCurrentAttr(table))->localVars;
	vars *= 4;//convert to word size
	char addr[8];
	sprintf(addr, "%d", vars);
	code = Expr->Instrs;
	code = AppendSeq(code, GenInstr(NULL, "addi", "$v0", TmpRegName(Expr->Reg), "0"));//store result in $v0
	AppendSeq(code, GenInstr(NULL, "lw", "$ra", "($sp)", NULL));//peek
	AppendSeq(code, GenInstr(NULL, "addi", "$sp", "$sp", addr));//pop
	AppendSeq(code, GenInstr(NULL, "jr", "$ra", NULL, NULL));
	ReleaseTmpReg(Expr->Reg);
	free(Expr);
	return code;
}

extern struct InstrSeq * doBoolReturn(struct BExprRes * bRes){
	//we must push the return value and pop the return address from the 
	//stack. This will result in the return value being at -4($sp). 
	//Finally, we must free the expression register and struct.
	struct InstrSeq * code;
	code = NULL;
	if(currentFunct == NULL || !findName(table, currentFunct) || ((struct Attribute *) getCurrentAttr(table))->functType == -1){
		writeIndicator(getCurrentColumnNum());
		writeMessage("Return called outside of a function.");
		if(bRes->Expr){
			ReleaseTmpReg(bRes->Expr->Reg);
			free(bRes->Expr);
		}
		free(bRes->Label);
		free(bRes);
		return code;
	}
	//get the size of the stack added by the function call
	int vars = ((struct Attribute *) getCurrentAttr(table))->localVars;
	vars *= 4;//convert to word size
	char addr[8];
	sprintf(addr, "%d", vars);
	if(bRes->Expr && bRes->Expr->isBoolean){//this is a boolean from memory
		//because this is now being used as a boolean, add a beqz to create a boolean situation
		bRes->Instrs = AppendSeq(bRes->Instrs, GenInstr(NULL, "beq", 
		TmpRegName(bRes->Expr->Reg), "$zero", bRes->Label));
		ReleaseTmpReg(bRes->Expr->Reg);
		free(bRes->Expr);
		bRes->Expr = NULL;//this is a boolean
	}
	code = AppendSeq(code, GenInstr(NULL, "li", "$v0", "0", NULL));
	AppendSeq(code, finishIf(doIf(bRes, GenInstr(NULL, "li", "$v0", "1", NULL))));
	//bRes and its label are freed in finishIf
	//the boolean result is in $v0
	AppendSeq(code, GenInstr(NULL, "lw", "$ra", "($sp)", NULL));//peek
	AppendSeq(code, GenInstr(NULL, "addi", "$sp", "$sp", addr));//pop
	AppendSeq(code, GenInstr(NULL, "jr", "$ra", NULL, NULL));
	return code;
}

struct ExprRes * doOp(struct ExprRes * Res1, struct ExprRes * Res2, char * op){
	int reg;
	reg = AvailTmpReg();
	Res1->Instrs = AppendSeq(Res1->Instrs, Res2->Instrs);
	Res1->Instrs = AppendSeq(Res1->Instrs, GenInstr(NULL, op, TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));
	ReleaseTmpReg(Res1->Reg);
	ReleaseTmpReg(Res2->Reg);
	Res1->Reg = reg;
	free(Res2);
	return Res1;
}

struct ExprRes * doPow(struct ExprRes * Res1, struct ExprRes * Res2){
	int reg;
	reg = AvailTmpReg();
	char * Label1 = GenLabel();
	char * Label2 = GenLabel();
	Res1->Instrs = AppendSeq(Res1->Instrs, Res2->Instrs);
	Res1->Instrs = AppendSeq(Res1->Instrs, GenInstr(NULL, "li", TmpRegName(reg), "1", NULL));//any number to the power of 0 is 1
	AppendSeq(Res1->Instrs, GenInstr(Label1, NULL, NULL, NULL, NULL));//jump here for comparison
	AppendSeq(Res1->Instrs, GenInstr(NULL, "beq", TmpRegName(Res2->Reg), "$zero", Label2));
	//multiply base by current result
	AppendSeq(Res1->Instrs, GenInstr(NULL, "mul", TmpRegName(reg), TmpRegName(reg), TmpRegName(Res1->Reg)));
	AppendSeq(Res1->Instrs, GenInstr(NULL, "addi", TmpRegName(Res2->Reg), TmpRegName(Res2->Reg), "-1"));//decrement counter/exponent
	AppendSeq(Res1->Instrs, GenInstr(NULL, "j", Label1, NULL, NULL));
	AppendSeq(Res1->Instrs, GenInstr(Label2, NULL, NULL, NULL, NULL));//exponentiation is finished
	ReleaseTmpReg(Res1->Reg);
	ReleaseTmpReg(Res2->Reg);
	Res1->Reg = reg;
	free(Res2);
	return Res1;
}

struct ExprRes * doNeg(struct ExprRes * Res1){
	AppendSeq(Res1->Instrs, GenInstr(NULL, "sub", TmpRegName(Res1->Reg), "$zero", TmpRegName(Res1->Reg)));
	return Res1;
}

struct ExprRes * doDivOrMod(struct ExprRes * Res1, struct ExprRes * Res2, char * op){
	int reg;
	reg = AvailTmpReg();
	Res1->Instrs = AppendSeq(Res1->Instrs, Res2->Instrs);
	Res1->Instrs = AppendSeq(Res1->Instrs, GenInstr(NULL, "div", TmpRegName(Res1->Reg), TmpRegName(Res2->Reg), NULL));
	if(!strcmp(op, "divide")){//the requested operation is divide
		AppendSeq(Res1->Instrs, GenInstr(NULL, "MFLO", TmpRegName(reg), NULL, NULL));
	}else{//the requested operation should be mod
		AppendSeq(Res1->Instrs, GenInstr(NULL, "MFHI", TmpRegName(reg), NULL, NULL));
	}
	ReleaseTmpReg(Res1->Reg);
	ReleaseTmpReg(Res2->Reg);
	Res1->Reg = reg;
	free(Res2);
	return Res1;
}

struct InstrSeq * doRead(struct IdentList * list) {
	//this method assumes that any undeclared variables were flagged when the IdentList was made
	struct IdentList * current;
	struct IdentList * nextEntry;
	struct InstrSeq * code;
	code = NULL;
	if(!list){//there is no first expression
		writeIndicator(getCurrentColumnNum());
		writeMessage("Nothing to read.");
		return code;
	}
	current = list;//start at the head of the list
	while(current){
		nextEntry = current->Next;
		struct ExprRes * Expr = (struct ExprRes *) malloc(sizeof(struct ExprRes));
		Expr->Instrs = GenInstr(NULL, "li", "$v0", "5", NULL);//set mode to read integer
		AppendSeq(Expr->Instrs,GenInstr(NULL, "syscall", NULL, NULL, NULL));//$v0 contains integer read
		Expr->Reg = getRegV0();//result is in register $v0
		code = AppendSeq(code, doAssign(current->Id, Expr, current->index, getType(current->Id)));
		//the code to do the read will be the start of the result returned by doAssign().
		//When doAssign() calls ReleaseTmpReg on Expr, the $v0 will be ignored. code has
		//the instructions to assign a read value to an Id with optional index. Any
		//indexing or variable lookup errors are handled by doAssign(). If there was an
		//index provided, the register and struct will have been freed by doAssign().
		//Expr will also be freed along with its register by doAssign().
		free(current->Id);
		free(current);
		current = nextEntry;
	}
	return code;
}

struct InstrSeq * doPrint(struct BExprResList * list) {
	struct BExprResList * current;
	struct BExprResList * nextEntry;
	struct InstrSeq * code;
	code = NULL;
	if(!list){//there is no first expression
		writeIndicator(getCurrentColumnNum());
		writeMessage("No arguments.");
		return code;
	}
	current = list;//start at the head of the list
	nextEntry = current->Next;
	if(current->BExpr->Expr && !(current->BExpr->Expr->isBoolean)){//this is an int
		code = current->BExpr->Expr->Instrs;
		code = AppendSeq(code,GenInstr(NULL, "li", "$v0", "1", NULL));
		AppendSeq(code,GenInstr(NULL,"move","$a0",TmpRegName(current->BExpr->Expr->Reg),NULL));
		ReleaseTmpReg(current->BExpr->Expr->Reg);
		free(current->BExpr->Expr);
		free(current->BExpr->Label);
		free(current->BExpr);
	}else{//this is a boolean
		if(current->BExpr->Expr && current->BExpr->Expr->isBoolean){//this is a boolean from memory
			//because this is now being used as a boolean, add a beqz to create a boolean situation
			current->BExpr->Instrs = AppendSeq(current->BExpr->Instrs, GenInstr(NULL, "beq", 
			TmpRegName(current->BExpr->Expr->Reg), "$zero", current->BExpr->Label));
			ReleaseTmpReg(current->BExpr->Expr->Reg);
			free(current->BExpr->Expr);
			current->BExpr->Expr = NULL;//this is a boolean
		}
		code = AppendSeq(code, GenInstr(NULL, "la", "$a0", "_false", NULL));
		AppendSeq(code, finishIf(doIf(current->BExpr, GenInstr(NULL, "la", "$a0", "_true", NULL))));
		//BExpr and its label are freed in finishIf
		AppendSeq(code, GenInstr(NULL, "li", "$v0", "4", NULL));
	}
	AppendSeq(code, GenInstr(NULL,"syscall",NULL,NULL,NULL));
	free(current);
	current = nextEntry;
	while(current){
		nextEntry = current->Next;
		AppendSeq(code,GenInstr(NULL, "li", "$v0", "4",NULL));
		AppendSeq(code,GenInstr(NULL, "la", "$a0", "_list", NULL));//print out a comma and space before the next expression
		AppendSeq(code,GenInstr(NULL, "syscall", NULL, NULL, NULL));
		if(current->BExpr->Expr && !current->BExpr->Expr->isBoolean){//Expr is not NULL, so this is an int
			AppendSeq(code, current->BExpr->Expr->Instrs);
			AppendSeq(code,GenInstr(NULL, "li", "$v0", "1", NULL));
			AppendSeq(code,GenInstr(NULL,"move","$a0",TmpRegName(current->BExpr->Expr->Reg),NULL));
			ReleaseTmpReg(current->BExpr->Expr->Reg);
			free(current->BExpr->Expr);
		}else{//this is a boolean
			if(current->BExpr->Expr && current->BExpr->Expr->isBoolean){//this is a boolean from memory
			//because this is now being used as a boolean, add a beqz to create a boolean situation
			current->BExpr->Instrs = AppendSeq(current->BExpr->Instrs, GenInstr(NULL, "beq", 
			TmpRegName(current->BExpr->Expr->Reg), "$zero", current->BExpr->Label));
			ReleaseTmpReg(current->BExpr->Expr->Reg);
			free(current->BExpr->Expr);
			current->BExpr->Expr = NULL;//this is a boolean
			}
			code = AppendSeq(code, GenInstr(NULL, "la", "$a0", "_false", NULL));
			AppendSeq(code, finishIf(doIf(current->BExpr, GenInstr(NULL, "la", "$a0", "_true", NULL))));
			//BExpr and its label are freed in finishIf
			AppendSeq(code, GenInstr(NULL, "li", "$v0", "4", NULL));
		}
		AppendSeq(code,GenInstr(NULL, "syscall", NULL, NULL, NULL));
		free(current->BExpr->Label);
		free(current->BExpr);
		free(current);
		current = nextEntry;
	}
	return code;
}

struct InstrSeq * doPrintLine() { 
	struct InstrSeq * code;
	code = NULL;
	code = AppendSeq(code, GenInstr(NULL, "li", "$v0", "4", NULL));
    AppendSeq(code, GenInstr(NULL, "la", "$a0", "_nl", NULL));
	AppendSeq(code, GenInstr(NULL, "syscall", NULL, NULL, NULL));
	return code;
}

struct InstrSeq * doPrintSpaces(struct ExprRes * Expr) { 
	char * Label1 = GenLabel();//this marks where the for loop comparison is done
	char * Label2 = GenLabel();//this marks where the for loop body starts
	struct InstrSeq * code;
    code = Expr->Instrs;
	//since we will only be printing spaces, we can set these values once and do only a syscall in the body
	code = AppendSeq(code,GenInstr(NULL, "li", "$v0", "4", NULL));
    AppendSeq(code,GenInstr(NULL, "la", "$a0", "_sp", NULL));
	AppendSeq(code,GenInstr(NULL, "j", Label1, NULL, NULL));//jump to the comparison
	AppendSeq(code,GenInstr(Label2, "syscall", NULL, NULL, NULL));//body of for loop
	AppendSeq(code,GenInstr(NULL, "addi", TmpRegName(Expr->Reg), TmpRegName(Expr->Reg), "-1"));//decrement counter
	AppendSeq(code,GenInstr(Label1, "bne", TmpRegName(Expr->Reg), "$zero", Label2));//if the value is 0, repeat the body
	ReleaseTmpReg(Expr->Reg);
	free(Expr);
	return code;
}

struct InstrSeq * doAssign(char *name, struct ExprRes * Expr, struct ExprRes * index, int expectedType) {
	//assign a value to a variable in the symbol table. If the variable is an array, 
	//then the index will be used to find an element in the array to assign. If the 
	//varaible is an int, then the grammar will pass a NULL index. A variable is 
	//determined to be an array if its associated size is not zero.
	struct InstrSeq * code;
	code = NULL;
	if(functTable){//we are in a function, so check local variables first
		if(!findName(functTable, name)){//variable is not local
			if(!findName(table, name) || ((struct Attribute *) getCurrentAttr(table))->type == -3){//variable does not exist
				writeIndicator(getCurrentColumnNum());
				writeMessage("Undeclared variable.");
				if(index){
					ReleaseTmpReg(index->Reg);
					free(index);
				}
				ReleaseTmpReg(Expr->Reg);
				free(Expr);
				return code;
			}else{//variable is global
				if(getType(name) != expectedType){
					writeIndicator(getCurrentColumnNum());
					writeMessage("Types do not match");
					code = NULL;
					if(index){
						ReleaseTmpReg(index->Reg);
						free(index);
					}
					return code;
				}
				if(index){//index is not NULL, so this should be an array value
					if(((struct Attribute *) getCurrentAttr(table))->type >= 0){//an index was provided for a non-array
						writeIndicator(getCurrentColumnNum());
						writeMessage("Index provided for non-array.");
						code = Expr->Instrs;
						code = AppendSeq(code, GenInstr(NULL, "sw", TmpRegName(Expr->Reg), name, NULL));
						ReleaseTmpReg(index->Reg);
						free(index);
						ReleaseTmpReg(Expr->Reg);
						free(Expr);
						return code;
					}
					int reg;
					reg = AvailTmpReg();
					code = AppendSeq(code, index->Instrs);//add the code to generate the index
					code = AppendSeq(code, Expr->Instrs);
					AppendSeq(code, GenInstr(NULL, "la", TmpRegName(reg), name, NULL));//get address of the start of the array
					//multiply the index by 4 to get the byte offset of the location to modify
					AppendSeq(code, GenInstr(NULL, "sll", TmpRegName(index->Reg), TmpRegName(index->Reg), "2"));
					AppendSeq(code, GenInstr(NULL, "add", TmpRegName(reg), TmpRegName(reg), TmpRegName(index->Reg)));//add offset to array address
					AppendSeq(code, GenInstr(NULL, "sw", TmpRegName(Expr->Reg), RegOff(0,TmpRegName(reg)), NULL));
					ReleaseTmpReg(reg);
					ReleaseTmpReg(index->Reg);
					free(index);
					ReleaseTmpReg(Expr->Reg);
					free(Expr);
					return code;
			}else{//this should be an int
				if(((struct Attribute *) getCurrentAttr(table))->type < 0){//array without index
					writeIndicator(getCurrentColumnNum());
					writeMessage("No index provided for array.");
				}
				//in the case of no array index, the first element is returned
				code = Expr->Instrs;
				code = AppendSeq(code, GenInstr(NULL, "sw", TmpRegName(Expr->Reg), name, NULL));
				ReleaseTmpReg(Expr->Reg);
				free(Expr);
				return code;
				}
			}
		}else{//variable is local
			if(getType(name) != expectedType){
				writeIndicator(getCurrentColumnNum());
				writeMessage("Types do not match");
				code = NULL;
				if(index){
					ReleaseTmpReg(index->Reg);
					free(index);
				}
				return code;
			}
			struct functAttr * fAttr = (struct functAttr *) getCurrentAttr(functTable);
			if(index){//this should be an array
				if(fAttr->type >= 0){//an index was provided for a non-array
					writeIndicator(getCurrentColumnNum());
					writeMessage("Index provided for non-array.");
					code = Expr->Instrs;
					code = AppendSeq(code, GenInstr(NULL, "sw", TmpRegName(Expr->Reg), fAttr->addr, NULL));
					ReleaseTmpReg(index->Reg);
					free(index);
					ReleaseTmpReg(Expr->Reg);
					free(Expr);
					return code;
				}else{//the types match, so get the array element
					int reg;
					reg = AvailTmpReg();
					code = AppendSeq(code, index->Instrs);//add the code to generate the index
					code = AppendSeq(code, Expr->Instrs);
					if(fAttr->isParam){//what we find in the stack is an address pointing to the array
						//load the address that points to the start of the array
						code = AppendSeq(code, GenInstr(NULL, "lw", TmpRegName(reg), fAttr->addr, NULL));
						AppendSeq(code, GenInstr(NULL, "la", TmpRegName(reg), RegOff(0,TmpRegName(reg)), NULL));
					}else{//what we find in the stack is the first element of the array
						//get the address of the start of the array
						code = AppendSeq(code, GenInstr(NULL, "la", TmpRegName(reg), fAttr->addr, NULL));
					}
					//at this point, we have the start address of the array
					AppendSeq(code, GenInstr(NULL, "sll", TmpRegName(index->Reg), TmpRegName(index->Reg), "2"));
					AppendSeq(code, GenInstr(NULL, "add", TmpRegName(reg), TmpRegName(reg), TmpRegName(index->Reg)));//add offset to array address
					AppendSeq(code, GenInstr(NULL, "sw", TmpRegName(Expr->Reg), RegOff(0,TmpRegName(reg)), NULL));
					ReleaseTmpReg(reg);
					ReleaseTmpReg(index->Reg);
					free(index);
					ReleaseTmpReg(Expr->Reg);
					free(Expr);
					return code;
				}
			}else{//this should be an int
				if(fAttr->type < 0){//no index was provided for the array
					writeIndicator(getCurrentColumnNum());
					writeMessage("No index provided for array.");
					int reg;
					reg = AvailTmpReg();
					code = Expr->Instrs;
					code = AppendSeq(code, GenInstr(NULL, "lw", TmpRegName(Expr->Reg), fAttr->addr, NULL));
					if(fAttr->isParam){//we have loaded the address of an array
						if(fAttr->isParam){//what we find in the stack is an address pointing to the array
						//load the address that points to the start of the array
						AppendSeq(code, GenInstr(NULL, "lw", TmpRegName(reg), fAttr->addr, NULL));
						AppendSeq(code, GenInstr(NULL, "la", TmpRegName(reg), RegOff(0,TmpRegName(reg)), NULL));
					}else{//what we find in the stack is the first element of the array
						//get the address of the start of the array
						AppendSeq(code, GenInstr(NULL, "la", TmpRegName(reg), fAttr->addr, NULL));
					}
					AppendSeq(code, GenInstr(NULL, "sw", TmpRegName(Expr->Reg), RegOff(0,TmpRegName(reg)), NULL));
					ReleaseTmpReg(reg);
					ReleaseTmpReg(Expr->Reg);
					free(Expr);
					return code;
					}
				}else{//local int with no index
					code = Expr->Instrs;
					code = AppendSeq(code, GenInstr(NULL, "sw", TmpRegName(Expr->Reg), fAttr->addr, NULL));
					ReleaseTmpReg(Expr->Reg);
					free(Expr);
					return code;
				}
			}
		}
	}else{//we are not in a function
		if(!findName(table, name) || ((struct Attribute *) getCurrentAttr(table))->type == -3){//variable does not exist
			writeIndicator(getCurrentColumnNum());
			writeMessage("Undeclared variable.");
			if(index){
				ReleaseTmpReg(index->Reg);
				free(index);
			}
			ReleaseTmpReg(Expr->Reg);
			free(Expr);
			return code;
		}else{//variable is global
			if(getType(name) != expectedType){
				writeIndicator(getCurrentColumnNum());
				writeMessage("Types do not match");
				code = NULL;
				if(index){
					ReleaseTmpReg(index->Reg);
					free(index);
				}
				return code;
			}
			if(index){//index is not NULL, so this should be an array value
				if(((struct Attribute *) getCurrentAttr(table))->type >= 0){//index provided for non-array
					writeIndicator(getCurrentColumnNum());
					writeMessage("Index provided for non-array.");
					code = Expr->Instrs;
					code = AppendSeq(code, GenInstr(NULL, "sw", TmpRegName(Expr->Reg), name, NULL));
					ReleaseTmpReg(index->Reg);
					free(index);
					ReleaseTmpReg(Expr->Reg);
					free(Expr);
					return code;
				}
				int reg;
				reg = AvailTmpReg();
				code = AppendSeq(code, index->Instrs);//add the code to generate the index
				code = AppendSeq(code, Expr->Instrs);
				AppendSeq(code, GenInstr(NULL, "la", TmpRegName(reg), name, NULL));//get address of the start of the array
				//multiply the index by 4 to get the byte offset of the location to modify
				AppendSeq(code, GenInstr(NULL, "sll", TmpRegName(index->Reg), TmpRegName(index->Reg), "2"));
				AppendSeq(code, GenInstr(NULL, "add", TmpRegName(reg), TmpRegName(reg), TmpRegName(index->Reg)));//add offset to array address
				AppendSeq(code, GenInstr(NULL, "sw", TmpRegName(Expr->Reg), RegOff(0,TmpRegName(reg)), NULL));
				ReleaseTmpReg(reg);
				ReleaseTmpReg(index->Reg);
				free(index);
				ReleaseTmpReg(Expr->Reg);
				free(Expr);
				return code;
			}else{//this should be an int
				if(((struct Attribute *) getCurrentAttr(table))->type < 0){//no index for array
					writeIndicator(getCurrentColumnNum());
					writeMessage("No index provided for array.");
				}
				//in the case of no array index, the first element is returned
				code = Expr->Instrs;
				code = AppendSeq(code, GenInstr(NULL, "sw", TmpRegName(Expr->Reg), name, NULL));
				ReleaseTmpReg(Expr->Reg);
				free(Expr);
				return code;
			}
		}
	}
}

extern struct BExprRes * doBExpr(struct ExprRes * Res1,  struct ExprRes * Res2, char * mode) {
	struct BExprRes * bRes;
	Res1->Instrs = AppendSeq(Res1->Instrs, Res2->Instrs);
 	bRes = (struct BExprRes *) malloc(sizeof(struct BExprRes));
	bRes->Label = GenLabel();
	bRes->Expr = NULL;//this is a boolean
	if(!strcmp(mode, "eq")){//the relational operator is "=="
		Res1->Instrs = AppendSeq(Res1->Instrs, GenInstr(NULL, "bne", TmpRegName(Res1->Reg), TmpRegName(Res2->Reg), bRes->Label));
	}else if(!strcmp(mode, "lt")){//the relational operator is "<"
		int reg;
		reg = AvailTmpReg();
		Res1->Instrs = AppendSeq(Res1->Instrs, GenInstr(NULL, "slt", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));
		//reg will have the value 1 if Res1->Reg is less than Res2->Reg
		AppendSeq(Res1->Instrs, GenInstr(NULL, "beq", TmpRegName(reg), "$zero", bRes->Label));
		ReleaseTmpReg(reg);
	}else if(!strcmp(mode, "leq")){//the relational operator is "<="
		int reg;
		reg = AvailTmpReg();
		Res1->Instrs = AppendSeq(Res1->Instrs, GenInstr(NULL, "slt", TmpRegName(reg), TmpRegName(Res2->Reg), TmpRegName(Res1->Reg)));
		//reg will have the value 1 if Res2->Reg is less than Res1->Reg
		AppendSeq(Res1->Instrs, GenInstr(NULL, "bne", TmpRegName(reg), "$zero", bRes->Label));
		ReleaseTmpReg(reg);\
	}else if(!strcmp(mode, "gt")){//the relational operator is ">"
		int reg;
		reg = AvailTmpReg();
		Res1->Instrs = AppendSeq(Res1->Instrs, GenInstr(NULL, "slt", TmpRegName(reg), TmpRegName(Res2->Reg), TmpRegName(Res1->Reg)));
		//reg will have the value 1 if Res2->Reg is less than Res1->Reg
		AppendSeq(Res1->Instrs, GenInstr(NULL, "beq", TmpRegName(reg), "$zero", bRes->Label));
		ReleaseTmpReg(reg);
	}else if(!strcmp(mode, "geq")){//the relational operator is "<="
		int reg;
		reg = AvailTmpReg();
		Res1->Instrs = AppendSeq(Res1->Instrs, GenInstr(NULL, "slt", TmpRegName(reg), TmpRegName(Res1->Reg), TmpRegName(Res2->Reg)));
		//reg will have the value 1 if Res1->Reg is less than Res2->Reg
		AppendSeq(Res1->Instrs, GenInstr(NULL, "bne", TmpRegName(reg), "$zero", bRes->Label));
		ReleaseTmpReg(reg);
	}else{//the relational operator is "!="
		Res1->Instrs = AppendSeq(Res1->Instrs, GenInstr(NULL, "beq", TmpRegName(Res1->Reg), TmpRegName(Res2->Reg), bRes->Label));
	}
	bRes->Instrs = Res1->Instrs;
	ReleaseTmpReg(Res1->Reg);
  	ReleaseTmpReg(Res2->Reg);
	free(Res1);
	free(Res2);
	return bRes;
}

extern struct BExprRes * doImmBExpr(struct ExprRes * Res1, int isBoolean) {
	//used to convert a number into a boolean expression. Nonzero is true, and zero is false
	//It is possible that the result will be assigned to an int or int array index instead of 
	//being used as a boolean. We will want to retain the code to generate the int.
	struct BExprRes * bRes;
	bRes = (struct BExprRes *) malloc(sizeof(struct BExprRes));
	bRes->Label = GenLabel();
	bRes->Instrs = Res1->Instrs;//we will add a beqz when this is used as a boolean
	if(!isBoolean){
		bRes->Expr = Res1;//this could be an int or array address travelling up the grammar
	}else{
		//we will release Res1's register and free Res1 if we need bRes to be a boolean later on
		AppendSeq(bRes->Instrs, GenInstr(NULL, "beq", "$zero", TmpRegName(Res1->Reg), bRes->Label));
		bRes->Expr = NULL;
		ReleaseTmpReg(Res1->Reg);
		free(Res1);
	}
	return bRes;
}

extern struct ExprRes * getBooleanVal(struct BExprRes * Res1){
	//store the value of a boolean expression. This will be accomplished by 
	//setting a register to 0 (false). Then, we will generate an if statement 
	//using the provided BExprRes. If the boolean is true, then the body will 
	//be executed, which will set the register to 1.
	int reg = AvailTmpReg();
	struct InstrSeq * code = NULL;
	struct InstrSeq * tBody = GenInstr(NULL, "li", TmpRegName(reg), "1", NULL);
	struct InstrSeq * fBody = GenInstr(NULL, "li", TmpRegName(reg), "0", NULL);
	code = AppendSeq(code, doElse(doIf(Res1, tBody), fBody));
	struct ExprRes * Expr = (struct ExprRes *) malloc(sizeof(struct ExprRes));
	Expr->Reg = reg;
	Expr->Instrs = code;
	//Res1 and its label were freed by doIf()
	return Expr;
}

extern struct BExprRes * doNot (struct BExprRes * Res1){
	char * Label = GenLabel();
	if(Res1->Expr){//previously an int
		//because this is now being used as a boolean, add a beqz to create a boolean situation
		Res1->Instrs = AppendSeq(Res1->Instrs, GenInstr(NULL, "beq", TmpRegName(Res1->Expr->Reg), "$zero", Res1->Label));
		ReleaseTmpReg(Res1->Expr->Reg);
		free(Res1->Expr);
		Res1->Expr = NULL;//this is a boolean
	}
	Res1->Instrs = AppendSeq(Res1->Instrs, GenInstr(NULL, "j", Label, NULL, NULL));
	AppendSeq(Res1->Instrs, GenInstr(Res1->Label, NULL, NULL, NULL, NULL));
	free(Res1->Label);//free up space of old label
	Res1->Label = Label;
	return Res1;
}

extern struct BExprRes * doAnd (struct BExprRes * Res1,  struct BExprRes * Res2){
	if(Res1->Expr){//previously an int
		//because this is now being used as a boolean, add a beqz to create a boolean situation
		Res1->Instrs = AppendSeq(Res1->Instrs, GenInstr(NULL, "beq", TmpRegName(Res1->Expr->Reg), "$zero", Res1->Label));
		ReleaseTmpReg(Res1->Expr->Reg);
		free(Res1->Expr);
		Res1->Expr = NULL;//this is a boolean
	}
	if(Res2->Expr){//previously an int
		//because this is now being used as a boolean, add a beqz to create a boolean situation
		Res2->Instrs = AppendSeq(Res2->Instrs, GenInstr(NULL, "beq", TmpRegName(Res2->Expr->Reg), "$zero", Res2->Label));
		ReleaseTmpReg(Res2->Expr->Reg);
		free(Res2->Expr);
		Res2->Expr = NULL;//this is a boolean
	}
	Res1->Instrs = AppendSeq(Res1->Instrs, Res2->Instrs);
	//each Label can have a max of 8 chars (including the NULL terminator), plus we want a new line, so the extra terminator is replaced
	char * newLabel = (char *) calloc(24, sizeof(char));
	strcat(newLabel, Res1->Label);
	strcat(newLabel, ":\r\n");//labels need a colon. Only one label per line
	strcat(newLabel, Res2->Label);
	free(Res1->Label);
	Res1->Label = newLabel;
	free(Res2->Label);
	free(Res2);
	return Res1;
}

extern struct BExprRes * doOr (struct BExprRes * Res1,  struct BExprRes * Res2){
	char * Label = GenLabel();//marks where a true should jump to
	if(Res1->Expr){//previously an int
		//because this is now being used as a boolean, add a beqz to create a boolean situation
		Res1->Instrs = AppendSeq(Res1->Instrs, GenInstr(NULL, "beq", TmpRegName(Res1->Expr->Reg), "$zero", Res1->Label));
		ReleaseTmpReg(Res1->Expr->Reg);
		free(Res1->Expr);
		Res1->Expr = NULL;//this is a boolean
	}
	if(Res2->Expr){//previously an int
		//because this is now being used as a boolean, add a beqz to create a boolean situation
		Res2->Instrs = AppendSeq(Res2->Instrs, GenInstr(NULL, "beq", TmpRegName(Res2->Expr->Reg), "$zero", Res2->Label));
		ReleaseTmpReg(Res2->Expr->Reg);
		free(Res2->Expr);
		Res2->Expr = NULL;//this is a boolean
	}
	Res1->Instrs = AppendSeq(Res1->Instrs, GenInstr(NULL, "j", Label, NULL, NULL));//short circuit
	AppendSeq(Res1->Instrs, GenInstr(Res1->Label, NULL, NULL, NULL, NULL));
	AppendSeq(Res1->Instrs, Res2->Instrs);
	AppendSeq(Res1->Instrs, GenInstr(Label, NULL, NULL, NULL, NULL));
	free(Res1->Label);
	Res1->Label = Res2->Label;
	free(Res2);
	return Res1;
}


extern struct BExprRes * doIf(struct BExprRes * bRes, struct InstrSeq * seq) {
	//this method leaves the possibility for subsequent "else if" or "else" statements
	//if the original condition fails, we jump to the end of the body. However, 
	//once we complete a body code sequence, we need to jump to the end of the entire 
	//if structure
	struct BExprRes * seq2;
	seq2 = (struct BExprRes *) malloc(sizeof(struct BExprRes));
	seq2->Label = GenLabel();//this will mark the end of the entire if structure
	seq2->Instrs = AppendSeq(bRes->Instrs, seq);//the conditional followed by the body
	seq2->Instrs = AppendSeq(seq2->Instrs, GenInstr(NULL, "j", seq2->Label, NULL, NULL));//once we are finished with the body instructions, break
	AppendSeq(seq2->Instrs, GenInstr(bRes->Label, NULL, NULL, NULL, NULL));//if the condition fails, skip the body
	free(bRes->Label);
	free(bRes);
	return seq2;
}

extern struct BExprRes * doElseIf(struct BExprRes * bRes1, struct BExprRes * bRes2, struct InstrSeq * seq1){
	//this method will append a conditional and body to an exitsing if structure
	//bRes1->Instrs contains a complete if structure except for the outer label to jump to 
	//after a body is done. bRes2 is juist the conditional of the else if, and seq1 is the 
	//body for that conditional
	struct BExprRes * seq2;
	seq2 = (struct BExprRes *) malloc(sizeof(struct BExprRes));
	seq2->Label = bRes1->Label;//the outer label of the if structure
	seq2->Instrs = bRes1->Instrs;//previous if structure
	seq2->Instrs = AppendSeq(seq2->Instrs, bRes2->Instrs);//add the conditional
	seq2->Instrs = AppendSeq(seq2->Instrs, seq1);//add the body
	seq2->Instrs = AppendSeq(seq2->Instrs, GenInstr(NULL, "j", seq2->Label, NULL, NULL));//once we are finished with the body instructions, break
	AppendSeq(seq2->Instrs, GenInstr(bRes2->Label, NULL, NULL, NULL, NULL));//if the condition fails, skip the body
	free(bRes1);//we will keep the label and instructions
	free(bRes2->Label);
	free(bRes2);
	return seq2;
}

extern struct InstrSeq * doElse(struct BExprRes *bRes, struct InstrSeq * seq1){
	//this method will append a body and outer label to an existing if structure.
	//the result will be a complete instruction sequence because the if structure 
	//cannot have any more conditionals after the else
	struct InstrSeq * seq2;
	seq2 = bRes->Instrs;//the previous if structure
	//each body has a jump to the outside, so this will only be executed if ever conditional is false
	seq2 = AppendSeq(seq2, seq1);
	seq2 = AppendSeq(seq2, GenInstr(bRes->Label, NULL, NULL, NULL, NULL));//append the outer label
	free(bRes->Label);
	free(bRes);
	return seq2;
}

extern struct InstrSeq * finishIf(struct BExprRes *bRes){
	//this method will be called for any if structures that do not have the optional
	//else at the end. It's only purpose is to append the outer label that all of the 
	//body statements will jump to after they are finished.
	struct InstrSeq * seq2;
	seq2 = bRes->Instrs;//the previous if structure
	seq2 = AppendSeq(seq2, GenInstr(bRes->Label, NULL, NULL, NULL, NULL));//append the outer label
	free(bRes->Label);
	free(bRes);
	return seq2;
}

extern struct InstrSeq * doWhile(struct BExprRes * bRes, struct InstrSeq * seq){
	struct InstrSeq * seq2;
	char * start = GenLabel();//the while loop will jump back here to check the condition
	seq2 = GenInstr(start, NULL, NULL, NULL, NULL);
	AppendSeq(seq2, bRes->Instrs);//append the conditional
	AppendSeq(seq2, seq);//body of the while loop
	AppendSeq(seq2, GenInstr(NULL, "j", start, NULL, NULL));//jump back to the comparison
	AppendSeq(seq2, GenInstr(bRes->Label, NULL, NULL, NULL, NULL));//exit point if conditional is false
	free(bRes->Label);
	free(bRes);
	return seq2;
}

extern struct InstrSeq * doFor(struct InstrSeq * init, struct BExprRes * bRes, struct InstrSeq * increment, struct InstrSeq * body){
	//init should include some declaration of the counter
	struct InstrSeq * seq2;
	char * start = GenLabel();//the while loop will jump back here to check the condition
	seq2 = init;//start by initializing the loop variable
	seq2 = AppendSeq(seq2, GenInstr(start, NULL, NULL, NULL, NULL));
	AppendSeq(seq2, bRes->Instrs);//append the conditional
	AppendSeq(seq2, body);//body of the for loop
	AppendSeq(seq2, increment);//increment/decrement loop variable
	AppendSeq(seq2, GenInstr(NULL, "j", start, NULL, NULL));//jump back to the comparison
	AppendSeq(seq2, GenInstr(bRes->Label, NULL, NULL, NULL, NULL));//exit point if conditional is false
	free(bRes->Label);
	free(bRes);
	return seq2;
}

/*

extern struct InstrSeq * doIf(struct ExprRes *res1, struct ExprRes *res2, struct InstrSeq * seq) {
	struct InstrSeq *seq2;
	char * label;
	label = GenLabel();
	AppendSeq(res1->Instrs, res2->Instrs);
	AppendSeq(res1->Instrs, GenInstr(NULL, "bne", TmpRegName(res1->Reg), TmpRegName(res2->Reg), label));
	seq2 = AppendSeq(res1->Instrs, seq);
	AppendSeq(seq2, GenInstr(label, NULL, NULL, NULL, NULL));
	ReleaseTmpReg(res1->Reg);
  	ReleaseTmpReg(res2->Reg);
	free(res1);
	free(res2);
	return seq2;
}

*/
void Finish(struct InstrSeq *Code){
	struct InstrSeq *code;
	//struct SymEntry *entry;
	int hasMore;
	struct Attr * attr;
	code = GenInstr(NULL,".text",NULL,NULL,NULL);
	//AppendSeq(code,GenInstr(NULL,".align","2",NULL,NULL));
	AppendSeq(code,GenInstr(NULL,".globl","main",NULL,NULL));
	AppendSeq(code, GenInstr("main",NULL,NULL,NULL,NULL));
	AppendSeq(code,Code);
	AppendSeq(code, GenInstr(NULL, "li", "$v0", "10", NULL)); 
	AppendSeq(code, GenInstr(NULL,"syscall",NULL,NULL,NULL));
	//add functions
	hasMore = startIterator(table);
	while (hasMore){
		struct Attribute * attr;
		attr = (struct Attribute *) getCurrentAttr(table);
		if(attr->functType != -1){//there is a function entry
			AppendSeq(code, attr->funct);
			free(attr->functLabel);
		}
		hasMore = nextEntry(table);
	}
	//add data
	AppendSeq(code,GenInstr(NULL,".data",NULL,NULL,NULL));
	AppendSeq(code,GenInstr(NULL,".align","4",NULL,NULL));
	AppendSeq(code,GenInstr("_nl",".asciiz","\"\\n\"",NULL,NULL));
	AppendSeq(code,GenInstr("_sp", ".asciiz","\" \"", NULL, NULL));
	AppendSeq(code,GenInstr("_list", ".asciiz","\", \"", NULL, NULL));
	AppendSeq(code,GenInstr("_true", ".asciiz","\"true\"", NULL, NULL));
	AppendSeq(code,GenInstr("_false", ".asciiz","\"false\"", NULL, NULL));
	hasMore = startIterator(table);
	while (hasMore){
		struct Attribute * attr;
		attr = (struct Attribute *) getCurrentAttr(table);
		if(attr->type != -3){//there is a variable entry
			AppendSeq(code,GenInstr((char *) getCurrentName(table), ".word", attr->notation, NULL, NULL));
			free(attr->notation);
		}
		hasMore = nextEntry(table);
	}
	WriteSeq(code);
	destroySymTab(table);
	return;
}
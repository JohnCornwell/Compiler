/* Semantics.h
   The action and supporting routines for performing semantics processing.
*/

struct Attribute{//used to store variable sizes and function info in the symbol table
	int type;//variable type. 0 is int, -1 is an int array, 1 is boolean, -2 is boolean array, and -3 means no entry
	char * notation;//the mips notation for the size
	int functType;//0 is void, 1 is int, and 2 is boolean
	struct InstrSeq * funct;//pointer to function code
	char * functLabel;//we can look this up when we want to call this function
	int localVars;//number of local variables and return address
	int argTypes[127];//parameter type for each parameter. -1 is array, 0 is int. -3 means there is no parameter
	//this means we can have a maximum of 508 bytes on the stack for a function's parameters
};

struct functAttr{//used to store information on local variables and parameters
	int type;//-1 is an int array, 0 is an int, 1 is boolean, and -2 is a boolean array
	char * addr;//the address of the parameter/local variable on the stack
	int isParam;//if true and this is an array, the address points to an array address
};

/* Semantic Records */
struct IdList {
	struct SymEntry * TheEntry;
	struct IdList * Next;
};

struct ExprRes {
	int Reg;
	struct InstrSeq * Instrs;
	//we need a way to tell if this is a boolean variable that was read from 
	//memory, and has not been used as a boolean by the time it reaches BExpr 
	//in the grammar. If this is the case, the BExprRes that has this struct 
	//needs to be classified as a boolean by freeing this struct. Used for 
	//prints.
	int isBoolean;
};

struct BExprResList {
	struct BExprRes * BExpr;
	struct BExprResList * Next;
};

struct IdentList {
	char * Id;
	struct ExprRes * index;
	struct IdentList * Next;
};

struct varList {
	char * Id;
	int type;
	int user;
	//only necessary for local parameters
	int isBoolean;//if the type is used for an array size, this will indicate int or boolean
	struct varList * Next;
};

struct BExprRes {
	char * Label;
	struct InstrSeq * Instrs;
	//when assigning a value to a variable, any integer values will be 
	//recognized as a boolean. In order to retain the instructions and 
	//value of the integer, we will retain the ExprRes until there is 
	//a relational or boolean operator encountered. If there is a 
	//relational or boolean operator encountered, the ExprRes will be
	//set to NULL to indicate that this is now a boolean.
	struct ExprRes * Expr;
};

struct ParamList{//a collection of data values and array addresses
	struct ExprRes * value;//holds a literal value or a pointer to an int or boolean array
	struct BExprRes * boolean;//holds a boolean value
	int type;//-1 is an int array, 0 is an int, -2 is a boolean array, and 1 is a boolean
	struct ParamList * Next;
};

/* Semantics Actions */
extern void enterSize(int size, int mode);
extern void makeFunction(int type);
extern void makeTable(struct varList * param, struct varList * local, char * name);
extern void addBody(char * name, struct InstrSeq * body);
extern struct ExprRes * doIntLit(char * digits);
extern struct ExprRes * doRval(char * name, struct ExprRes * index, int expectedType);/////////
extern struct InstrSeq * doAssign(char * name, struct ExprRes * Res1, struct ExprRes * index, int expectedType);/////////
extern struct ExprRes * doOp(struct ExprRes * Res1, struct ExprRes * Res2, char * op);
struct ExprRes * doDivOrMod(struct ExprRes * Res1, struct ExprRes * Res2, char * op);
struct ExprRes * doPow(struct ExprRes * Res1, struct ExprRes * Res2);
struct ExprRes * doNeg(struct ExprRes * Res1);
struct BExprResList * AppendExpr(struct BExprRes * BExpr, struct BExprResList * list);
struct IdentList * AppendRead(char * Id, struct ExprRes * index, struct IdentList * list);
struct ParamList * newPList(struct ExprRes * value, struct BExprRes * boolean, int type);
struct ExprRes * getArg(char * Id);//////////
extern int getType(char * Id);///////
extern struct varList * AppendVar(char * Id, int size, struct varList * list, int user, int isBoolean);
extern struct InstrSeq * getVoidFunction(char * name, struct ParamList * params);
extern struct ExprRes * getIntFunction(char * name, struct ParamList * params);
extern struct InstrSeq * doVoidReturn();
extern struct InstrSeq * doIntReturn(struct ExprRes * Expr);
extern struct InstrSeq * doBoolReturn(struct BExprRes * bRes);
extern struct InstrSeq * doRead(struct IdentList * list);/////////////
extern struct InstrSeq * doPrint(struct BExprResList * BExprList);
extern struct InstrSeq * doPrintLine();
extern struct InstrSeq * doPrintSpaces(struct ExprRes * Expr);
extern struct BExprRes * doBExpr(struct ExprRes * Res1,  struct ExprRes * Res2, char * mode);
extern struct BExprRes * doImmBExpr(struct ExprRes * Res1, int isBoolean);
extern struct ExprRes * getBooleanVal(struct BExprRes * Res1);
extern struct BExprRes * doNot(struct BExprRes * Res1);
extern struct BExprRes * doAnd(struct BExprRes * Res1,  struct BExprRes * Res2);
extern struct BExprRes * doOr(struct BExprRes * Res1,  struct BExprRes * Res2);
extern struct BExprRes * doIf(struct BExprRes * bRes, struct InstrSeq * seq);
extern struct BExprRes * doElseIf(struct BExprRes * bRes1, struct BExprRes * bRes2, struct InstrSeq * seq1);
extern struct InstrSeq * doElse(struct BExprRes *bRes, struct InstrSeq * seq1);
extern struct InstrSeq * finishIf(struct BExprRes *bRes);
extern struct InstrSeq * doWhile(struct BExprRes *bRes, struct InstrSeq * seq);
extern struct InstrSeq * doFor(struct InstrSeq * init, struct BExprRes * bRes, struct InstrSeq * increment, struct InstrSeq * body);

extern void	Finish(struct InstrSeq *Code);
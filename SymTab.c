#include <stdlib.h>
#include <string.h>
#include "SymTab.h"


#include <stdio.h>

int hash(SymTab * table, char * name){
	//add up each char value and mod by the size of the table
	int hash = 0;
	while(*name != 0){//while the character being pointed to is the terminating character
		hash += *name;
		name ++;//go to next char
	}
	//make sure that the largest number returned is the max index of the table
	return hash % table->size;
}

/* PRE: size >= 0
 size is an estimate of the number of items that will be stored in the symbol
 table
 Return a pointer to a new symbol table
*/
SymTab * createSymTab(int size){
	SymTab * table = (SymTab *) malloc(sizeof(SymTab));
	table->size = size;
	table->contents = (SymEntry **) calloc(size, sizeof(SymEntry *));//initialize array values to zero
	table->current = NULL;
	return table;
}

//In the following functions assume a pre condition that table references a
//previously created symbol table

//recover space created by the symbol table functions
//no functions should use the symbol table after it is destroyed
void destroySymTab(SymTab *table){
	int index = table->size - 1;
	while(index >= 0){
		SymEntry * entry = table->contents[index];
		while(entry){//while entry is not NULL
			SymEntry * next = entry->next;
			free(entry->attribute);
			free(entry->name);
			free(entry);
			entry = next;
		}
		index--;
		entry = table->contents[index];
	}
	free(table->contents);
	free(table);
}

/*if name is not in the symbol table, a copy of name is added to the symbol table
 with a NULL attribute, set current to reference the new (name, attribute) pair
 and return 1
 if name is in the symbol table, set current to reference the (name, attribute)
 pair and return 0
*/
int enterName(SymTab * table, char * name){
	if(findName(table, name) == 1){//found name in the table
		return 0;
	}
	int index = hash(table, name);
	SymEntry * entry = (SymEntry *) malloc(sizeof(SymEntry));
	entry->name = (char *) malloc(strlen(name) + 1);//have the entry name point to a space
	strcpy(entry->name, name);
	entry->attribute = NULL;
	entry->next = table->contents[index];
	table->contents[index] = entry;
	table->current = entry;
	return 1;
}

/*if name is in the symbol table, set current to reference the (name, attribute)
 pair and return 1
 otherwise do not change current and return 0
*/
int findName(SymTab *table, char *name){
	int index = hash(table, name);
	SymEntry * entry = table->contents[index];
	while(entry != NULL){//the pointer is not null
		if(!strcmp(name, entry->name)){//strcmp returns 0 if the strings are equal
			table->current = entry;
			return 1;
		}
		entry = entry->next;
	}
	return 0;
}

//if current references a (name, attribute) pair return 1
//otherwise return 0;
int hasCurrent(SymTab *table){
	if(table->current){
		return 1;
	}
	return 0;
}

//PRE: hashCurrent() == 1
//change the attribute value of the current (name, attribute) pair to attr
void setCurrentAttr(SymTab *table, void * attr){
	table->current->attribute = malloc(sizeof(attr));
	table->current->attribute = attr;
}

//PRE: hasCurrent() == 1
//return the attribute in the current (name, attribute) pair
void * getCurrentAttr(SymTab *table){
	return table->current->attribute;
}

//PRE: hasCurrent() == 1
//return the name in the current (name, attribute) pair
char * getCurrentName(SymTab *table){
	return table->current->name;
}

//Assume no changes are made to the symbol table while iterating through the symbol table
//if the symbol table is empty, return 0
//otherwise set current to the "first" (name, attribute) pair in the symbol table and return 1
int startIterator(SymTab *table){
	int index = 0;
	while(index < table->size){//not at the end of the array, and the current address is 0
		if(table->contents[index] == NULL){//if the address is null
			index++;
		}else{//found the first entry
			table->current = table->contents[index];
			return 1;
		}
	}
	return 0;
}

/*if all (name, attribute) pairs have been visited since the last call to
 startIterator, return 0
 otherwise set current to the "next" (name, attribute) pair and return 1
*/
int nextEntry(SymTab *table){
	SymEntry * entry = table->current;
	if(entry->next != NULL){
		table->current = entry->next;
		return 1;
	}//else that was the last entry in the linked list
	int index = hash(table, entry->name) + 1;//gets the index of the next linked list
	while(index < table->size){
		if(table->contents[index] == NULL){
			index++;
		}else{//this index has an entry
			table->current = table->contents[index];
			return 1;
		}
	}//reached the end of the table without finding an entry
	return 0;
}

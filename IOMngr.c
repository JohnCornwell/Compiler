#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXLINE 1024

FILE * sourceFile = NULL;
FILE * listingFile = NULL;//if listing file is null, output is printed in stdout.
int currentLine = 0;//used to number the lines in the listing file.
int currentCol = -1;//the current index in the current line.
char line [MAXLINE] = {0};//holds the line read from file.
char * f = "1";
int lastError = 0;//indicates the last line to have an error/indicator printed.
int readAll = 1;//boolean is true when the array of characters is exhausted.

int openFiles(char * sourceName, char * listingName){
	if((sourceFile = fopen(sourceName, "r+"))){
		if(listingName){//listing file pointer is not null
			if((listingFile = fopen(listingName, "w"))){
				return 1;
			}
			return 0;
		}
		return 1;
	}
	return 0;
}

void closeFiles(){
	fclose(sourceFile);
	if(listingFile){
		fclose(listingFile);
	}
}

char getNextSourceChar(){
	if(line[currentCol + 1] == 0){//if all characters in the current array have been read
		if(feof(sourceFile)){//reached the end of the source file
			return EOF;
		}//else there is still something to read
		f = fgets(line, MAXLINE, sourceFile);
		if(!f){
			line[0] = 0;
			currentCol = -1;
			return EOF;
		}
		currentLine++;//increment line number
		currentCol = -1;//increment currentCol before returning a char
		if(listingFile){//there is a listing file
			fprintf(listingFile, "%d. %s", currentLine, line);//write the line number and the line read
			if(strchr(line, '\n') == NULL){//should only be called on the end of file
				fprintf(listingFile, "\n");//adds a new line so that errors are printed beneath a line without a newline
			}
		}
	}
	//at this point, we have a char array from the file
	currentCol++;//go to the next char
	return line[currentCol];
}

void writeIndicator(int column){
	if(listingFile){//there is a listing file to write to
		fprintf(listingFile, "%*c^\n", column + 3, ' ');//line numbering takes up three characters
		return;
	}
	if(lastError != currentLine){
		lastError = currentLine;
		printf("%d. %s", currentLine, line);
		if(strchr(line, '\n') == NULL){//should only be called on the end of file
			printf("\n");//adds a new line so that errors are printed beneath a line without a newline
		}
	}
	printf("%*c^\n", column + 3, ' ');//line numbering takes up three characters
}

void writeMessage(char * message){
	if(listingFile){//there is a listing file to write to.
		fprintf(listingFile, "%s\n", message);
		return;
	}
	printf("%s\n", message);
}

int getCurrentLineNum(){
	return currentLine;
}

int getCurrentColumnNum(){
	return currentCol;
}

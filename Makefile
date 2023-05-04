CC = gcc
OFILES = SymTab.o Semantics.o CodeGen.o IOMngr.o y.tab.o lex.yy.o main.o
HFILES = SymTab.h IOMngr.h CodeGen.h Semantics.h

compiler: $(OFILES) $(HFILES)
	$(CC) $(OFILES) -o compiler

CodeGen.o: CodeGen.c $(HFILES)
	$(CC) -c -g CodeGen.c 

y.tab.o: y.tab.c y.tab.h $(HFILES)
	$(CC) -c -g y.tab.c
	
lex.yy.o: lex.yy.c $(HFILES)
	$(CC) -c -g lex.yy.c

IOMngr.o: IOMngr.c $(HFILES)
	$(CC) -c -g IOMngr.c 

Semantics.o: Semantics.c $(HFILES)
	$(CC) -c -g Semantics.c 

SymTab.o: SymTab.c $(HFILES)
	$(CC) -c -g SymTab.c 

main.o:	main.c $(HFILES)
	$(CC) -c -g main.c
	
clean: 
	rm main.o SymTab.o Semantics.o IOMngr.o y.tab.o CodeGen.o lex.yy.o compiler

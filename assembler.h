#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

#define OPCODE_I 5
#define OPERANDO_1 10
#define OPERANDO_2 15
#define OPERANDO_3 20
#define SA 25
#define END 31

	extern FILE *yyin, *yyout;

	int yylex();
	int yyerror(char*);
	void SegundaEtapa();
	void GerarObjeto();


#endif

%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <math.h>

	#include "buffer.h"
	#include "hash.h"
	#include "estruturas.h"
	#include "assembler.h"


	FILE *yyin, *yyout;

%}


%token ITIPO1 ITIPO2 ITIPO3
%token IOPS1 IOPS2 IPO3
%token JTIPO1
%token REGISTRADOR
%token IMEDIATO
%token VARIAVEL
%token LABEL
%token DECLARACAO
%token ADDRESS
%token DIRECTIVE
%token NOMEVARIAVEL VALORVARIAVEL
%token SYSCALL

/* rtype1 */
%token SLLV SRLV SRAV ADD ADDU SUB SUBU AND OR XOR NOR SLT SLTU MUL
/* rtype2 */
%token JALR MULT MULTU DIV DIVU
/* rtype3 */
%token JR MFHI MTHI MFLO MTLO
/* rtype4 */
%token SLL SRL SRA
/* branch */
%token BEQ


%%

codigo: partedados texto
	| texto
	;
partedados: data
	;

data: declaracao data
	| declaracao
	;

declaracao: NOMEVARIAVEL DIRECTIVE valorvariavel
	{
		numero_variaveis += 1;
		tabela_variaveis[$1] = pre_posicao_data;
		pre_posicao_data = pos_posicao_data;
	}
	| NOMEVARIAVEL DIRECTIVE
	{

		Itob(0,0);
		strcpy(segunda_traducao[numero_linhas++].primeira_traducao, buffer);
		LimpaBuffer();
		numero_variaveis += 1;
		tabela_variaveis[$1] = pre_posicao_data;
		pre_posicao_data = pos_posicao_data;
	}
	;

valorvariavel: valorvariavel VALORVARIAVEL
	{
		Itob($2, END);
		strcpy(segunda_traducao[numero_linhas++].primeira_traducao, buffer);
		LimpaBuffer();
		pos_posicao_data += 1;

	}
	| VALORVARIAVEL
	{
		Itob($1, END);
		strcpy(segunda_traducao[numero_linhas++].primeira_traducao, buffer);
		LimpaBuffer();
		pos_posicao_data +=1;
	}
	;

texto: palavra texto
	| palavra
	;

palavra: rtype1 rop1
	{
	 	strcpy(segunda_traducao[numero_linhas++].primeira_traducao , buffer);
	 	LimpaBuffer();
	 	text_linhas +=1;
	}
	| rtype2 rop2
	{
		strcpy(segunda_traducao[numero_linhas++].primeira_traducao , buffer);
		LimpaBuffer();
		text_linhas +=1;
	}
	| rtype3 rop3
	{
		strcpy(segunda_traducao[numero_linhas++].primeira_traducao , buffer);
		LimpaBuffer();
		text_linhas +=1;
	}
	| rtype4 rop4
	{
		strcpy(segunda_traducao[numero_linhas++].primeira_traducao , buffer);
		LimpaBuffer();
		text_linhas +=1;
	}
	| iformat
	{
		strcpy(segunda_traducao[numero_linhas++].primeira_traducao , buffer);
		LimpaBuffer();
		text_linhas +=1;
	}
	| jformat
	{
		strcpy(segunda_traducao[numero_linhas++].primeira_traducao , buffer);
		LimpaBuffer();
		text_linhas +=1;
	}
	| rotulo {/*faca alguma coisa*/}
	| chamada
	{
		strcpy(segunda_traducao[numero_linhas++].primeira_traducao , buffer);
		LimpaBuffer();
		text_linhas +=1;
	}
	;

rtype1: SLLV {Itob($1, END);}
	| SRLV {Itob($1, END);}
	| SRAV {Itob($1, END);}
	| ADD {Itob($1, END);}
	| ADDU {Itob($1, END);}
	| SUB {Itob($1, END);}
	| SUBU {Itob($1, END);}
	| AND {Itob($1, END);}
	| OR {Itob($1, END);}
	| XOR {Itob($1, END);}
	| NOR {Itob($1, END);}
	| SLT {Itob($1, END);}
	| SLTU {Itob($1, END);}
	| MUL{Itob($1, OPCODE_I);}
	;

rop1: REGISTRADOR REGISTRADOR REGISTRADOR
	{
		Itob($1, OPERANDO_3);
		Itob($2, OPERANDO_1);
		Itob($3, OPERANDO_2);
	}
	;

rtype2: MULT {Itob($1, END);}
	| MULTU {Itob($1, END);}
	| DIV {Itob($1, END);}
	| DIVU{Itob($1, END);}
	;

rop2: REGISTRADOR REGISTRADOR
	{
		Itob($1, OPERANDO_1);
		Itob($2, OPERANDO_2);
	}
	;

rtype3: JR{Itob($1, END);}
	| MFHI{Itob($1, END);}
	| MTHI{Itob($1, END);}
	| MFLO{Itob($1, END);}
	| MTLO{Itob($1, END);}
	| JALR {Itob($1, END);Itob(31, OPERANDO_3);}
	;

rop3: REGISTRADOR
	{
		Itob($1, OPERANDO_1);
	}
	;

rtype4: SLL {Itob($1, END);}
	| SRL {Itob($1, END);}
	| SRA {Itob($1, END);}
	;

rop4: REGISTRADOR REGISTRADOR IMEDIATO
	{
		Itob($1, OPERANDO_3);
		Itob($2, OPERANDO_2);
		Itob($3, SA);
	}
	| REGISTRADOR REGISTRADOR VARIAVEL
	{
		Itob($1, OPERANDO_3);
		Itob($2, OPERANDO_2);
		Itob(tabela_variaveis[$3], SA);
	}
	;

iformat: itype1 iop1
	| itype2 iop2
	| itype3 iop3
	;

itype1: ITIPO1 {Itob($1, OPCODE_I);}
	;

iop1: REGISTRADOR REGISTRADOR IMEDIATO
	{
		Itob($1, OPERANDO_2);
		Itob($2, OPERANDO_1);
		Itob($3, END);
	}
	| REGISTRADOR REGISTRADOR VARIAVEL
	{
		Itob($1, OPERANDO_2);
		Itob($2, OPERANDO_1);
		Itob(tabela_variaveis[$3], END);
	}
	| REGISTRADOR REGISTRADOR ADDRESS
	{
		Itob($1, OPERANDO_2);
		Itob($2, OPERANDO_1);
		if(tabela_rotulos[$3] != -1) Itob(tabela_rotulos[$3], END);
		else segunda_traducao[numero_linhas].referencia_indefinida = $3;
	}
	;

itype2: ITIPO2 {Itob($1, OPCODE_I);}
	;

iop2: REGISTRADOR IMEDIATO
	{
		Itob($1, OPERANDO_2);
		Itob($2, END);
	}
	| REGISTRADOR VARIAVEL
	{
		Itob($1, OPERANDO_2);
		Itob(tabela_variaveis[$2], END);
	}
	| REGISTRADOR ADDRESS
	{
		Itob($1, OPERANDO_2);
		if(tabela_rotulos[$2] != -1) Itob(tabela_rotulos[$2], END);
		else segunda_traducao[numero_linhas].referencia_indefinida = $2;
	}
	;

itype3: ITIPO3 {Itob($1, OPCODE_I);}
	;

iop3: REGISTRADOR IMEDIATO REGISTRADOR
	{
		Itob($1, OPERANDO_2);
		Itob($2, END);
		Itob($3, OPERANDO_1);
	}
	;

jformat: jtype1 jop1
	;

jtype1: JTIPO1
	{
		Itob($1, OPCODE_I);
	}
	;

jop1: ADDRESS
	{
		/* backpatching */
		if(tabela_rotulos[$1] != -1) Itob(tabela_rotulos[$1], END);
		else segunda_traducao[numero_linhas].referencia_indefinida = $1;
	}
	;

rotulo: LABEL
	{
		tabela_rotulos[$1] = text_linhas+1;
	}
	;
chamada: SYSCALL
	{
		Itob(12, END);
	}

%%

	int yyerror(char* s)
	{
  		fprintf(stderr, "ERROU NO CODIGO: %s\n", s);
  		return -1;
	}

	void SegundaEtapa()
	{
		int atual_instrucao = -1;
		int index;
		int flag;
		int instrucao_binario;
		int zero = 0;

		while(atual_instrucao++ < numero_linhas - 1)
		{
			index = 31;
			flag = tabela_rotulos[segunda_traducao[atual_instrucao].referencia_indefinida];
			if(flag != -1)
			{
				while(flag > 0)
				{
					segunda_traducao[atual_instrucao].primeira_traducao[index--] = (flag & 1) + '0';
					flag = (flag >> 1);
				}
			}

			if(strlen(segunda_traducao[atual_instrucao].primeira_traducao) == 32)
			{
				printf("%s\n", segunda_traducao[atual_instrucao].primeira_traducao);
				instrucao_binario = (int) strtol(segunda_traducao[atual_instrucao].primeira_traducao, NULL, 2);
				fwrite(&instrucao_binario, sizeof(int), 1, yyout);
				//fprintf(yyout, "%d\n", (int)strtol(segunda_traducao[atual_instrucao].primeira_traducao, NULL, 2));
			}
			else
			{
				fwrite(&zero, sizeof(int), 1, yyout);
				printf("\n");
			}
		}
	}

	void GerarObjeto(char *arquivo)
	{
		yyin = fopen(arquivo, "r");
		yyout = fopen("output", "w");
		yyparse();
		SegundaEtapa();
		fclose(yyout);
		fclose(yyin);
	}

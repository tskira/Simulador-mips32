%{
	#include <string.h>

	#include "assembler.tab.h"
	#include "buffer.h"
	#include "hash.h"
	#include "estruturas.h"

	int zero = 0;
%}

%option yylineno

%x DADO
%x TEXTO
%x VAR_INIT
%x VALOR
%x PULO
%x BRANCHINST

%%
".data" {BEGIN DADO;}
".text"+[ \n]+".globl main" {numero_linhas = 10; BEGIN TEXTO;}
[ \n] {}
[ \t] {}

<DADO>
{
".byte" {BEGIN VALOR; return DIRECTIVE;}
".half" {BEGIN VALOR; return DIRECTIVE;}
".word" {BEGIN VALOR; return DIRECTIVE;}
".int"	{BEGIN VALOR; return DIRECTIVE;}

"," {BEGIN VALOR;}
[a-zA-Z]+":" {yytext[strlen(yytext) - 1] = '\0' ; yylval = Hash(yytext); return NOMEVARIAVEL;}
".text"+[ \n]+".globl main" {numero_linhas = 10; BEGIN TEXTO;}
[ \n] {}
[ \t] {}
. {}
}

<VALOR>
{
[ \t] {}
[0-9]+ {yylval = atoi(yytext);BEGIN DADO; return VALORVARIAVEL;}
"-"[0-9]+ {yylval = atoi(yytext);BEGIN DADO; return VALORVARIAVEL;}
[ \n] {yylval = 0; BEGIN DADO; return VALORVARIAVEL;}
. {}
}

<TEXTO>
{
"sllv" {yylval = 4; return SLLV;}
"srlv" {yylval = 6; return SRLV;}
"srav" {yylval = 7; return SRAV;}
"add" {yylval = 32; return ADD;}
"addu" {yylval = 33; return ADDU;}
"sub" {yylval = 34; return SUB;}
"subu" {yylval = 35; return SUBU;}
"and" {yylval = 36; return AND;}
"or" {yylval = 37; return OR;}
"xor" {yylval = 38; return XOR;}
"nor" {yylval = 39; return NOR;}
"slt" {yylval = 42; return SLT;}
"sltu" {yylval = 43; return SLTU;}
"jalr" {yylval = 9; return JALR;}
"mult" {yylval = 24; return MULT;}
"multu" {yylval = 25; return MULTU;}
"div" {yylval = 26; return DIV;}
"divu" {yylval = 27; return DIVU;}
"jr" {yylval = 8; return JR;}
"mfhi" {yylval = 16; return MFHI;}
"mthi" {yylval = 17; return MTHI;}
"mflo" {yylval = 18; return MFLO;}
"mtlo" {yylval = 19; return MTLO;}
"sll" {yylval = 0; return SLL;}
"srl" {yylval = 2; return SRL;}
"sra" {yylval = 3; return SRA;}
"mul" {yylval = 28; return MUL;}

"beq" {yylval = 4; BEGIN BRANCHINST; return ITIPO1;}
"bne" {yylval = 5; BEGIN BRANCHINST; return ITIPO1;}
"addi" {yylval = 8; return ITIPO1;}
"addiu" {yylval = 9; return ITIPO1;}
"slti" {yylval = 10; return ITIPO1;}
"sltiu" {yylval = 11; return ITIPO1;}
"andi" {yylval = 12; return ITIPO1;}
"ori" {yylval = 13; return ITIPO1;}
"xori" {yylval = 14; return ITIPO1;}

"blez" {yylval = 6; BEGIN BRANCHINST; return ITIPO2;}
"bgtz" {yylval = 7; BEGIN BRANCHINST; return ITIPO2;}
"lui" {yylval = 15; return ITIPO2;}

"lb" {yylval = 32; return ITIPO3;}
"lh" {yylval = 33; return ITIPO3;}
"lw" {yylval = 35; return ITIPO3;}
"lbu" {yylval = 36; return ITIPO3;}
"lhu" {yylval = 37; return ITIPO3;}
"sb" {yylval = 40; return ITIPO3;}
"sh" {yylval = 41; return ITIPO3;}
"sw" {yylval = 43; return ITIPO3;}

"j" {yylval = 2; BEGIN PULO; return JTIPO1;}
"jal" {yylval = 3; BEGIN PULO; return JTIPO1;}

[0-9]+ {yylval = atoi(yytext); return IMEDIATO;}
"-"[0-9]+ {yylval = atoi(yytext); return IMEDIATO;}

"$zero" {yylval = 0; return REGISTRADOR;}
"$at" {yylval = 1; return REGISTRADOR;}
"$v0" {yylval = 2; return REGISTRADOR;}
"$v1" {yylval = 3;return REGISTRADOR;}
"$a0" {yylval = 4;return REGISTRADOR;}
"$a1" {yylval = 5;return REGISTRADOR;}
"$a2" {yylval = 6;return REGISTRADOR;}
"$a3" {yylval = 7;return REGISTRADOR;}
"$t0" {yylval = 8;return REGISTRADOR;}
"$t1" {yylval = 9;return REGISTRADOR;}
"$t2" {yylval = 10;return REGISTRADOR;}
"$t3" {yylval = 11;return REGISTRADOR;}
"$t4" {yylval = 12;return REGISTRADOR;}
"$t5" {yylval = 13;return REGISTRADOR;}
"$t6" {yylval = 14;return REGISTRADOR;}
"$t7" {yylval = 15;return REGISTRADOR;}
"$t8" {yylval = 16;return REGISTRADOR;}
"$t9" {yylval = 17;return REGISTRADOR;}
"$s0" {yylval = 18;return REGISTRADOR;}
"$s1" {yylval = 19;return REGISTRADOR;}
"$s2" {yylval = 20;return REGISTRADOR;}
"$s3" {yylval = 21;return REGISTRADOR;}
"$s4" {yylval = 22;return REGISTRADOR;}
"$s5" {yylval = 23;return REGISTRADOR;}
"$s6" {yylval = 24;return REGISTRADOR;}
"$s7" {yylval = 25;return REGISTRADOR;}
"$k0" {yylval = 26;return REGISTRADOR;}
"$k1" {yylval = 27;return REGISTRADOR;}
"$gp" {yylval = 28;return REGISTRADOR;}
"$sp" {yylval = 29; return REGISTRADOR;}
"$fp" {yylval = 30;return REGISTRADOR;}
"$ra" {yylval = 31;return REGISTRADOR;}
"syscall" {return SYSCALL;}
[a-zA-Z]+":" {yytext[strlen(yytext) - 1] = '\0'; yylval = Hash(yytext); return LABEL;}
[a-zA-Z] {yylval = Hash(yytext); return VARIAVEL;}

[ \t] {}
[ \n] {}
. {}
}

<PULO>
{
[a-zA-Z]+ {yylval = Hash(yytext); BEGIN TEXTO; return ADDRESS;}
[ \n] {}
. {}
}

<BRANCHINST>
{
"$zero" {yylval = 0; return REGISTRADOR;}
"$at" {yylval = 1; return REGISTRADOR;}
"$v0" {yylval = 2; return REGISTRADOR;}
"$v1" {yylval = 3;return REGISTRADOR;}
"$a0" {yylval = 4;return REGISTRADOR;}
"$a1" {yylval = 5;return REGISTRADOR;}
"$a2" {yylval = 6;return REGISTRADOR;}
"$a3" {yylval = 7;return REGISTRADOR;}
"$t0" {yylval = 8;return REGISTRADOR;}
"$t1" {yylval = 9;return REGISTRADOR;}
"$t2" {yylval = 10;return REGISTRADOR;}
"$t3" {yylval = 11;return REGISTRADOR;}
"$t4" {yylval = 12;return REGISTRADOR;}
"$t5" {yylval = 13;return REGISTRADOR;}
"$t6" {yylval = 14;return REGISTRADOR;}
"$t7" {yylval = 15;return REGISTRADOR;}
"$t8" {yylval = 16;return REGISTRADOR;}
"$t9" {yylval = 17;return REGISTRADOR;}
"$s0" {yylval = 18;return REGISTRADOR;}
"$s1" {yylval = 19;return REGISTRADOR;}
"$s2" {yylval = 20;return REGISTRADOR;}
"$s3" {yylval = 21;return REGISTRADOR;}
"$s4" {yylval = 22;return REGISTRADOR;}
"$s5" {yylval = 23;return REGISTRADOR;}
"$s6" {yylval = 24;return REGISTRADOR;}
"$s7" {yylval = 25;return REGISTRADOR;}
"$k0" {yylval = 26;return REGISTRADOR;}
"$k1" {yylval = 27;return REGISTRADOR;}
"$gp" {yylval = 28;return REGISTRADOR;}
"$sp" {yylval = 29; return REGISTRADOR;}
"$fp" {yylval = 30;return REGISTRADOR;}
"$ra" {yylval = 31;return REGISTRADOR;}

[a-zA-Z]+ {yylval = Hash(yytext); BEGIN TEXTO; return ADDRESS;}
[ \n] {}
. {}
}
%%

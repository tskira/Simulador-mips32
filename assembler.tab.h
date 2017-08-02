/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_ASSEMBLER_TAB_H_INCLUDED
# define YY_YY_ASSEMBLER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ITIPO1 = 258,
    ITIPO2 = 259,
    ITIPO3 = 260,
    IOPS1 = 261,
    IOPS2 = 262,
    IPO3 = 263,
    JTIPO1 = 264,
    REGISTRADOR = 265,
    IMEDIATO = 266,
    VARIAVEL = 267,
    LABEL = 268,
    DECLARACAO = 269,
    ADDRESS = 270,
    DIRECTIVE = 271,
    NOMEVARIAVEL = 272,
    VALORVARIAVEL = 273,
    SYSCALL = 274,
    SLLV = 275,
    SRLV = 276,
    SRAV = 277,
    ADD = 278,
    ADDU = 279,
    SUB = 280,
    SUBU = 281,
    AND = 282,
    OR = 283,
    XOR = 284,
    NOR = 285,
    SLT = 286,
    SLTU = 287,
    MUL = 288,
    JALR = 289,
    MULT = 290,
    MULTU = 291,
    DIV = 292,
    DIVU = 293,
    JR = 294,
    MFHI = 295,
    MTHI = 296,
    MFLO = 297,
    MTLO = 298,
    SLL = 299,
    SRL = 300,
    SRA = 301,
    BEQ = 302
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_ASSEMBLER_TAB_H_INCLUDED  */

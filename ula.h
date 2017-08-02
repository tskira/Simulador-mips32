#ifndef ULA_H_
#define ULA_H_

	#include <stdio.h>
	#include <stdlib.h>
	#include "registradores.h"


	/*
	 * Struct para definir a unidade logica aritmetica
	 *
	 * @atributos:
	 * operando_x, operando_y: sao os valores de entrada da ula
	 * alu_cc_bit1: variavel que armazena se X=Y
	 * alu_cc_bit2: armazena se X > Y
	 * alu_output: saida da ula
	 * alu_op: a operacao a ser executada pela ula
	 */
	typedef struct ula
	{
		int operando_x;
	 	int operando_y;
		unsigned int alu_cc_bit1;
		unsigned int alu_cc_bit2;
		long long int alu_output;
		unsigned int alu_op;
	} alu;

	typedef void (*ula_operations)(alu*);

	/*
	 * Funcoes da ULA:
	 */

	 void ExecutarAlu(alu*);
	 void AluAdd(alu*);
	 void AluSub(alu*);
	 void AluAnd(alu*);
	 void AluOr(alu*);
	 void AluXor(alu*);
	 void AluNot(alu*);
	 void AluZeroTest(alu*);
	 void AluMult(alu*);
	 void AluDiv(alu*);
	 void AluLeftShift(alu*);
	 void AluRightShift(alu*);
	 void AluMultLong(alu*);

	extern ula_operations alu_primitive_operations[12];

#endif

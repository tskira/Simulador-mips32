#include "ula.h"

	ula_operations alu_primitive_operations[12] =
	{
		[0] = &AluAdd,
		[1] = &AluSub,
		[2] = &AluAnd,
		[3] = &AluOr,
		[4] = &AluXor,
		[5] = &AluNot,
		[6] = &AluZeroTest,
		[7] = &AluMult,
		[8] = &AluDiv,
		[9] = &AluLeftShift,
		[10] = &AluRightShift,
		[11] = &AluMultLong,
	};

	void ExecutarAlu(alu *alu_executar)
	{
		alu_primitive_operations[alu_executar->alu_op](alu_executar);
	}


	void AluAdd(alu *alu_alvo)
	{
	 	alu_alvo->alu_output = (alu_alvo->operando_x + alu_alvo->operando_y);

	}

	void AluSub(alu *alu_alvo)
	{
		alu_alvo->alu_output = (alu_alvo->operando_x - alu_alvo->operando_y);
	}

	void AluAnd(alu *alu_alvo)
	{
		alu_alvo->alu_output = (alu_alvo->operando_x & alu_alvo->operando_y);
	}

	void AluOr(alu *alu_alvo)
	{
		alu_alvo->alu_output = (alu_alvo->operando_x | alu_alvo->operando_y);
	}

	void AluXor(alu *alu_alvo)
	{
		alu_alvo->alu_output = (alu_alvo->operando_x ^ alu_alvo->operando_y);
	}

	void AluNot(alu *alu_alvo)
	{
		alu_alvo->alu_output = ~(alu_alvo->operando_x);
	}

	void AluZeroTest(alu *alu_alvo)
	{
		if (alu_alvo->operando_x == 0) alu_alvo->alu_output = 1;
		else alu_alvo->alu_output = 0;
		if(alu_alvo->operando_x > alu_alvo->operando_y) alu_alvo->alu_cc_bit2 = 1;
		if(alu_alvo->operando_x == alu_alvo->operando_y) alu_alvo->alu_cc_bit1 = 1;
	}

	void AluMult(alu *alu_alvo)
	{
		long long int xl, yl;
		xl = alu_alvo->operando_x;
		yl = alu_alvo->operando_y;
		alu_alvo->alu_output =  xl * yl;
	}

	void AluMultLong(alu *alu_alvo)
	{
		long long int xl, yl;

		xl = (unsigned int) alu_alvo->operando_x;
		yl = (unsigned int) alu_alvo->operando_y;
		alu_alvo->alu_output =  xl * yl;
	}

	void AluDiv(alu *alu_alvo)
	{
		alu_alvo->alu_output = (alu_alvo->operando_x / alu_alvo->operando_y);
	}

	void AluLeftShift(alu *alu_alvo)
	{
		alu_alvo->alu_output = (alu_alvo->operando_x << alu_alvo->operando_y);
	}

	void AluRightShift(alu *alu_alvo)
	{
		alu_alvo->alu_output = (alu_alvo->operando_x >> alu_alvo->operando_y);
	}

#include "instructions.h"

	/*
	 * Vetor de ponteiros de instrucoes para as operacoes definidas no MIPS
	 * Tais instrucoes estao indexadas pelo seu opcode
	 */
	ponteiro_instrucao instruction_set[2753] =
	{
		[0] = &InstSll,
		[1] = &InstNop, // <-
		[2] = &InstSrl,
		[3] = &InstSra,
		[4] = &InstSllv,
		[5] = &InstNop, //<-
		[6] = &InstSrlv,
		[8] = &InstJr,
		[9] = &InstJalr,
		[12] = &InstSyscall,
		[16] = &InstMfhi,
		[17] = &InstMthi,
		[18] = &InstMflo,
		[19] = &InstMtlo,
		[24] = &InstMult,
		[25] = &InstMultu,
		[26] = &InstDiv,
		[27] = &InstDivu,
		[32] = &InstAdd,
		[33] = &InstAddu,
		[34] = &InstSub,
		[35] = &InstSubu,
		[36] = &InstAnd,
		[37] = &InstOr,
		[38] = &InstXor,
		[39] = &InstNor,
		[42] = &InstSlt,
		[43] = &InstSltu,
		//no zero instructions:
		[128] = &InstJ,
		[192] = &InstJal,
		[256] = &InstBeq,
		[320] = &InstBne,
		[384] = &InstBlez,
		[448] = &InstBgtz,
		[512] = &InstAddi,
		[576] = &InstAddiu,
		[640] = &InstSlti,
		[704] = &InstSltiu,
		[768] = &InstAndi,
		[832] = &InstOri,
		[896] = &InstXori,
		[960] = &InstLui,
		[1792] = &InstMul,
		[2048] = &InstLb,
		[2112] = &InstLh,
		[2240] = &InstLw,
		[2304] = &InstLbu,
		[2368] = &InstLhu,
		[2560] = &InstSb,
		[2624] = &InstSh,
		[2752] = &InstSw,
	};


 	int clock_instruction[2753] =
	{
		[0] = 1,
		[2] = 1,
		[3] = 1,
		[4] = 1,
		[6] = 1,
		[8] = 2,
		[9] = 2,
		[12] = 1,
		[16] = 1,
		[17] = 1,
		[18] = 1,
		[19] = 1,
		[24] = 5,
		[25] = 5,
		[26] = 5,
		[27] = 5,
		[32] = 2,
		[33] = 2,
		[34] = 2,
		[35] = 2,
		[36] = 1,
		[37] = 1,
		[38] = 1,
		[39] = 1,
		[42] = 2,
		[43] = 2,
		//no zero instruction
		[128] = 2,
		[192] = 2,
		[256] = 2,
		[320] = 2,
		[384] = 2,
		[448] = 2,
		[512] = 2,
		[576] = 2,
		[640] = 2,
		[704] = 2,
		[768] = 1,
		[832] = 1,
		[896] = 1,
		[960] = 2,
		[1792] = 5,
		[2048] = 4,
		[2112] = 4,
		[2240] = 4,
		[2304] = 4,
		[2368] = 4,
		[2560] = 4,
		[2624] = 4,
		[2752] = 4,

	};

	void InstSllv(int fu_alvo)
	{
		/* seleciona operacao de deslocamento a esquerda */
		functional_unit[fu_alvo].fu_alu.alu_op = 9;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj & 31;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].vk;
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstSrlv(int fu_alvo)
	{
		/* seleciona operacao de deslocamento a direita */
		functional_unit[fu_alvo].fu_alu.alu_op = 10;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj & 31;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].vk;
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstAdd(int fu_alvo)
	{
		union_int_char tradutor_registrador;
		int index;
		/* operacao 0 == ADD */
		/* verifica overflow */
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].vk;
		if ((functional_unit[fu_alvo].fu_alu.operando_x > 0 && functional_unit[fu_alvo].fu_alu.operando_y > INT_MAX - functional_unit[fu_alvo].fu_alu.operando_x) ||
			(functional_unit[fu_alvo].fu_alu.operando_y > 0 && functional_unit[fu_alvo].fu_alu.operando_x > INT_MAX - functional_unit[fu_alvo].fu_alu.operando_y) ||
		 	(functional_unit[fu_alvo].fu_alu.operando_x < 0 && functional_unit[fu_alvo].fu_alu.operando_y < INT_MIN - functional_unit[fu_alvo].fu_alu.operando_x) ||
			(functional_unit[fu_alvo].fu_alu.operando_y < 0 && functional_unit[fu_alvo].fu_alu.operando_x < INT_MIN - functional_unit[fu_alvo].fu_alu.operando_y) )
		{
			for(index = 0; index < 32; index++)
			{
				if(register_stats[index].qi = fu_alvo)
				{
					/* converte o valor do registrador para inteiro */
					tradutor_registrador.valor_char.byte_32 = registradores[index][0];
					tradutor_registrador.valor_char.byte_24 = registradores[index][1];
					tradutor_registrador.valor_char.byte_16 = registradores[index][2];
					tradutor_registrador.valor_char.byte_8 = registradores[index][3];
					functional_unit[fu_alvo].fu_alu.alu_output  = tradutor_registrador.valor_inteiro;
				}
			}
		}
		else
		{
			/* se nao computa normal */
			functional_unit[fu_alvo].fu_alu.alu_op = 0;
			/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
			ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
		}

	}

	void InstAddu(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 0;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].vk;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstSub(int fu_alvo)
	{
		union_int_char tradutor_registrador;
		int index;
		/* operacao 1 == SUB */
		/* verifica overflow */
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].vk;
		if ((functional_unit[fu_alvo].fu_alu.operando_x > 0 && functional_unit[fu_alvo].fu_alu.operando_y > INT_MAX - functional_unit[fu_alvo].fu_alu.operando_x) ||
			(functional_unit[fu_alvo].fu_alu.operando_y > 0 && functional_unit[fu_alvo].fu_alu.operando_x > INT_MAX - functional_unit[fu_alvo].fu_alu.operando_y) ||
		 	(functional_unit[fu_alvo].fu_alu.operando_x < 0 && functional_unit[fu_alvo].fu_alu.operando_y < INT_MIN - functional_unit[fu_alvo].fu_alu.operando_x) ||
			(functional_unit[fu_alvo].fu_alu.operando_y < 0 && functional_unit[fu_alvo].fu_alu.operando_x < INT_MIN - functional_unit[fu_alvo].fu_alu.operando_y) )
		{
			for(index = 0; index < 32; index++)
			{
				if(register_stats[index].qi = fu_alvo)
				{
					/* converte o valor do registrador para inteiro */
					tradutor_registrador.valor_char.byte_32 = registradores[index][0];
					tradutor_registrador.valor_char.byte_24 = registradores[index][1];
					tradutor_registrador.valor_char.byte_16 = registradores[index][2];
					tradutor_registrador.valor_char.byte_8 = registradores[index][3];
					functional_unit[fu_alvo].fu_alu.alu_output  = tradutor_registrador.valor_inteiro;
				}
			}
		}
		else
		{
			/* se nao computa normal */
			functional_unit[fu_alvo].fu_alu.alu_op = 1;
			/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
			ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
		}
	}

	void InstSubu(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 1;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].vk;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstAnd(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 2;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].vk;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstOr(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 3;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].vk;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstXor(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 4;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].vk;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstNor(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 3;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].vk;
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
		functional_unit[fu_alvo].fu_alu.operando_x = functional_unit[fu_alvo].fu_alu.alu_output;
		functional_unit[fu_alvo].fu_alu.alu_op = 5;
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstSlt(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 1;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].vk;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
		if(functional_unit[fu_alvo].fu_alu.alu_output >= 0) functional_unit[fu_alvo].fu_alu.alu_output = 0;
		else functional_unit[fu_alvo].fu_alu.alu_output = 1;
	}

	void InstSltu(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 1;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].vk;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
		functional_unit[fu_alvo].fu_alu.alu_output = functional_unit[fu_alvo].fu_alu.alu_output < 0? 1 : 0;
		if(functional_unit[fu_alvo].fu_alu.operando_x < 0 || functional_unit[fu_alvo].fu_alu.operando_y < 0)
		{
			functional_unit[fu_alvo].fu_alu.alu_output = ((unsigned int)functional_unit[fu_alvo].fu_alu.operando_x < (unsigned int)functional_unit[fu_alvo].fu_alu.operando_y)? 1 : 0;
		}
	}

	void InstJalr(int fu_alvo)
	{
		/* calcular o endereco de retorno, pc + 4 */
		functional_unit[fu_alvo].fu_alu.alu_op = 0;
		functional_unit[fu_alvo].fu_alu.operando_x = program_counter;
		functional_unit[fu_alvo].fu_alu.operando_y = 0;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstMult(int fu_alvo)
	{
		/* lo hi?*/
		functional_unit[fu_alvo].fu_alu.alu_op = 11;
		functional_unit[fu_alvo].fu_alu.operando_x = (unsigned int)reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = (unsigned int)reservation_station[fu_alvo].vk;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstMultu(int fu_alvo)
	{
		/* lo hi?*/
		functional_unit[fu_alvo].fu_alu.alu_op = 7;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].vk;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstDiv(int fu_alvo)
	{
		/* lo hi?*/
		functional_unit[fu_alvo].fu_alu.alu_op = 8;
		functional_unit[fu_alvo].fu_alu.operando_x = (unsigned int)reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = (unsigned int)reservation_station[fu_alvo].vk;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstDivu(int fu_alvo)
	{
		/* lo hi?*/
		functional_unit[fu_alvo].fu_alu.alu_op = 8;
		functional_unit[fu_alvo].fu_alu.operando_x = (unsigned int)reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = (unsigned int)reservation_station[fu_alvo].vk;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstJr(int fu_alvo)
	{
		/*jump register*/
		/* calular o end para o pulo */

		//functional_unit[fu_alvo].fu_alu.alu_op = 7;
		functional_unit[fu_alvo].fu_alu.alu_output = reservation_station[fu_alvo].vj;
		//functional_unit[fu_alvo].fu_alu.operando_y = 4;
		//ExecutarAlu(&functional_unit[fu_alvo].fu_alu);



	}

	void InstMfhi(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_output = reservation_station[fu_alvo].vj;
	}

	void InstMthi(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_output = reservation_station[fu_alvo].vj;
	}

	void InstMflo(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_output = reservation_station[fu_alvo].vj;
	}

	void InstMtlo(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_output = reservation_station[fu_alvo].vj;
	}

	void InstSll(int fu_alvo)
	{
		/* seleciona operacao de deslocamento a esquerda */
		functional_unit[fu_alvo].fu_alu.alu_op = 9;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vk;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].a;
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstSrl(int fu_alvo)
	{
		/* seleciona operacao de deslocamento a direita */
		functional_unit[fu_alvo].fu_alu.alu_op = 10;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vk;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].a;
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstSra(int fu_alvo)
	{
		/* mudar a saida para double gerou algumas incompatibilidades, cuidar disso */
		int index;
		functional_unit[fu_alvo].fu_alu.alu_op = 10;
		int alu_output_int;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vk;
		for(index = 0; index < reservation_station[fu_alvo].a; index++)
		{
			functional_unit[fu_alvo].fu_alu.operando_y = 1;
			ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
			if(functional_unit[fu_alvo].fu_alu.operando_x & 4294967296)
			{
				alu_output_int = functional_unit[fu_alvo].fu_alu.alu_output;
				alu_output_int = alu_output_int | 4294967296;
				//functional_unit[fu_alvo].fu_alu.alu_output = functional_unit[fu_alvo].fu_alu.alu_output | 4294967296;
				functional_unit[fu_alvo].fu_alu.alu_output = alu_output_int;
			}
			functional_unit[fu_alvo].fu_alu.operando_x = functional_unit[fu_alvo].fu_alu.alu_output;
		}
	}

	void InstBeq(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 6;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].vk;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
		if(functional_unit[fu_alvo].fu_alu.alu_cc_bit1) functional_unit[fu_alvo].fu_alu.alu_output = 1;
		else functional_unit[fu_alvo].fu_alu.alu_output = 0;
		//functional_unit[fu_alvo].fu_alu.alu_output = functional_unit[fu_alvo].fu_alu.alu_output == 0;
	}

	void InstBne(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 6;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].vk;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
		if(functional_unit[fu_alvo].fu_alu.alu_cc_bit1) functional_unit[fu_alvo].fu_alu.alu_output = 0;
		else functional_unit[fu_alvo].fu_alu.alu_output = 1;
	}

	void InstAddi(int fu_alvo)
	{
		union_int_char tradutor_registrador;
		int index;
		/* operacao 0 == add */
		/* verifica overflow */
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].a;
		if ((functional_unit[fu_alvo].fu_alu.operando_x > 0 && functional_unit[fu_alvo].fu_alu.operando_y > INT_MAX - functional_unit[fu_alvo].fu_alu.operando_x) ||
			(functional_unit[fu_alvo].fu_alu.operando_y > 0 && functional_unit[fu_alvo].fu_alu.operando_x > INT_MAX - functional_unit[fu_alvo].fu_alu.operando_y) ||
		 	(functional_unit[fu_alvo].fu_alu.operando_x < 0 && functional_unit[fu_alvo].fu_alu.operando_y < INT_MIN - functional_unit[fu_alvo].fu_alu.operando_x) ||
			(functional_unit[fu_alvo].fu_alu.operando_y < 0 && functional_unit[fu_alvo].fu_alu.operando_x < INT_MIN - functional_unit[fu_alvo].fu_alu.operando_y) )
		{
			for(index = 0; index < 32; index++)
			{
				if(register_stats[index].qi = fu_alvo)
				{
					/* converte o valor do registrador para inteiro */
					tradutor_registrador.valor_char.byte_32 = registradores[index][0];
					tradutor_registrador.valor_char.byte_24 = registradores[index][1];
					tradutor_registrador.valor_char.byte_16 = registradores[index][2];
					tradutor_registrador.valor_char.byte_8 = registradores[index][3];
					functional_unit[fu_alvo].fu_alu.alu_output  = tradutor_registrador.valor_inteiro;
				}
			}
		}
		else
		{
			/* se nao computa normal */
			functional_unit[fu_alvo].fu_alu.alu_op = 0;
			/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
			ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
		}
	}

	void InstAddiu(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 0;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].a;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstSlti(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 1;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].a;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
		if(functional_unit[fu_alvo].fu_alu.alu_output >= 0) functional_unit[fu_alvo].fu_alu.alu_output = 0;
		else functional_unit[fu_alvo].fu_alu.alu_output = 1;
	}

	void InstSltiu(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 1;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].a;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
		functional_unit[fu_alvo].fu_alu.alu_output = functional_unit[fu_alvo].fu_alu.alu_output < 0? 1 : 0;
		if(functional_unit[fu_alvo].fu_alu.operando_x < 0 || functional_unit[fu_alvo].fu_alu.operando_y < 0)
		{
			functional_unit[fu_alvo].fu_alu.alu_output = ((unsigned int)functional_unit[fu_alvo].fu_alu.operando_x < (unsigned int)functional_unit[fu_alvo].fu_alu.operando_y)? 1 : 0;
		}
	}

	void InstAndi(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 2;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].a;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstOri(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 3;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].a;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstXori(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 4;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].a;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstBlez(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 6;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vk;
		functional_unit[fu_alvo].fu_alu.operando_y = 0;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
		if(!functional_unit[fu_alvo].fu_alu.alu_cc_bit2) functional_unit[fu_alvo].fu_alu.alu_output = 1;
	}

	void InstBgtz(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 6;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vk;
		functional_unit[fu_alvo].fu_alu.operando_y = 0;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
		functional_unit[fu_alvo].fu_alu.alu_output = functional_unit[fu_alvo].fu_alu.alu_cc_bit2;
	}

	void InstLui(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 9;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].a;
		functional_unit[fu_alvo].fu_alu.operando_y = 16;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstLh(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 0;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].a;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstLb(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 0;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].a;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstLw(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 0;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].a;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstLbu(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 0;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].a;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstLhu(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 0;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].a;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstSb(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 0;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].a;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstSh(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 0;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].a;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstSw(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 0;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].a;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstJ(int fu_alvo)
	{
		/* calular o end para o pulo */
		functional_unit[fu_alvo].fu_alu.alu_op = 7;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].a - 1;
		functional_unit[fu_alvo].fu_alu.operando_y = 4;
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstJal(int fu_alvo)
	{
		/* calcular o endereco de retorno, pc + 4 */
		functional_unit[fu_alvo].fu_alu.alu_op = 0;
		functional_unit[fu_alvo].fu_alu.operando_x = program_counter;
		functional_unit[fu_alvo].fu_alu.operando_y = 0;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

	void InstSyscall(int fu_alvo)
	{
		/* syscall so realiza o exit */
		if(EstacaoVazia())
		{
			flag_halt = 1;
		}
	}

	void InstNop(int fu_alvo)
	{
		printf("\nNO OPERATION\n");
	}

	void InstMul(int fu_alvo)
	{
		functional_unit[fu_alvo].fu_alu.alu_op = 7;
		functional_unit[fu_alvo].fu_alu.operando_x = reservation_station[fu_alvo].vj;
		functional_unit[fu_alvo].fu_alu.operando_y = reservation_station[fu_alvo].vk;
		/* Faz a ula executar uma operacao primitiva e coloca o resultado no output da ula*/
		ExecutarAlu(&functional_unit[fu_alvo].fu_alu);
	}

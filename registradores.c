#include <stdio.h>
#include <stdlib.h>

#include "registradores.h"


	unsigned char registradores[34][4] =
	{
		[0 ... 33] = {[0 ... 3] = 0}
	};

	void InicializaRegistradores()
	{
		union_int_char valor_inicial;

			valor_inicial.valor_inteiro = DATA_SEG;
			registradores[$GP][0] = valor_inicial.valor_char.byte_32;
			registradores[$GP][1] = valor_inicial.valor_char.byte_24;
			registradores[$GP][2] = valor_inicial.valor_char.byte_16;
			registradores[$GP][3] = valor_inicial.valor_char.byte_8;

			valor_inicial.valor_inteiro = MEM_SIZE;
			registradores[$SP][0] = valor_inicial.valor_char.byte_32;
			registradores[$SP][1] = valor_inicial.valor_char.byte_24;
			registradores[$SP][2] = valor_inicial.valor_char.byte_16;
			registradores[$SP][3] = valor_inicial.valor_char.byte_8;
	}

	void PrintaRegistradores()
	{
		int index;
		union_int_char char_para_int;

		for(index = 0; index < 34; index++)
		{
			/*
			printf("\n[%2d]: %x %x %x %x", index, registradores[index][0],
												  registradores[index][1],
												  registradores[index][2],
												  registradores[index][3]);
			*/
			char_para_int.valor_char.byte_32 = registradores[index][0];
			char_para_int.valor_char.byte_24 = registradores[index][1];
			char_para_int.valor_char.byte_16 = registradores[index][2];
			char_para_int.valor_char.byte_8  = registradores[index][3];
			if(index % 6 == 0) printf("\n");
			printf("[%3d]: %3u\t", index, char_para_int.valor_inteiro);
		}
	}

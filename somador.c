/*
 * Modulo para implementacao do somador do program counter
 * presente no fetch do pipeline
 */
#include <stdio.h>
#include "somador.h"

	/*
	 * Funcao que incrementa a variavel program_counter em 4
	 * Armazena no registrador intermediario pc_plus_4
	 */
	void IncrementarPc()
	{
		pc_plus_4 = program_counter + 4;
	}

/*
 * Modulo para hash
 * Utilizado para facilitar o acesso de variaveis e labels
 */
#include <stdio.h>
#include "hash.h"

	/*
	 * Funcao de Hash
	 * Nao tenho muita certeza sobre a capacidade injetiva dessa funcao
	 * Qualquer problema mudar o mod
	 */
	unsigned int Hash(char* symbol)
	{
	   unsigned int h = 0;
	   char c;
	   while(c = *symbol++) h = h*9^c;
	   return h%1000;
	}

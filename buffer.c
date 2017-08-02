/*
 * Modulo para traducao de valores e escrita no buffer global
 */

#include <stdio.h>
#include "buffer.h"
#include <string.h>

	/*
	 * Buffer global, utilizado para as traducoes
	 * Toda instrucao eh transformada em palavra e armezanada neste buffer
	 */
	char buffer[33] = {[0 ... 32] = '0', [32] = '\0'};

	/*
	 * Funcao que traduz um inteiro para binario e escreve no buffer
	 *
	 * @param
	 * value: o valor do inteiro a ser escrito
	 * index: posicao no buffer a ser escrita
	 *
	 * @resticao
	 * nao funfa para negativos
	 */
	void Itob(int value, int index)
 	{
		if (value < 0)
		{
			value = value & 65535;
			while(value && index >= 0)
			{
				buffer[index--] = (value & 0x1) ? '1':'0';
				value >>= 1;
			}
		}
		else
		{
			while(value > 0)
			{
				buffer[index--] = (value & 1) + '0'; //bit menos significativo AND 1 dpois converte em char
				value = (value >> 1); //passa pro prox bit
			}
		}

	 }

	 /*
	  * Funcao para exibir o buffer
	  * So printa ele mesmo e boa
	  */
	 void PrintBuffer()
	 {
		 printf("\n%s", buffer);
	 }

	 /*
	  * Funcao para remover residuos do buffer
	  * Previne a sobreposicao de escrita no buffer
	  * Por conveniencia escreve '0' nele
	  */
	 void LimpaBuffer()
	 {
		 memset(buffer,'0', 32);
	 }

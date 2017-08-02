/*
 * Modulo para implementacao do barramento que liga a memoria ao processador
 * possui largura de 4 bytes que e o tamanho de uma palavra
 */
 	#include "barramento.h"

	unsigned char barramento_mp_processador[4];

	/*
	 * Funcao para colocar um valor inteiro no barramento que liga a memoria
	 * principal ao processador
	 * Utiliza bit field para a conversao do valor inteiro em char
	 *
	 * @param
	 * value: o valor a ser escrito no barramento
	 */
	void JogaNoBarramento(unsigned char *value)
	{
		barramento_mp_processador[0] = value[0];
		barramento_mp_processador[1] = value[1];
		barramento_mp_processador[2] = value[2];
		barramento_mp_processador[3] = value[3];
	}

	/*
	 * Funcao para pegar um valor do barramento
	 *
	 * @returns
	 * retorna o valor escrito no barramento
	 */
	unsigned char* PegaNoBarramento()
	{
		return (barramento_mp_processador);
	}

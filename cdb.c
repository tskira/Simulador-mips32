/*
 * Modulo para implementacao do barramento interno do processador, o cdb
 * possui largura de 4 bytes que e o tamanho de uma palavra
 */
 	#include "cdb.h"

	unsigned char cdb[4];

	/*
	 * Funcao para colocar um valor inteiro no cdb
	 * Utiliza bit field para a conversao do valor inteiro em char
	 *
	 * @param
	 * value: o valor a ser escrito no barramento
	 */
	void JogaNoCdb(unsigned char *value)
	{
		cdb[0] = value[0];
		cdb[1] = value[1];
		cdb[2] = value[2];
		cdb[3] = value[3];
	}

	/*
	 * Funcao para pegar um valor do barramento
	 *
	 * @returns
	 * retorna o valor escrito no barramento
	 */
	unsigned char* PegaNoCdb()
	{
		return (cdb);
	}

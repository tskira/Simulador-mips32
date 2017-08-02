#ifndef MEMORIA_H_
#define MEMORIA_H_

//tamanho real: 536 870 912 (2²⁹)
#define MEM_SIZE 536870912

//tamaho real: 67 108 864 (2²⁶)
#define DATA_SEG 67108864 
#define TEXT_SEG 0

#include "so.h"


	/*
	 * Estrutura para decompor inteiro em char de um jeito pro-player
	 * Usar shift bit ou typecast e coisa de fraco sem talento
	 */
	typedef struct decompor_palavra
	{
		unsigned char byte_8 : 8;
		unsigned char byte_16: 8;
		unsigned char byte_24: 8;
		unsigned char byte_32: 8;
	} palavra_em_bytes;

	typedef union palavra_int_char
	{
		unsigned int valor_inteiro;
		palavra_em_bytes valor_char;
	} union_int_char;

	extern unsigned char *memoria_principal;
	extern unsigned char *palavra;

	void InicializaMemoria();
	void Read(int);
	void Write(int);
	void PrintMemoria();

#endif

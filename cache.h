/*
 * Modulo que implementa a cache do simulador
 * Mapeamento direto
 * Tamanho 16B x 2KB
 * Politica de subistituição: write back
 */
#ifndef CACHE_H_
#define CACHE_H_

#include "memoria.h"
#include "cdb.h"
#include "so.h"

/*
 * Tamanho da linha da cache
 * Valor default 16
 */
#define LINE_SIZE 16

/* Numero de linhas da cache
 * Valor default 2048
 */
#define CACHE_SIZE 2048

#define FALSE 0
#define TRUE 1

#define CACHE_TEXT 0
#define CACHE_DATA 1

	/*
	 * Aqui e onde a magica do C acontece
	 * Magica nao se explica, apenas se sente
	 */
	typedef struct decompor
	{
		unsigned byte : 4;
		unsigned linha : 11;
		unsigned tag: 14;
	} tag_linha_byte;

	/* wtf */
	typedef union decompor_endereco
	{
		unsigned int endereco_inteiro;
		tag_linha_byte endereco_mapeado;
	} endereco_decomposto;

	typedef struct line
	{
		unsigned int tag_da_linha;
		unsigned int flag_atualizar;
		unsigned char bytes_da_linha[LINE_SIZE];
	} linha_cache;

	extern linha_cache memoria_cache[2][CACHE_SIZE];

	void ReadCache(int);
	void WriteCache(int);
	void SubstituirCache(int);

#endif

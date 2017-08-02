#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "so.h"

	unsigned char inteiro_em_char[4];
	int char_em_inteiro;

	/*
	 * Funcao para carregar um programa na memoria
	 *
	 * @param
	 * nome_arquivo: é o nome do programa a ser carregado
	 */

	void CarregarArquivo(char *nome_arquivo)
	{
		int instrucao_32bits;
		union_int_char decompor_instrucao;
		int posicao_memoria = 0;
		FILE *arquivo_alvo = fopen(nome_arquivo, "r");

		printf("\n #### DATA #### \n");
		while(fread(&instrucao_32bits, sizeof(int), 1, arquivo_alvo) &&
		 	  ftell(arquivo_alvo) <= DOT_TEXT)
		{
			decompor_instrucao.valor_inteiro = instrucao_32bits;
			palavra[0] = decompor_instrucao.valor_char.byte_32;
			palavra[1] = decompor_instrucao.valor_char.byte_24;
			palavra[2] = decompor_instrucao.valor_char.byte_16;
			palavra[3] = decompor_instrucao.valor_char.byte_8;
			JogaNoBarramento(palavra);
			Write((DATA_SEG + posicao_memoria));
			posicao_memoria += 4;
			printf("\n%d", instrucao_32bits);
		}
		printf("\n #### TEXT #### \n");
		posicao_memoria = 0;
		fseek(arquivo_alvo, DOT_TEXT, SEEK_SET);
		while(fread(&instrucao_32bits, sizeof(int), 1, arquivo_alvo))
		{
			decompor_instrucao.valor_inteiro = instrucao_32bits;
			palavra[0] = decompor_instrucao.valor_char.byte_32;
			palavra[1] = decompor_instrucao.valor_char.byte_24;
			palavra[2] = decompor_instrucao.valor_char.byte_16;
			palavra[3] = decompor_instrucao.valor_char.byte_8;
			JogaNoBarramento(palavra);
			Write((TEXT_SEG + posicao_memoria));
			posicao_memoria += 4;
			printf("\n%d", instrucao_32bits);
		}
		fclose(arquivo_alvo);
	}

	/*
	 * Metodo para conversao de inteiro em char
	 *
	 * value: o valor a ser convertido
	 */
	unsigned char *Itoc(int value)
	{

		int iterator;
		for(iterator = 0; iterator < 4; iterator++)
		{
			inteiro_em_char[iterator] = (unsigned char)(value >> (32 - (8 * (iterator + 1)))) & 0xFF; //cheat
		}

		return inteiro_em_char;
	}

	/*
	 * Funcao para reverter o vetor de 4 char em um int
	 *
	 * @param
	 * char_alvo: a palavra a ser desconvertida
	 */
	int Ctoi(char *char_alvo)
	{
		char_em_inteiro = (char_alvo[0] << 24) |
		 				  (char_alvo[1] << 16) |
						  (char_alvo[2] << 8) |
						   char_alvo[3];
		return char_em_inteiro;
	}

	/*
	 * Funcao para printar a cache
	 * So de zoa mesmo
	 */
	void PrintCache()
	{
		int index_i;
		int index_j;

		printf("\n\n ### TEXT CACHE ### \n\n");
		for(index_i = 0; index_i < CACHE_SIZE; index_i++)
		{
			printf("\n[%2d][%2d]", memoria_cache[CACHE_TEXT][index_i].flag_atualizar ,index_i);
			for(index_j = 0; index_j < LINE_SIZE; index_j++)
			{
				printf("%x ", memoria_cache[CACHE_TEXT][index_i].bytes_da_linha[index_j]);
			}
		}

		printf("\n\n ### DATA CACHE ### \n\n");
		for(index_i = 0; index_i < CACHE_SIZE; index_i++)
		{
			printf("\n[%2d][%2d]", memoria_cache[CACHE_DATA][index_i].flag_atualizar ,index_i);
			for(index_j = 0; index_j < LINE_SIZE; index_j++)
			{
				printf("%x ", memoria_cache[CACHE_DATA][index_i].bytes_da_linha[index_j]);
			}
		}
	}

	/*
	 * Metodo para printar a memoria, so de zoa mesmo
	 */
	void PrintMemoria()
	{
		int index = 0;
		printf("\n #### TEXT #### \n");
		for (index = 0 ; index < MEM_SIZE ; index++)
		{
			if(index == 32) printf("\n\n #### DATA ####");
			if(index % 4 == 0) printf("\n");
			(printf("\n[%3d] : %x", index, *(memoria_principal + index)));
		}
		printf("\n");
	}

	/*
	 * Funcao para inicializar alguns componentes
	 */
	void CarregarBios(char *codigo_mips)
	{
		InicializaMemoria();
		GerarObjeto(codigo_mips);
		CarregarArquivo("output");
		InicializaRegistradores();

	}

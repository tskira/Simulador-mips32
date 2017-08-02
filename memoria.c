/*
 * Modulo que implementa a memoria do simulador
 * Tomando o MIPS como modelo, cade palavra tem 32 bits = 4 char
 * A memoria segue o modele da pg 21 do manual
 * O tamanho a ser utilizado sera 512mb
 * Cada celula tera o tamanho de 8 bits = 1 char
 * Serao 64mb posicoes enderecaveis na memoria
 * A memoria esta em big endian
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memoria.h"

	unsigned char *memoria_principal;
	unsigned char *palavra;

	/*
	 * Funcao para alocacao de espaco para a memoria e
	 * Para o palavra auxiliar
	 */
	void InicializaMemoria()
	{
		memoria_principal = malloc( MEM_SIZE * sizeof(char));
		palavra = malloc(4 * sizeof(char));
	}

	/*
	 * Funcao para leitura na memoria
	 * A leitura sera realizada por palavra
	 * Logo cada leitura devolve os 4bytes consecutivos a partir
	 * Do endereco alvo
	 *
	 * @param
	 * endereco_alvo: posicao da memoria que deseja se ler
	 *
	 * @returns
	 * palavra: a sequencia lida
	 */
	void Read(int endereco_alvo)
	{
		int index;

		if (endereco_alvo % 4 == 0)
		{
			for (index = 0; index < 4; index++)
			{
				palavra[index] = memoria_principal[endereco_alvo + index];
			}
			JogaNoBarramento(palavra);
		}
		else
		{
			printf("\nPosicao invalida");
		}

	}

	/*
	 * Funcao para escrita na memoria
	 * Como na arquitetura mips as palavras sao de 32bits
	 * Uma escrita consiste no armazenamento de 4bytes consecutivos em
	 * Determinado endereco
	 * O valor de entrada e convertindo em unsigned char, e depois e	 salvo
	 *
	 * @param
	 * endereco_alvo: a posicao da memoria onde deseja iniciar uma escrita
	 * valor: o valor em inteiro a ser escrito
	 */
	void Write(int endereco_alvo)
	{
		int index;

		if(endereco_alvo % 4 == 0)
		{
			for (index = 0; index < 4; index++)
			{
				memoria_principal[endereco_alvo + index] = barramento_mp_processador[index];
			}
		}
		else printf("\nPosicao invalida");
	}

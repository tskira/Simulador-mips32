#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache.h"

	linha_cache memoria_cache[2][CACHE_SIZE] =
	{
		{[0 ... (CACHE_SIZE - 1)] = { .tag_da_linha = -1}},
		{[0 ... (CACHE_SIZE - 1)] = {.tag_da_linha = -1}}
	};

	/*
	 * Funcao para ler dados na cache
	 * Se o dado buscado estiver na cache procede normal
	 * Se nao aplica o algoritmo de substituicao de dados da cache
	 * Este algoritmo verifica a flag atualizar
	 * Se estiver setado em TRUE algum dado desta linha foi modificado e deve
	 * Ser atualizado na MP
	 *
	 * @param
	 * endereco_alvo: endereco buscado
	 *
	 * @returns
	 * coloca o valor do endereco alvo no cdb
	 */
	void ReadCache(int endereco_alvo)
	{
		endereco_decomposto alvo_decomposto;
		int index;
		int cache_select;

		alvo_decomposto.endereco_inteiro = endereco_alvo;
		if(endereco_alvo % 4 != 0) return;
		if (endereco_alvo < DATA_SEG) cache_select = CACHE_TEXT;
		else cache_select = CACHE_DATA;
		if(memoria_cache[cache_select][alvo_decomposto.endereco_mapeado.linha].tag_da_linha !=
			 			 alvo_decomposto.endereco_mapeado.tag)
		{
			/* miss */
			//printf("\n MISS, aplicando algoritmo de substituicao");my_type
			printf("\nMISS NA CACHE, ENDERECO: %d\n", endereco_alvo);

			SubstituirCache(endereco_alvo);
		}
		for (index = 0; index < 4; index++)
		{
			palavra[index] = memoria_cache[cache_select][alvo_decomposto.endereco_mapeado.linha].
							 bytes_da_linha[alvo_decomposto.endereco_mapeado.byte + index];
		}
		JogaNoCdb(palavra);
	}

	/*
	 * Funcao para escrever um valor na cache
	 * Recebe o endereco e o valor a ser escrito
	 * Atualiza-se o valor da flag_atualizar para TRUE
	 * Utiliza a tecnica fodona para converter o inteiro e char
	 * Escreve nos 4 respectivos bytes alvo
	 * Considera que o valor a ser escrito ja esta no CDB
	 *
	 * @param
	 * endereco_alvo: o endereco da memoria principal onde o valor deveria ser
	 * escrito
	 * valor: o inteiro (representando uma instracao ou valor) a ser escrito
	 */
	void WriteCache(int endereco_alvo)
	{
		endereco_decomposto alvo_decomposto;
		int index;
		int cache_select;

		if (endereco_alvo % 4 != 0) return;
		/* Seleciona a cache respectiva ao endereco (TEXT ou DATA) */
		if (endereco_alvo < DATA_SEG) cache_select = CACHE_TEXT;
		else cache_select = CACHE_DATA;
		alvo_decomposto.endereco_inteiro = endereco_alvo;
		if(memoria_cache[cache_select][alvo_decomposto.endereco_mapeado.linha].tag_da_linha !=
			 			 alvo_decomposto.endereco_mapeado.tag)
		{
			/* miss */
			//printf("\n MISS, aplicando algoritmo de substituicao");
			SubstituirCache(endereco_alvo);
		}
		memoria_cache[cache_select][alvo_decomposto.endereco_mapeado.linha].flag_atualizar = TRUE;
		/* testando tecninca boa pra converter inteiro em char: */
		for(index = 0; index < 4; index++)
		{
			memoria_cache[cache_select][alvo_decomposto.endereco_mapeado.linha]
						 .bytes_da_linha[alvo_decomposto.endereco_mapeado.byte + index] =
						 PegaNoCdb()[index];
		}

	}

	/*
	 * Algoritmo de substituicao da cache
	 * Verifica se houve alguma alteracao na linha da cache a ser atualizado
	 * Se sim, entao inicia se o processo de atualizacao da MP:
	 * O bloco (tag da linha + linha da cache) e escrito na MP
	 * O bloco que contem o endereco alvo e escrito na cache, na sua respectiva
	 * linha
	 * A flag_atualizar e setado em FALSE
	 * Atualiza-se o campo tag da linha da cache
	 *
	 * @param
	 * endereco_bloco_sub: e o endereco alvo da memoria que deve ser substituido
	 * na cache. Pelo mapeamento o bloco inteiro deve ser substituido
	 */
	void SubstituirCache(int endereco_bloco_sub)
	{
		endereco_decomposto alvo_decomposto;
		int index;
		int cache_select;

		alvo_decomposto.endereco_inteiro = endereco_bloco_sub;
		if (endereco_bloco_sub < DATA_SEG) cache_select = CACHE_TEXT;
		else cache_select = CACHE_DATA;
		/* algum dado foi modificado na cache precisa ser atualizado na MP */
		for(index = 0; index < 16; index += 4)
		{
			if(memoria_cache[cache_select][alvo_decomposto.endereco_mapeado.linha].flag_atualizar)
			{
				/*
				 * O endereco do bloco na linha da cache alvo precisa ser recomposto
				 * Depois atualiza-se a MP com os valores do bloco que ja estava
				 */
				palavra[0] = memoria_cache[cache_select][alvo_decomposto.endereco_mapeado.linha].bytes_da_linha[index];
				palavra[1] = memoria_cache[cache_select][alvo_decomposto.endereco_mapeado.linha].bytes_da_linha[index + 1];
				palavra[2] = memoria_cache[cache_select][alvo_decomposto.endereco_mapeado.linha].bytes_da_linha[index + 2];
				palavra[3] = memoria_cache[cache_select][alvo_decomposto.endereco_mapeado.linha].bytes_da_linha[index + 3];
				JogaNoBarramento(palavra);
				Write((memoria_cache[cache_select][alvo_decomposto.endereco_mapeado.linha].tag_da_linha * 32768) +
								  (alvo_decomposto.endereco_mapeado.linha * 16) +
								  (index));
			}
			/*
			 * Ler os valores da MP e escrever na referente linha da cache
			 * Neste momento deveria estar sendo utilzada as funcoes WRITE e READ
			 * da memoria.c
			 * Se lembrar depois mudar isso
			 */
			Read((alvo_decomposto.endereco_mapeado.tag * 32768) +
							  (alvo_decomposto.endereco_mapeado.linha * 16) +
							  (index));
			palavra = PegaNoBarramento();
			memoria_cache[cache_select][alvo_decomposto.endereco_mapeado.linha]
									   .bytes_da_linha[index] = palavra[0];
			memoria_cache[cache_select][alvo_decomposto.endereco_mapeado.linha]
									   .bytes_da_linha[index + 1] = palavra[1];
			memoria_cache[cache_select][alvo_decomposto.endereco_mapeado.linha]
									   .bytes_da_linha[index + 2] = palavra[2];
			memoria_cache[cache_select][alvo_decomposto.endereco_mapeado.linha]
									   .bytes_da_linha[index + 3] = palavra[3];

		}
		/* atualiza flag e tag da linha da cache */
		memoria_cache[cache_select][alvo_decomposto.endereco_mapeado.linha].flag_atualizar = FALSE;
		memoria_cache[cache_select][alvo_decomposto.endereco_mapeado.linha].tag_da_linha =
					  alvo_decomposto.endereco_mapeado.tag;
		//printf("\n Cache atualizada");
	}

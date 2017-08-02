/*
 * Modulo para definicao de algumas estruturas globais par ao assembler
 */
#include <stdio.h>
#include <string.h>

#include "estruturas.h"

	/*
	 * Tabela que armazena o endereco dos rotulos definidos
	 */
	int tabela_rotulos[1000] = {[0 ... 999] = -1};

	/*
	 * Tabela que armazena o endereco das variaveis definidas
	 */
	 int tabela_variaveis[1000] = {[0 ... 999] = -1};

	/*
	 * Vetor para amazenar o codigo gerado na primeira traducao
	 */
	pre_traducao segunda_traducao[100];

	/* Para armazenar o numero de variaveis declaradas, numero de linhas da segunda_traducao e numero de linhas da parte texto*/
	int numero_variaveis;
	int numero_linhas;
	int text_linhas;
	int pre_posicao_data, pos_posicao_data;

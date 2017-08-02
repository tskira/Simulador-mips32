#ifndef ESTRUTURAS_H_
#define ESTRUTURAS_H_


	/*
	 * Estrutura para armazenamento da primeira analise da traducao
	 * A traducao ocorrera em duas etapas para resolver conflitos de
	 * pos referencias a rotulos
	 *
	 * referencia_indefinida: se o rotulo ainda nao foi definido es
	 * tara setado em -1, caso contrario tera o endereco do rotulo
	 * primeira_traducao: armazena a instrucao gerada pela primeira
	 * traducao
	 */
	typedef struct primeira_traducao
	{
		int referencia_indefinida;
		char primeira_traducao[33];
	} pre_traducao;

	extern int tabela_rotulos[1000];
	extern int tabela_variaveis[1000];
	extern pre_traducao segunda_traducao[100];
	extern int numero_variaveis;
	extern int numero_linhas;
	extern int text_linhas;
	extern int pre_posicao_data, pos_posicao_data;

#endif

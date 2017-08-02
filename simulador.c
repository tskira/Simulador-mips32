/*
 * Trabalho de Arq II
 * Aluno Thiago Kira
 */

#include <stdio.h>
#include <argp.h>
#include <string.h>

#include "memoria.h"
#include "buffer.h"
#include "hash.h"
#include "estruturas.h"
#include "assembler.h"
#include "so.h"
#include "cache.h"
#include "registradores.h"
#include "barramento.h"
#include "cdb.h"
#include "processador.h"
#include "somador.h"
#include "pipeline.h"
#include "fila.h"
#include "clock.h"


struct arguments
{
	char *args[2];
	int funcao;
};


static struct argp_option options[] =
{
	{0, 'd', " mips_input numero_ciclos ", OPTION_ARG_OPTIONAL, "Executa o codigo em modo detalhado \nmips_input: nome do arquivo contendo codigo mips a ser executado\nnumero_ciclos: o numero de ciclos a executar\nEnter para seguir para o prox. estagio "},
	{0, 's', " mips_input ", OPTION_ARG_OPTIONAL, "Executa o codigo em modo simplificado \nmips_input: nome do arquivo com codigo mips a ser executado"},
	{0}
};

static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;
	switch(key)
	{
		case 'd':
		{
			arguments->funcao = 0;
			break;
		}
		case 's':
		{
			arguments->funcao = 1;
			break;
		}

		case ARGP_KEY_ARG:
		  if (state->arg_num > 2)
		  {
		  	argp_usage(state);
		  }
		  arguments->args[state->arg_num] = arg;
		  break;

		  /*
		case ARGP_KEY_END:
		  if (state->arg_num != 0 )
		  {
		  	argp_usage (state);
		  }
		  break;
		  */
		default:
		  return ARGP_ERR_UNKNOWN;

	}
	return 0;
}

static struct argp argp = {options, parse_opt, 0, 0};

int main (int argc, char **argv)
{
	struct arguments arguments;
	int count = 0;
	char c;

	arguments.args[0] = "";
	arguments.args[1] = "";

	argp_parse(&argp, argc, argv, OPTION_ARG_OPTIONAL, 0, &arguments);

	switch(arguments.funcao)
	{
		case 0:
		{
			#define D_
			CarregarBios(arguments.args[0]);
			printf("\n");
			int max;
			max = atoi(arguments.args[1]);
			if(max == 0) max = 1000;

			while((c = getchar()) == '\n')
			{
				int index;
				if(flag_halt) break;
				if(clocks == max) break;

				switch (count % 5)
				{
					case (4):
					{
						printf("\n ###### FETCH ######\n");
						printf("\nFLAG STALL: %d\n", flag_stall);
						Fetch();
						printf("\nRI: %d\nPC: %d\n", inst.valor_inteiro, program_counter);
						break;
					}

					case(3):
					{
						printf("\n ###### DECODE ######\n");
						printf("\nFlag Desinfileira: %d", flag_desinfileira);
						Decode();
						printf("\n");
						for(index = instruction_queue.inicio; index < instruction_queue.tamanho; (index = index + 1) % 6)
						{
							printf("%d | ", instruction_queue.elementos[index]);
						}
						printf("\nINSTRUCTION QUEUE SIZE: %d\n", instruction_queue.tamanho);
						printf("\nVALOR DESINFILEIRADO: %d", inst_rij_decomposta.instrucao_inteiro);
						break;
					}

					case(2):
					{
						printf("\n ###### EXECUTION ######\n");
						Execution();
						printf("\n ESTACOES DE RESERVA \n");
						PrintEstacao();
						break;
					}

					case(1):
					{
						printf("\n \n###### MEMORY ACESS ######\n");
						MemoryAcess();
						printf("\nAtualizou o pc");
						break;
					}


					case(0):
					{
						printf("\n \n###### WRITE BACK ######\n");
						int a;
						WriteBack();
						printf("\n REGISTRADORES \n");
						PrintaRegistradores();
						printf("\n\nREGISTER STATS \n");

						for(a = 0; a < 34; a++)
						{
							if(a % 6 == 0) printf("\n");
							printf("[%3d] : %3d ", a, register_stats[a].qi);
						}

						//PrintCache();
						break;
					}

				}

				if(count % 5 == 0) clocks++;
				printf("\n\nCLOCK: %d", clocks);
				if(clocks == max) break;
				count++;
			}
			printf("\nACABOU\n");
			break;
		}

		case 1:
		{
			#define S_
			int a;
			int max;
			CarregarBios(arguments.args[0]);
			printf("\n");
			max = atoi(arguments.args[1]);
			if(max == 0) max = 1000;
			Clock(max);
			printf("\n\nESTACOES DE RESERVA\n");
			PrintEstacao();
			printf("\n\nBANCO DE REGISTRADORES\n");
			PrintaRegistradores();
			printf("\n\nREGISTER STATS \n");

			for(a = 0; a < 34; a++)
			{
				if(a % 6 == 0) printf("\n");
				printf("[%3d] : %3d ", a, register_stats[a].qi);
			}
			printf("\n\nNUMERO DE CLOCKS: %d", clocks);

			break;
		}
	}
	printf("\n\n");
}

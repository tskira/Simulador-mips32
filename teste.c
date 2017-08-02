	#include <stdio.h>
#include <stdlib.h>

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

	int main()
	{
		unsigned char *teste;
		int x;
		int count = 0;
		union_int_char palavra_inteira;
		palavra_inteira.valor_inteiro = 32;
		unsigned char* palavra_barramento;
		unsigned char palavra_cdb[4];
		fila minha_fila = {.inicio = 0, .tamanho = 0, .fim = -1};
		char c;
		int clock_number = -1;

		CarregarBios("input");
		/*
		printf("\n ### RAMO PROCESSADOR ### \n\n");
		PrintMemoria();
		printf("\n");
		ReadCache(0);
		ReadCache(32);
		//printf("\n %x %x %x %x", teste[0], teste[1], teste[2], teste[3]);
		PrintCache();

		printf("\n\n #### TESTE DO WRITECACHE ####\n\n");
		palavra_inteira.valor_inteiro = 9;
		palavra_cdb[0] = palavra_inteira.valor_char.byte_32;
		palavra_cdb[1] = palavra_inteira.valor_char.byte_24;
		palavra_cdb[2] = palavra_inteira.valor_char.byte_16;
		palavra_cdb[3] = palavra_inteira.valor_char.byte_8;
		JogaNoCdb(palavra_cdb);

		WriteCache(4);
		PrintCache();
		PrintMemoria();
		printf("\n");
		printf("\n ### BANCO DE REGISTRADORES ### \n");
		PrintaRegistradores();
		printf("\n\n");

		printf("\n%x %x %x %x\n", palavra_inteira.valor_char.byte_32,
								palavra_inteira.valor_char.byte_24,
								palavra_inteira.valor_char.byte_16,
								palavra_inteira.valor_char.byte_8);


		ReadCache(4);
		palavra_barramento = PegaNoCdb();
		printf("\n ### TESTE DO BARRAMENTO ###\n %x %x %x %x\n", palavra_barramento[0],
								 palavra_barramento[1],
							 	 palavra_barramento[2],
							 	 palavra_barramento[3]);
		ReadCache(0);
		palavra_inteira.valor_char.byte_32 = PegaNoCdb()[0];
		palavra_inteira.valor_char.byte_24 = PegaNoCdb()[1];
		palavra_inteira.valor_char.byte_16 = PegaNoCdb()[2];
		palavra_inteira.valor_char.byte_8 = PegaNoCdb()[3];

		printf("\nPrimeira posicao: %d \n", palavra_inteira.valor_inteiro );
		IncrementarPc();
		program_counter = pc_plus_4;
		IncrementarPc();
		printf("\n%d\n", pc_plus_4);
		Infileira(&minha_fila, 2);
		Infileira(&minha_fila, 3);
		Infileira(&minha_fila, 4);
		Desinfileira(&minha_fila);
		PrintFila(minha_fila);
		*/
		/*
		Fetch();
		printf("\nPC: %d", pc_plus_4);
		Decode();
		printf("\nDecomposto: op: %d - rd: %d - rt: %d - rs: %d - s: %d - f: %d ", inst_rij_decomposta.r_type.opcode,
										  inst_rij_decomposta.r_type.operando_rd,
									  	  inst_rij_decomposta.r_type.operando_rt,
									  	  inst_rij_decomposta.r_type.operando_rs,
									  	  inst_rij_decomposta.r_type.shamt,
									  	  inst_rij_decomposta.r_type.funct );
		Execution();
		PrintEstacaoAdd();
		*/
		printf("\n");

		while((c = getchar()) == '\n')
		{
			int index;
			if(flag_halt) break;
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

			if(count % 5 == 0) clock_number++;
			printf("\n\nCLOCK: %d", clock_number);
			count++;
		}
		/*
		Fetch();
		printf("\nPC: %d", program_counter);
		printf("\nFLAG DESINFILEIRA: %d", flag_desinfileira);
		Decode();
		printf("\nINST: %d", inst_rij_decomposta.instrucao_inteiro);
		Execution();
		PrintEstacao();
		printf("\n");
		*/
		printf("\nACABOU\n");
		return 0;

	}

#include <stdio.h>
#include <stdlib.h>

#include "pipeline.h"

	/* IF/ID registradores */
	int pc_plus_4 = 0;
	union_int_char inst;
	int flag_stall = 0;

	/* ID/EX registradores e estruturas */
	int flag_desinfileira = 0;
	fila instruction_queue = {.inicio = 0, .fim = -1, .tamanho = 0, .elementos = {[0 ... (Q_SIZE - 1)] = 0}};
	union_rij_inteiro inst_rij_decomposta;
	union_int_char inst_aux;

	/* EX/MA registradores e estruturas */
	int saida_ula;
	int target;
	int flag_condition = 0;
	union_int_char resultado_ula_u;
	int b_register;
	long long int accumulator_register;
	estado_do_registrador register_stats[34] =
	{
		[0 ... 33] = {.qi = -1}
	};

	/*MA/WB registradores e estruturas */
	union_int_char load_memory_data;
	union_int_char resultado_escrita;
	char store_buffer[4];

	funcao_pipeline estagios_pipeline[] =
	{
		[0] = &WriteBack,
		[1] = &MemoryAcess,
		[2] = &Execution,
		[3] = &Decode,
		[4] = &Fetch
	};

	void Fetch()
	{
		/* Verifica se a fila de instrucoes nao esta cheia */
		if(instruction_queue.tamanho < Q_SIZE && !flag_stall)
		{
			ReadCache(program_counter);
			/* Coloca a instrucao buscada no registrador intermediario inst (ri do mips) */
			inst.valor_char.byte_32 = PegaNoCdb()[0];
			inst.valor_char.byte_24 = PegaNoCdb()[1];
			inst.valor_char.byte_16 = PegaNoCdb()[2];
			inst.valor_char.byte_8 =  PegaNoCdb()[3];
			/* Incrementa o pc e coloca no registrador intermediario pc_plus_4 */
			IncrementarPc();
		}
	}

	void Decode()
	{
		/* -> Decodificar apenas se houverem estacoes de reserva para a instrucao livres */

		int index;
		/* Adiciona a instrucao do ir na fila */
		if (instruction_queue.tamanho < Q_SIZE && !flag_stall)
		{
			palavra[0] = inst.valor_char.byte_32;
			palavra[1] = inst.valor_char.byte_24;
			palavra[2] = inst.valor_char.byte_16;
			palavra[3] = inst.valor_char.byte_8;
			JogaNoCdb(palavra);
			inst_aux.valor_char.byte_32 = PegaNoCdb()[0];
			inst_aux.valor_char.byte_24 = PegaNoCdb()[1];
			inst_aux.valor_char.byte_16 = PegaNoCdb()[2];
			inst_aux.valor_char.byte_8 = PegaNoCdb()[3];

			/* adiciona a instrucao decodificada na fila */
			Infileira(&instruction_queue, inst_aux.valor_inteiro);
			inst.valor_inteiro = 0;
		}

		/*
		 * Retira da fila a instrucao na sequencia
		 * -> Arrumar aki para retirar apenas se houverem estacoes de reserva livres <-
		 * Decodifica a instrucao e armazena os valores de interesse nos registradores intermediario
		 * Se a flag estiver setada, entao a instrucao da cabeca da fila foi colocada em alguma er
		 * Assim, pode-se desinfileirar a prox instrucao
		 */
		if(flag_desinfileira)
		{
			inst_aux.valor_inteiro = Desinfileira(&instruction_queue);
			palavra[0] = inst_aux.valor_char.byte_32;
			palavra[1] = inst_aux.valor_char.byte_24;
			palavra[2] = inst_aux.valor_char.byte_16;
			palavra[3] = inst_aux.valor_char.byte_8;
			JogaNoCdb(palavra);
			inst_aux.valor_char.byte_32 = PegaNoCdb()[0];
			inst_aux.valor_char.byte_24 = PegaNoCdb()[1];
			inst_aux.valor_char.byte_16 = PegaNoCdb()[2];
			inst_aux.valor_char.byte_8 = PegaNoCdb()[3];

			/* retira inst da fila e decodifica no registrador intermediario */
			inst_rij_decomposta.instrucao_inteiro = inst_aux.valor_inteiro;
			/* nao enviar lixo entre os estagios do pipeline */
			if(inst_rij_decomposta.i_type.opcode == 4 || inst_rij_decomposta.i_type.opcode == 5 ||
			   inst_rij_decomposta.i_type.opcode == 6 || inst_rij_decomposta.i_type.opcode == 7 ||
		   	   (inst_rij_decomposta.r_type.opcode == 0 && inst_rij_decomposta.r_type.funct == 9)||
			   (inst_rij_decomposta.r_type.opcode == 0 && inst_rij_decomposta.r_type.funct == 8)||
		   	   inst_rij_decomposta.j_type.opcode == 3 || inst_rij_decomposta.j_type.opcode == 2)
			{
				/* caso branch */
				flag_stall = 1;
			}
			flag_desinfileira = 0;
		}

	}

	void Execution()
	{
		static int index_station = 0;
		int index;
		int count;

		/* -> arrumar aki para executar apenas se a unidade funcional referente a instrucao esteja livre */
		/* pega a instrucao decodificada no regisgtrador intermediario e tenta colocar numa er */
		inst_aux.valor_inteiro = inst_rij_decomposta.instrucao_inteiro;

		palavra[0] = inst_aux.valor_char.byte_32;
		palavra[1] = inst_aux.valor_char.byte_24;
		palavra[2] = inst_aux.valor_char.byte_16;
		palavra[3] = inst_aux.valor_char.byte_8;
		JogaNoCdb(palavra);

		/* Atualiza a flag desinfileira se uma er foi liberada */
		/* Emissao */
		flag_desinfileira = Emissao();


		/*
		 * Correr as estacoes de reserva verificando quais instrucoes podem ser executadas
		 * Ou seja, aquelas tais quais os campos Q estao em -1
		 */
		 for(index = 0; index < 15; index++)
		 {

			 if(reservation_station[index].busy > 0)
			 {
				 if(!functional_unit[index].flag_executou)
				 {
					 /* Execute do tomasulo */
					 if(reservation_station[index].qj == -1 &&
					 	reservation_station[index].qk == -1)
					 {
						 instruction_set[reservation_station[index].op](index);
						 if(reservation_station[index].op != 12)
						 {
							 /* caso nao syscall */
							 functional_unit[index].flag_executou = 1;
    						 reservation_station[index].busy -= 1;
						 }
						 #ifdef D_
						 printf("\nULA STATE: x: %d | y: %d | output: %lld", functional_unit[index].fu_alu.operando_x,
					 													    functional_unit[index].fu_alu.operando_y,
																			 functional_unit[index].fu_alu.alu_output);
						#endif
					 }
				 }
				 else
				 {
					 reservation_station[index].busy -= 1;
				 }
			 }

		 }

		 if(!cdb_busy)
		 {
			 for(index = (index_station++,index_station = index_station % 15), count = 0; count < 15; index = (index + 1) % 15, count++)
			 {
				 /* cdb nao esta ocupado neste ciclo, pode ser utilizado */
				 if(reservation_station[index].busy == 0)
				 {
					 cdb_busy = 1;
    				 inst_aux.valor_inteiro = functional_unit[index].fu_alu.alu_output;
    				 palavra[0] = inst_aux.valor_char.byte_32;
    				 palavra[1] = inst_aux.valor_char.byte_24;
    				 palavra[2] = inst_aux.valor_char.byte_16;
    				 palavra[3] = inst_aux.valor_char.byte_8;
    				 JogaNoCdb(palavra);
    				 resultado_ula_u.valor_char.byte_32 = PegaNoCdb()[0];
    				 resultado_ula_u.valor_char.byte_24 = PegaNoCdb()[1];
    				 resultado_ula_u.valor_char.byte_16 = PegaNoCdb()[2];
    				 resultado_ula_u.valor_char.byte_8 = PegaNoCdb()[3];
    				 saida_ula = resultado_ula_u.valor_inteiro;
    				 cdb_er_utilizando = index;

					 /* instrucoes que utilizam o registrador B */
					 if(reservation_station[index].op == 2752 || reservation_station[index].op == 2624 ||
						reservation_station[index].op == 2560)
					 {
						 /* Caso em que a operacao e um store, utiliza portanto registrador b */
						 b_register = reservation_station[index].vk;
					 }

					 /* instrucoes que utilizam o registrador target */
					 if(reservation_station[index].op == 256 || reservation_station[index].op == 320 ||
					 	reservation_station[index].op == 384 || reservation_station[index].op == 448 )
					 {
						 /* eh um branch */
						 target = (reservation_station[index].a);
						 flag_condition = saida_ula;
					 }

					 if(reservation_station[index].op == 9)
					 {
						 /* eh um jarl */
						 target = reservation_station[index].vj;
						 flag_condition = 1;
					 }

					 if(reservation_station[index].op == 192)
					 {
						 /* jal */
						 target = (reservation_station[index].a - 1) * 4;
						 flag_condition = 1;
					 }

					 if(reservation_station[index].op == 128 || reservation_station[index].op == 8)
					 {
						 /* j */
						 target = saida_ula;
						 flag_condition = 1;
					 }

					 if(reservation_station[index].op == 24 || reservation_station[index].op == 25)
					 {
						 /* mul, multu */
						 accumulator_register = functional_unit[index].fu_alu.alu_output;
					 }
					 if(reservation_station[index].op == 26 || reservation_station[index].op == 27)
					 {
						 long long int lj, lk;
						 lj = reservation_station[index].vj;
						 lk = reservation_station[index].vk;
						 lj = lj % lk;
						 lj = lj << 32;
						 lk = functional_unit[index].fu_alu.alu_output;
						 lj = lj | functional_unit[index].fu_alu.alu_output;
						 accumulator_register = lj;
					 }

				 }
			 }
		 }
	}

	void MemoryAcess()
	{
		/* atualizar o pc */
		#ifdef D_
			printf("\nFLAG CONDITION : %d", flag_condition);
		#endif
		if (flag_condition)
		{
			program_counter = target;
			flag_stall = 0;
			cdb_busy += 1;
			flag_condition = 0;
		}
		else
		{
			program_counter = pc_plus_4;

			if(cdb_busy)
			{
				if(reservation_station[cdb_er_utilizando].op == 256 || reservation_station[cdb_er_utilizando].op == 320 ||
				   reservation_station[cdb_er_utilizando].op == 384 || reservation_station[cdb_er_utilizando].op == 448)
				{
					/* o branch foi decidido, atualizar a flag stall */
					flag_stall = 0;
				}

				if(reservation_station[cdb_er_utilizando].op == 2240)
				{
					/* case lw */
					ReadCache(saida_ula + DATA_SEG);
					/* Coloca a instrucao buscada no registrador intermediario inst (ri do mips) */
					load_memory_data.valor_char.byte_32 = PegaNoCdb()[0];
					load_memory_data.valor_char.byte_24 = PegaNoCdb()[1];
					load_memory_data.valor_char.byte_16 = PegaNoCdb()[2];
					load_memory_data.valor_char.byte_8 =  PegaNoCdb()[3];
					saida_ula = load_memory_data.valor_inteiro;
				}

				if(reservation_station[cdb_er_utilizando].op == 2048  || reservation_station[cdb_er_utilizando].op == 2304)
				{
					/* case lb, lbu */
					ReadCache(saida_ula + DATA_SEG);
					/* Coloca a instrucao buscada no registrador intermediario inst (ri do mips) */
					load_memory_data.valor_char.byte_32 = PegaNoCdb()[0];
					load_memory_data.valor_char.byte_24 = PegaNoCdb()[1];
					load_memory_data.valor_char.byte_16 = PegaNoCdb()[2];
					load_memory_data.valor_char.byte_8 =  PegaNoCdb()[3];
					saida_ula = load_memory_data.valor_inteiro;
					saida_ula = saida_ula & 255;
				}

				if(reservation_station[cdb_er_utilizando].op == 2112 || reservation_station[cdb_er_utilizando].op == 2368)
				{
					/* case lh, lhu */
					ReadCache(saida_ula + DATA_SEG);
					/* Coloca a instrucao buscada no registrador intermediario inst (ri do mips) */
					load_memory_data.valor_char.byte_32 = PegaNoCdb()[0];
					load_memory_data.valor_char.byte_24 = PegaNoCdb()[1];
					load_memory_data.valor_char.byte_16 = PegaNoCdb()[2];
					load_memory_data.valor_char.byte_8 =  PegaNoCdb()[3];
					saida_ula = load_memory_data.valor_inteiro;
					saida_ula = saida_ula & 65535;
				}

				if(reservation_station[cdb_er_utilizando].op == 2560)
				{
					/* case sb */
					load_memory_data.valor_inteiro = b_register;
					load_memory_data.valor_inteiro = load_memory_data.valor_inteiro & 255;
					store_buffer[0] = load_memory_data.valor_char.byte_32;
					store_buffer[1] = load_memory_data.valor_char.byte_24;
					store_buffer[2] = load_memory_data.valor_char.byte_16;
					store_buffer[3] = load_memory_data.valor_char.byte_8;
					JogaNoCdb(store_buffer);
					WriteCache(saida_ula + DATA_SEG);
					saida_ula = 0;
				}

				if(reservation_station[cdb_er_utilizando].op == 2624)
				{
					/* case sh */
					load_memory_data.valor_inteiro = b_register;
					load_memory_data.valor_inteiro = load_memory_data.valor_inteiro & 65535;
					store_buffer[0] = load_memory_data.valor_char.byte_32;
					store_buffer[1] = load_memory_data.valor_char.byte_24;
					store_buffer[2] = load_memory_data.valor_char.byte_16;
					store_buffer[3] = load_memory_data.valor_char.byte_8;
					JogaNoCdb(store_buffer);
					WriteCache(saida_ula + DATA_SEG);
					saida_ula = 0;
				}

				if(reservation_station[cdb_er_utilizando].op == 2752)
				{
					/* case sw */
					load_memory_data.valor_inteiro = b_register;
					store_buffer[0] = load_memory_data.valor_char.byte_32;
					store_buffer[1] = load_memory_data.valor_char.byte_24;
					store_buffer[2] = load_memory_data.valor_char.byte_16;
					store_buffer[3] = load_memory_data.valor_char.byte_8;
					JogaNoCdb(store_buffer);
					WriteCache(saida_ula + DATA_SEG);
					saida_ula = 0;
				}

				cdb_busy += 1;
			}
		}
		/* acessar a memoria se nescessario */
	}

	void WriteBack()
	{
		int index;
		long long int acc_aux;

		if(cdb_busy == 2)
		{
			/* Tem algo para escrever */

			cdb_busy = 0;
			functional_unit[cdb_er_utilizando].flag_executou = 0;
			resultado_escrita.valor_inteiro = saida_ula;
			palavra[0] = resultado_escrita.valor_char.byte_32;
			palavra[1] = resultado_escrita.valor_char.byte_24;
			palavra[2] = resultado_escrita.valor_char.byte_16;
			palavra[3] = resultado_escrita.valor_char.byte_8;
			JogaNoCdb(palavra);
			resultado_escrita.valor_char.byte_32 = PegaNoCdb()[0];
			resultado_escrita.valor_char.byte_24 = PegaNoCdb()[1];
			resultado_escrita.valor_char.byte_16 = PegaNoCdb()[2];
			resultado_escrita.valor_char.byte_8 = PegaNoCdb()[3];
			for(index = 0; index < 34; index++)
			{
				if(register_stats[index].qi == cdb_er_utilizando)
				{
					registradores[index][0] = resultado_escrita.valor_char.byte_32;
					registradores[index][1] = resultado_escrita.valor_char.byte_24;
					registradores[index][2] = resultado_escrita.valor_char.byte_16;
					registradores[index][3] = resultado_escrita.valor_char.byte_8;
					register_stats[index].qi = -1;


					if(index == 32 && reservation_station[cdb_er_utilizando].op == 24 ||
					   index == 32 && reservation_station[cdb_er_utilizando].op == 25 ||
				   	   index == 32 && reservation_station[cdb_er_utilizando].op == 26 ||
				   	   index == 32 && reservation_station[cdb_er_utilizando].op == 27 )
					{
						acc_aux = accumulator_register >> 32;
						/* caso hi */

						resultado_escrita.valor_inteiro = acc_aux;
						registradores[index][0] = resultado_escrita.valor_char.byte_32;
						registradores[index][1] = resultado_escrita.valor_char.byte_24;
						registradores[index][2] = resultado_escrita.valor_char.byte_16;
						registradores[index][3] = resultado_escrita.valor_char.byte_8;
					}

					if(index == 33 && reservation_station[cdb_er_utilizando].op == 24 ||
					   index == 33 && reservation_station[cdb_er_utilizando].op == 25 ||
				   	   index == 33 && reservation_station[cdb_er_utilizando].op == 26 ||
				   	   index == 33 && reservation_station[cdb_er_utilizando].op == 27)
					{
						/* caso lo */
						acc_aux = accumulator_register << 32;
						acc_aux = accumulator_register >> 32;

						resultado_escrita.valor_inteiro = accumulator_register;
						registradores[index][0] = resultado_escrita.valor_char.byte_32;
						registradores[index][1] = resultado_escrita.valor_char.byte_24;
						registradores[index][2] = resultado_escrita.valor_char.byte_16;
						registradores[index][3] = resultado_escrita.valor_char.byte_8;
					}
				}
			}
			for(index = 0; index < 15; index++)
			{
				if(reservation_station[index].qj == cdb_er_utilizando)
				   {
					   reservation_station[index].qj = -1;
					   reservation_station[index].vj = resultado_escrita.valor_inteiro;
				   }

			   if(reservation_station[index].qk == cdb_er_utilizando)
				  {
					  reservation_station[index].qk = -1;
					  reservation_station[index].vk = resultado_escrita.valor_inteiro;
				  }
			}
			reservation_station[cdb_er_utilizando].busy = -1;
			FlushEstacao(cdb_er_utilizando);
		}
	}


	void ExecutarPipeline(int numero_de_clocks)
	{
		int index;
		while(!flag_halt && clocks != numero_de_clocks)
		{
			for(index = 0; index < 5; index ++)
			{
				estagios_pipeline[index]();
			}
			clocks++;
		}

	}

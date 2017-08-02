#include "estacoes.h"

	/* inicializacao das estacaoes de reserva */

	estacao_de_reserva reservation_station[15] =
	{
		[0 ... 14] = {.op = 0, .qj = -1, .qk = -1, .vj = 0, .vk = 0, .a = 0, .busy = -1},
	};


	/* aplicacao do tomasulo para emissao */
	int Emissao()
	{
		union_int_char leitor_registradores;
		union_int_char ex_instrucao_alvo;
		union_rij_inteiro ex_decode_alvo;
		int index;
		int colocou_na_er;
		int opcode_alvo;

		ex_instrucao_alvo.valor_char.byte_32 = PegaNoCdb()[0];
		ex_instrucao_alvo.valor_char.byte_24 = PegaNoCdb()[1];
		ex_instrucao_alvo.valor_char.byte_16 = PegaNoCdb()[2];
		ex_instrucao_alvo.valor_char.byte_8 = PegaNoCdb()[3];
		ex_decode_alvo.instrucao_inteiro = ex_instrucao_alvo.valor_inteiro;
		opcode_alvo = ex_decode_alvo.r_type.opcode;
		/* Arrumar os cases para as instrucoes */
		if(ex_decode_alvo.r_type.opcode == 0)
		{
			/* zero instruction */
			/* tipo R */
			switch(ex_decode_alvo.r_type.funct)
			{
				case(32):
				{
					/* add */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(12):
				{
					/* add */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(4):
				{
					/* sllv */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(6):
				{
					/* srlv */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(8):
				{
					/* jr */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(9):
				{
					/* jalr */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(33):
				{
					/* addu */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(34):
				{
					/* sub */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(35):
				{
					/* subu */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(36):
				{
					/* and */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(37):
				{
					/* or */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(38):
				{
					/* xor */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(39):
				{
					/* nor */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(42):
				{
					/* slt */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(43):
				{
					/* sltu */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(0):
				{
					/* sll */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(2):
				{
					/* srl */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(3):
				{
					/* sra */
					return (TomasuloIssue(ADD_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(24):
				{
					/* mult */
					return (TomasuloIssue(MUL_ER, HI_LO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(25):
				{
					/* multu */
					return (TomasuloIssue(MUL_ER, HI_LO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(26):
				{
					/* div */
					return (TomasuloIssue(MUL_ER, HI_LO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(27):
				{
					/* divu */
					return (TomasuloIssue(MUL_ER, HI_LO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(16):
				{
					/* mfhi */
					return (TomasuloIssue(ADD_ER, ACC_MOVE, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(17):
				{
					/* mthi */
					return (TomasuloIssue(ADD_ER, MOVE_ACC, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(18):
				{
					/* mthi */
					return (TomasuloIssue(ADD_ER, ACC_LO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(19):
				{
					/* mthi */
					return (TomasuloIssue(ADD_ER, LO_ACC, ex_decode_alvo.instrucao_inteiro));
					break;
				}
			}
		}
		else
		{
			opcode_alvo = opcode_alvo * 64;
			/* nao zero */
			switch(opcode_alvo)
			{
				case(128):
				{
					/* j */
					return (TomasuloIssue(ADD_ER, J_JMP, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(192):
				{
					/* jal */
					return (TomasuloIssue(ADD_ER, JAL_JMP, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(256):
				{
					return (TomasuloIssue(ADD_ER, I_BRANCH, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(320):
				{
					return (TomasuloIssue(ADD_ER, I_BRANCH, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(384):
				{
					return (TomasuloIssue(ADD_ER, I_BRANCH, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(448):
				{
					return (TomasuloIssue(ADD_ER, I_BRANCH, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(512):
				{
					/* addi */
					return (TomasuloIssue(ADD_ER, I_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(576):
				{
					/* addiu */
					return (TomasuloIssue(ADD_ER, I_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(640):
				{
					/* slti */
					return (TomasuloIssue(ADD_ER, I_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(704):
				{
					/* sltiu*/
					return (TomasuloIssue(ADD_ER, I_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(768):
				{
					/* andi */
					return (TomasuloIssue(ADD_ER, I_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(832):
				{
					/* ori */
					return (TomasuloIssue(ADD_ER, I_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(896):
				{
					/* xori */
					return (TomasuloIssue(ADD_ER, I_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}
				case(960):
				{
					/*lui*/
					return (TomasuloIssue(ADD_ER, I_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(1792):
				{
					return (TomasuloIssue(MUL_ER, R_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(2048):
				{
					return (TomasuloIssue(LOAD_ER, I_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(2112):
				{
					return (TomasuloIssue(LOAD_ER, I_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(2240):
				{
					return (TomasuloIssue(LOAD_ER, I_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(2304):
				{
					return (TomasuloIssue(LOAD_ER, I_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(2368):
				{
					return (TomasuloIssue(LOAD_ER, I_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(2560):
				{
					return (TomasuloIssue(STORE_ER, I_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(2624):
				{
					return (TomasuloIssue(STORE_ER, I_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

				case(2752):
				{
					return (TomasuloIssue(STORE_ER, I_TIPO, ex_decode_alvo.instrucao_inteiro));
					break;
				}

			}
		}

		return 0;
	}

	int TomasuloIssue(int er_alvo, int tipo_alvo, int i_alocar)
	{
		int index;
		union_int_char leitor_registradores;
		union_rij_inteiro instrucao_alocar;

		instrucao_alocar.instrucao_inteiro = i_alocar;

		switch(er_alvo)
		{
			case(ADD_ER):
			{
				switch(tipo_alvo)
				{
					case(R_TIPO):
					{
						index = 0;
						while(index < ADD_ER)
						{
							if(reservation_station[index].busy == -1)
							{
								/* axou uma er livre */
								if(i_alocar == 0) return 1; //caso nop
								/* Verficar a disponibilidade de de vj: */
								if(register_stats[instrucao_alocar.r_type.operando_rs].qi != -1)
								{
									reservation_station[index].qj = register_stats[instrucao_alocar.r_type.operando_rs].qi;
								}
								else
								{
									/* valor do registrador esta disponivel pega do banco de registradores */
									JogaNoCdb(registradores[instrucao_alocar.r_type.operando_rs]);
									leitor_registradores.valor_char.byte_32 = PegaNoCdb()[0];
									leitor_registradores.valor_char.byte_24 = PegaNoCdb()[1];
									leitor_registradores.valor_char.byte_16 = PegaNoCdb()[2];
									leitor_registradores.valor_char.byte_8 = PegaNoCdb()[3];
									reservation_station[index].vj = leitor_registradores.valor_inteiro;
									reservation_station[index].qj = -1;
								}

								/* Verficar a disponibilidade de de vk: */
								if(register_stats[instrucao_alocar.r_type.operando_rt].qi != -1)
								{
									reservation_station[index].qk = register_stats[instrucao_alocar.r_type.operando_rt].qi;
								}
								else
								{
									/* valor do registrador esta disponivel pega do banco de registradores */
									JogaNoCdb(registradores[instrucao_alocar.r_type.operando_rt]);
									leitor_registradores.valor_char.byte_32 = PegaNoCdb()[0];
									leitor_registradores.valor_char.byte_24 = PegaNoCdb()[1];
									leitor_registradores.valor_char.byte_16 = PegaNoCdb()[2];
									leitor_registradores.valor_char.byte_8 = PegaNoCdb()[3];
									reservation_station[index].vk = leitor_registradores.valor_inteiro;
									reservation_station[index].qk = -1;
								}
								reservation_station[index].a = instrucao_alocar.r_type.shamt;
								reservation_station[index].op = instrucao_alocar.r_type.funct;
								reservation_station[index].busy = clock_instruction[instrucao_alocar.r_type.funct];
								/* registrador zero deve segurar valor 0 sempre */
								if(instrucao_alocar.r_type.operando_rd != 0) register_stats[instrucao_alocar.r_type.operando_rd].qi = index;
								return 1;
							}
							index++;
						}
						break;
					}

					case(I_TIPO):
					{
						index = 0;
						while (index < 3)
						{
							if(reservation_station[index].busy == -1)
							{
								/* axou uma er livre */

								/* Verficar a disponibilidade de de vj: */
								if(register_stats[instrucao_alocar.i_type.operando_rs].qi != -1)
								{
									reservation_station[index].qj = register_stats[instrucao_alocar.i_type.operando_rs].qi;
								}
								else
								{
									/* valor do registrador esta disponivel pega do banco de registradores */
									JogaNoCdb(registradores[instrucao_alocar.i_type.operando_rs]);
									leitor_registradores.valor_char.byte_32 = PegaNoCdb()[0];
									leitor_registradores.valor_char.byte_24 = PegaNoCdb()[1];
									leitor_registradores.valor_char.byte_16 = PegaNoCdb()[2];
									leitor_registradores.valor_char.byte_8 = PegaNoCdb()[3];
									reservation_station[index].vj = leitor_registradores.valor_inteiro;
									reservation_station[index].qj = -1;
								}

								reservation_station[index].qk = -1;
								reservation_station[index].busy = clock_instruction[(instrucao_alocar.i_type.opcode * 64)];
								reservation_station[index].op = (instrucao_alocar.i_type.opcode * 64);
								reservation_station[index].a = ConvertNumber(instrucao_alocar.i_type.imediato);
								/* registrador zero deve segurar valor 0 sempre */
								if(instrucao_alocar.i_type.operando_rt != 0) register_stats[instrucao_alocar.i_type.operando_rt].qi = index;

								return 1;
							}
							index++;
						}

						break;
					}

					case(I_BRANCH):
					{
						index = 0;
						while(index < ADD_ER)
						{
							if(reservation_station[index].busy == -1)
							{
								/* axou uma er livre */
								/* Verficar a disponibilidade de de vj: */
								if(register_stats[instrucao_alocar.i_type.operando_rs].qi != -1)
								{
									reservation_station[index].qj = register_stats[instrucao_alocar.i_type.operando_rs].qi;
								}
								else
								{
									/* valor do registrador esta disponivel pega do banco de registradores */
									JogaNoCdb(registradores[instrucao_alocar.i_type.operando_rs]);
									leitor_registradores.valor_char.byte_32 = PegaNoCdb()[0];
									leitor_registradores.valor_char.byte_24 = PegaNoCdb()[1];
									leitor_registradores.valor_char.byte_16 = PegaNoCdb()[2];
									leitor_registradores.valor_char.byte_8 = PegaNoCdb()[3];
									reservation_station[index].vj = leitor_registradores.valor_inteiro;
									reservation_station[index].qj = -1;
								}

								/* Verficar a disponibilidade de de vk: */
								if(register_stats[instrucao_alocar.i_type.operando_rt].qi != -1)
								{
									reservation_station[index].qk = register_stats[instrucao_alocar.i_type.operando_rt].qi;
								}
								else
								{
									/* valor do registrador esta disponivel pega do banco de registradores */
									JogaNoCdb(registradores[instrucao_alocar.i_type.operando_rt]);
									leitor_registradores.valor_char.byte_32 = PegaNoCdb()[0];
									leitor_registradores.valor_char.byte_24 = PegaNoCdb()[1];
									leitor_registradores.valor_char.byte_16 = PegaNoCdb()[2];
									leitor_registradores.valor_char.byte_8 = PegaNoCdb()[3];
									reservation_station[index].vk = leitor_registradores.valor_inteiro;
									reservation_station[index].qk = -1;
								}
								reservation_station[index].a = ConvertNumber(instrucao_alocar.i_type.imediato);
								reservation_station[index].op = instrucao_alocar.i_type.opcode * 64;
								reservation_station[index].busy = clock_instruction[instrucao_alocar.r_type.opcode * 64];
								return 1;
							}
							index++;
						}
						break;
					}

					case(JAL_JMP):
					{
						index = 0;
						while (index < 3)
						{
							if(reservation_station[index].busy == -1)
							{
								/* axou uma er livre */

								reservation_station[index].qj = -1;
								reservation_station[index].qk = -1;
								reservation_station[index].busy = clock_instruction[(instrucao_alocar.j_type.opcode * 64)];
								reservation_station[index].op = (instrucao_alocar.j_type.opcode * 64);
								reservation_station[index].a = instrucao_alocar.j_type.address;
								/* registrador zero deve segurar valor 0 sempre */
								register_stats[31].qi = index;

								return 1;
							}
							index++;
						}
						break;
					}

					case(J_JMP):
					{
						index = 0;
						while (index < 3)
						{
							if(reservation_station[index].busy == -1)
							{
								/* axou uma er livre */

								reservation_station[index].qj = -1;
								reservation_station[index].qk = -1;
								reservation_station[index].busy = clock_instruction[(instrucao_alocar.j_type.opcode * 64)];
								reservation_station[index].op = (instrucao_alocar.j_type.opcode * 64);
								reservation_station[index].a = instrucao_alocar.j_type.address;
								/* registrador zero deve segurar valor 0 sempre */

								return 1;
							}
							index++;
						}
						break;
					}

					case(ACC_MOVE):
					{
						index = 0;
						while(index < ADD_ER)
						{
							if(reservation_station[index].busy == -1)
							{
								/* axou uma er livre */
								if(i_alocar == 0) return 1; //caso nop
								/* Verficar a disponibilidade de de vj: */
								if(register_stats[32].qi != -1)
								{
									reservation_station[index].qj = register_stats[32].qi;
								}
								else
								{
									/* valor do registrador esta disponivel pega do banco de registradores */
									JogaNoCdb(registradores[32]);
									leitor_registradores.valor_char.byte_32 = PegaNoCdb()[0];
									leitor_registradores.valor_char.byte_24 = PegaNoCdb()[1];
									leitor_registradores.valor_char.byte_16 = PegaNoCdb()[2];
									leitor_registradores.valor_char.byte_8 = PegaNoCdb()[3];
									reservation_station[index].vj = leitor_registradores.valor_inteiro;
									reservation_station[index].qj = -1;
								}

								//reservation_station[index].a = instrucao_alocar.r_type.shamt;
								reservation_station[index].op = instrucao_alocar.r_type.funct;
								reservation_station[index].busy = clock_instruction[instrucao_alocar.r_type.funct];
								/* registrador zero deve segurar valor 0 sempre */
								if(instrucao_alocar.r_type.operando_rs != 0) register_stats[instrucao_alocar.r_type.operando_rs].qi = index;
								return 1;
							}
							index++;
						}
						break;
					}

					case(MOVE_ACC):
					{
						index = 0;
						while(index < ADD_ER)
						{
							if(reservation_station[index].busy == -1)
							{
								/* axou uma er livre */
								if(i_alocar == 0) return 1; //caso nop
								/* Verficar a disponibilidade de de vj: */
								if(register_stats[instrucao_alocar.r_type.operando_rs].qi != -1)
								{
									reservation_station[index].qj = register_stats[instrucao_alocar.r_type.operando_rs].qi;
								}
								else
								{
									/* valor do registrador esta disponivel pega do banco de registradores */
									JogaNoCdb(registradores[instrucao_alocar.r_type.operando_rs]);
									leitor_registradores.valor_char.byte_32 = PegaNoCdb()[0];
									leitor_registradores.valor_char.byte_24 = PegaNoCdb()[1];
									leitor_registradores.valor_char.byte_16 = PegaNoCdb()[2];
									leitor_registradores.valor_char.byte_8 = PegaNoCdb()[3];
									reservation_station[index].vj = leitor_registradores.valor_inteiro;
									reservation_station[index].qj = -1;
								}

								reservation_station[index].op = instrucao_alocar.r_type.funct;
								reservation_station[index].busy = clock_instruction[instrucao_alocar.r_type.funct];
								/* registrador zero deve segurar valor 0 sempre */
								register_stats[32].qi = index;
								return 1;
							}
							index++;
						}
						break;
					}

					case(ACC_LO):
					{
						index = 0;
						while(index < ADD_ER)
						{
							if(reservation_station[index].busy == -1)
							{
								/* axou uma er livre */
								if(i_alocar == 0) return 1; //caso nop
								/* Verficar a disponibilidade de de vj: */
								if(register_stats[33].qi != -1)
								{
									reservation_station[index].qj = register_stats[33].qi;
								}
								else
								{
									/* valor do registrador esta disponivel pega do banco de registradores */
									JogaNoCdb(registradores[33]);
									leitor_registradores.valor_char.byte_32 = PegaNoCdb()[0];
									leitor_registradores.valor_char.byte_24 = PegaNoCdb()[1];
									leitor_registradores.valor_char.byte_16 = PegaNoCdb()[2];
									leitor_registradores.valor_char.byte_8 = PegaNoCdb()[3];
									reservation_station[index].vj = leitor_registradores.valor_inteiro;
									reservation_station[index].qj = -1;
								}

								//reservation_station[index].a = instrucao_alocar.r_type.shamt;
								reservation_station[index].op = instrucao_alocar.r_type.funct;
								reservation_station[index].busy = clock_instruction[instrucao_alocar.r_type.funct];
								/* registrador zero deve segurar valor 0 sempre */
								if(instrucao_alocar.r_type.operando_rs != 0) register_stats[instrucao_alocar.r_type.operando_rs].qi = index;
								return 1;
							}
							index++;
						}
						break;
					}


					case(LO_ACC):
					{
						index = 0;
						while(index < ADD_ER)
						{
							if(reservation_station[index].busy == -1)
							{
								/* axou uma er livre */
								if(i_alocar == 0) return 1; //caso nop
								/* Verficar a disponibilidade de de vj: */
								if(register_stats[instrucao_alocar.r_type.operando_rs].qi != -1)
								{
									reservation_station[index].qj = register_stats[instrucao_alocar.r_type.operando_rs].qi;
								}
								else
								{
									/* valor do registrador esta disponivel pega do banco de registradores */
									JogaNoCdb(registradores[instrucao_alocar.r_type.operando_rs]);
									leitor_registradores.valor_char.byte_32 = PegaNoCdb()[0];
									leitor_registradores.valor_char.byte_24 = PegaNoCdb()[1];
									leitor_registradores.valor_char.byte_16 = PegaNoCdb()[2];
									leitor_registradores.valor_char.byte_8 = PegaNoCdb()[3];
									reservation_station[index].vj = leitor_registradores.valor_inteiro;
									reservation_station[index].qj = -1;
								}

								reservation_station[index].op = instrucao_alocar.r_type.funct;
								reservation_station[index].busy = clock_instruction[instrucao_alocar.r_type.funct];
								/* registrador zero deve segurar valor 0 sempre */
								register_stats[33].qi = index;
								return 1;
							}
							index++;
						}
						break;
					}


				}
				break;
			}

			case(MUL_ER):
			{
				switch(tipo_alvo)
				 {
					case (R_TIPO):
					{
						index = 3;
						while(index < MUL_ER)
						{
							if(reservation_station[index].busy == -1)
							{
								/* axou uma er livre */
								/* Verficar a disponibilidade de de vj: */
								if(register_stats[instrucao_alocar.r_type.operando_rs].qi != -1)
								{
									reservation_station[index].qj = register_stats[instrucao_alocar.r_type.operando_rs].qi;
								}
								else
								{
									/* valor do registrador esta disponivel pega do banco de registradores */
									JogaNoCdb(registradores[instrucao_alocar.r_type.operando_rs]);
									leitor_registradores.valor_char.byte_32 = PegaNoCdb()[0];
									leitor_registradores.valor_char.byte_24 = PegaNoCdb()[1];
									leitor_registradores.valor_char.byte_16 = PegaNoCdb()[2];
									leitor_registradores.valor_char.byte_8 = PegaNoCdb()[3];
									reservation_station[index].vj = leitor_registradores.valor_inteiro;
									reservation_station[index].qj = -1;
								}

								/* Verficar a disponibilidade de de vk: */
								if(register_stats[instrucao_alocar.r_type.operando_rt].qi != -1)
								{
									reservation_station[index].qk = register_stats[instrucao_alocar.r_type.operando_rt].qi;
								}
								else
								{
									/* valor do registrador esta disponivel pega do banco de registradores */
									JogaNoCdb(registradores[instrucao_alocar.r_type.operando_rt]);
									leitor_registradores.valor_char.byte_32 = PegaNoCdb()[0];
									leitor_registradores.valor_char.byte_24 = PegaNoCdb()[1];
									leitor_registradores.valor_char.byte_16 = PegaNoCdb()[2];
									leitor_registradores.valor_char.byte_8 = PegaNoCdb()[3];
									reservation_station[index].vk = leitor_registradores.valor_inteiro;
									reservation_station[index].qk = -1;
								}
								reservation_station[index].a = instrucao_alocar.r_type.shamt;
								reservation_station[index].op = instrucao_alocar.r_type.opcode * 64;
								reservation_station[index].busy = clock_instruction[instrucao_alocar.r_type.opcode * 64];
								/* registrador zero deve segurar valor 0 sempre */
								if(instrucao_alocar.r_type.operando_rd != 0) register_stats[instrucao_alocar.r_type.operando_rd].qi = index;

								return 1;
							}
							index++;
						}

						break;
					}

					case(HI_LO):
					{
						index = 3;
						while(index < MUL_ER)
						{
							if(reservation_station[index].busy == -1)
							{
								/* axou uma er livre */
								/* Verficar a disponibilidade de de vj: */
								if(register_stats[instrucao_alocar.r_type.operando_rs].qi != -1)
								{
									reservation_station[index].qj = register_stats[instrucao_alocar.r_type.operando_rs].qi;
								}
								else
								{
									/* valor do registrador esta disponivel pega do banco de registradores */
									JogaNoCdb(registradores[instrucao_alocar.r_type.operando_rs]);
									leitor_registradores.valor_char.byte_32 = PegaNoCdb()[0];
									leitor_registradores.valor_char.byte_24 = PegaNoCdb()[1];
									leitor_registradores.valor_char.byte_16 = PegaNoCdb()[2];
									leitor_registradores.valor_char.byte_8 = PegaNoCdb()[3];
									reservation_station[index].vj = leitor_registradores.valor_inteiro;
									reservation_station[index].qj = -1;
								}

								/* Verficar a disponibilidade de de vk: */
								if(register_stats[instrucao_alocar.r_type.operando_rt].qi != -1)
								{
									reservation_station[index].qk = register_stats[instrucao_alocar.r_type.operando_rt].qi;
								}
								else
								{
									/* valor do registrador esta disponivel pega do banco de registradores */
									JogaNoCdb(registradores[instrucao_alocar.r_type.operando_rt]);
									leitor_registradores.valor_char.byte_32 = PegaNoCdb()[0];
									leitor_registradores.valor_char.byte_24 = PegaNoCdb()[1];
									leitor_registradores.valor_char.byte_16 = PegaNoCdb()[2];
									leitor_registradores.valor_char.byte_8 = PegaNoCdb()[3];
									reservation_station[index].vk = leitor_registradores.valor_inteiro;
									reservation_station[index].qk = -1;
								}
								reservation_station[index].op = instrucao_alocar.r_type.funct;
								reservation_station[index].busy = clock_instruction[instrucao_alocar.r_type.funct];
								/* registrador zero deve segurar valor 0 sempre */
								register_stats[32].qi = index;
								register_stats[33].qi = index;

								return 1;
							}
							index++;
						}

						break;
					}
				}

				break;
			}

			case(LOAD_ER):
			{
				index = 5;
				while (index < LOAD_ER)
				{
					if(reservation_station[index].busy == -1)
					{
						/* axou uma er livre */

						/* Verficar a disponibilidade de de vj: */
						if(register_stats[instrucao_alocar.i_type.operando_rs].qi != -1)
						{
							reservation_station[index].qj = register_stats[instrucao_alocar.i_type.operando_rs].qi;
						}
						else
						{
							/* valor do registrador esta disponivel pega do banco de registradores */
							JogaNoCdb(registradores[instrucao_alocar.i_type.operando_rs]);
							leitor_registradores.valor_char.byte_32 = PegaNoCdb()[0];
							leitor_registradores.valor_char.byte_24 = PegaNoCdb()[1];
							leitor_registradores.valor_char.byte_16 = PegaNoCdb()[2];
							leitor_registradores.valor_char.byte_8 = PegaNoCdb()[3];
							reservation_station[index].vj = leitor_registradores.valor_inteiro;
							reservation_station[index].qj = -1;
						}

						reservation_station[index].qk = -1;
						reservation_station[index].busy = clock_instruction[(instrucao_alocar.i_type.opcode * 64)];
						reservation_station[index].op = (instrucao_alocar.i_type.opcode * 64);
						reservation_station[index].a = ConvertNumber(instrucao_alocar.i_type.imediato);
						/* registrador zero deve segurar valor 0 sempre */
						if(instrucao_alocar.i_type.operando_rt != 0) register_stats[instrucao_alocar.i_type.operando_rt].qi = index;
						return 1;
					}
					index++;
				}
				break;
			}

			case(STORE_ER):
			{
				index = 10;
				while (index < STORE_ER)
				{
					if(reservation_station[index].busy == -1)
					{
						/* axou uma er livre */

						/* Verficar a disponibilidade de de vj: */
						if(register_stats[instrucao_alocar.i_type.operando_rs].qi != -1)
						{
							reservation_station[index].qj = register_stats[instrucao_alocar.i_type.operando_rs].qi;
						}
						else
						{
							/* valor do registrador esta disponivel pega do banco de registradores */
							JogaNoCdb(registradores[instrucao_alocar.i_type.operando_rs]);
							leitor_registradores.valor_char.byte_32 = PegaNoCdb()[0];
							leitor_registradores.valor_char.byte_24 = PegaNoCdb()[1];
							leitor_registradores.valor_char.byte_16 = PegaNoCdb()[2];
							leitor_registradores.valor_char.byte_8 = PegaNoCdb()[3];
							reservation_station[index].vj = leitor_registradores.valor_inteiro;
							reservation_station[index].qj = -1;
						}

						if(register_stats[instrucao_alocar.i_type.operando_rt].qi != -1)
						{
							reservation_station[index].qk = register_stats[instrucao_alocar.i_type.operando_rt].qi;
						}
						else
						{
							/* valor do registrador esta disponivel pega do banco de registradores */
							JogaNoCdb(registradores[instrucao_alocar.i_type.operando_rt]);
							leitor_registradores.valor_char.byte_32 = PegaNoCdb()[0];
							leitor_registradores.valor_char.byte_24 = PegaNoCdb()[1];
							leitor_registradores.valor_char.byte_16 = PegaNoCdb()[2];
							leitor_registradores.valor_char.byte_8 = PegaNoCdb()[3];
							reservation_station[index].vk = leitor_registradores.valor_inteiro;
							reservation_station[index].qk = -1;
						}

						reservation_station[index].busy = clock_instruction[(instrucao_alocar.i_type.opcode * 64)];
						reservation_station[index].op = (instrucao_alocar.i_type.opcode * 64);
						reservation_station[index].a = ConvertNumber(instrucao_alocar.i_type.imediato);
						/* registrador zero deve segurar valor 0 sempre */
						//if(instrucao_alocar.i_type.operando_rt != 0) register_stats[instrucao_alocar.i_type.operando_rt].qi = index;
						return 1;
					}
					index++;
				}
				break;
			}
		}
		return 0;
	}

	void PrintEstacao()
	{
		int index;

		for (index = 0; index < 15; index++)
		{
			if(index >= 0 && index < 3) printf("\nADD");
			if(index >= 3 && index < 5) printf("\nMUL");
			if(index >= 5 && index < 10) printf("\nLOAD");
			if(index >= 10 && index < 15) printf("\nSTORE");

			printf("#%2d => op: %d/%d | vj : %d | vk : %d | qj : %d | qk : %d | a : %u | busy : %d",
					index,
					reservation_station[index].op >> 6, reservation_station[index].op & 127, reservation_station[index].vj, reservation_station[index].vk,
					reservation_station[index].qj, reservation_station[index].qk, reservation_station[index].a, reservation_station[index].busy);
		}
	}

	void FlushEstacao(int estacao_alvo)
	{

		reservation_station[estacao_alvo].op = 0;
		reservation_station[estacao_alvo].vj = 0;
		reservation_station[estacao_alvo].vk = 0;
		reservation_station[estacao_alvo].qk = -1;
		reservation_station[estacao_alvo].qj = -1;
		reservation_station[estacao_alvo].a = 0;
	}

	int ConvertNumber(int value)
	{
		int aux;
		aux = value >> 15;
		if(aux)
		{
			value = value | 4294901760;
		}
		return value;
	}

	int EstacaoVazia()
	{
		int i;
		int estavazio = 1;

		for(i = 0; i < 15; i++)
		{
			if(reservation_station[i].busy != -1)
			{
				if(reservation_station[i].op != 12)
				{
					estavazio = 0;
				}
			}
		}
		return estavazio;
	}

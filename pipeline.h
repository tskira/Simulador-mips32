#ifndef PIPELINE_H_
#define PIPELINE_H_

	#include "processador.h"
	#include "cdb.h"
	#include "cache.h"
	#include "memoria.h"
	#include "somador.h"
	#include "fila.h"
	#include "instructions.h"
	#include "estacoes.h"
	#include "funcional.h"
	#include "clock.h"

	typedef void (*funcao_pipeline)(void);

	typedef struct inst_r_type
	{
		unsigned funct : 6;
		unsigned shamt : 5;
		unsigned operando_rd : 5;
		unsigned operando_rt : 5;
		unsigned operando_rs : 5;
		unsigned opcode: 6;
	} instruction_r;

	typedef struct inst_i_type
	{
		unsigned imediato : 16;
		unsigned operando_rt : 5;
		unsigned operando_rs : 5;
		unsigned opcode: 6;
	} instruction_i;

	typedef struct inst_j_type
	{
		unsigned address : 26;
		unsigned opcode: 6;
	} instruction_j;

	typedef union inst_decomposta
	{
		instruction_j j_type;
		instruction_i i_type;
		instruction_r r_type;
		unsigned int instrucao_inteiro;
	} union_rij_inteiro;

	typedef struct reg_stat
	{
		int qi;
	} estado_do_registrador;

	void WriteBack();
	void MemoryAcess();
	void Execution();
	void Decode();
	void Fetch();

	void ExecutarPipeline(int);

	extern funcao_pipeline estagios_pipeline[];

	/* IF/ID registradores */
	extern int pc_plus_4;
	extern union_int_char inst;
	extern int flag_stall;

	/*ID/EX registradores e estruturas */
	extern int flag_desinfileira ;
	extern fila instruction_queue;
	extern union_rij_inteiro inst_rij_decomposta;
	extern int target;
	extern int flag_condition;

	/* EX/MA registradores e estruturas */
	extern int saida_ula;
	extern int b_register;
	extern long long int accumulator_register;
	extern estado_do_registrador register_stats[34];

	/*MA/WB registradores e estruturas */
	extern union_int_char load_memory_data;
	extern 	union_int_char resultado_escrita;


#endif

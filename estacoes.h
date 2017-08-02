#ifndef RESERVATION_STATE_H_
#define RESERVATION_STATE_H_

	#include "pipeline.h"
	#include "instructions.h"
	#include "registradores.h"

	#define ADD_ER 3
	#define MUL_ER 5
	#define LOAD_ER 10
	#define STORE_ER 15

	#define R_TIPO 0
	#define I_TIPO 1
	#define J_TIPO 2
	#define I_BRANCH 3
	#define JAL_JMP 4
	#define J_JMP 5
	#define HI_LO 6
	#define ACC_MOVE 7
	#define MOVE_ACC 8
	#define ACC_LO 9
	#define LO_ACC 10

	typedef struct res_station
	{
		unsigned int op;
		int qj;
		int qk;
		int vj;
		int vk;
		int a;
	 	int busy;
	} estacao_de_reserva;

	extern estacao_de_reserva reservation_station[15];


	int Emissao();
	void PrintEstacao();
	int TomasuloIssue(int, int, int);
	void FlushEstacao(int);
	int ConvertNumber(int);
	int EstacaoVazia(void);

#endif

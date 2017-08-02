#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

	#include <stdio.h>
	#include <stdlib.h>
	#include <limits.h>

	#include "memoria.h"
	#include "cache.h"
	#include "registradores.h"
	#include "funcional.h"
	#include "processador.h"

	typedef void (*ponteiro_instrucao)(int);

	void InstSllv(int);
	void InstSrlv(int);
	void InstSrav(int);
	void InstAdd(int);
	void InstAddu(int);
	void InstSub(int);
	void InstSubu(int);
	void InstAnd(int);
	void InstOr(int);
	void InstXor(int);
	void InstNor(int);
	void InstSlt(int);
	void InstSltu(int);
	void InstJalr(int);
	void InstMult(int);
	void InstMultu(int);
	void InstDiv(int);
	void InstDivu(int);
	void InstJr(int);
	void InstMfhi(int);
	void InstMthi(int);
	void InstMflo(int);
	void InstMtlo(int);
	void InstSll(int);
	void InstSrl(int);
	void InstSra(int);
	void InstBeq(int);
	void InstBne(int);
	void InstAddi(int);
	void InstAddiu(int);
	void InstSlti(int);
	void InstSltiu(int);
	void InstAndi(int);
	void InstOri(int);
	void InstXori(int);
	void InstBlez(int);
	void InstBgtz(int);
	void InstLui(int);
	void InstLh(int);
	void InstLb(int);
	void InstLw(int);
	void InstLbu(int);
	void InstLhu(int);
	void InstSb(int);
	void InstSh(int);
	void InstSw(int);
	void InstJ(int);
	void InstJal(int);
	void InstSyscall(int);
	void InstNop(int);
	void InstMul(int);

	extern ponteiro_instrucao instruction_set[2753];
	extern int clock_instruction[2753];

#endif

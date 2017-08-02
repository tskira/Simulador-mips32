#ifndef SO_H_
#define SO_H_

#define DOT_TEXT 40
#define DOT_DATA 0

	#include "memoria.h"
	#include "cache.h"
	#include "barramento.h"
	#include "registradores.h"
	#include "assembler.h"

	extern unsigned char inteiro_em_char[4];
	extern int char_em_inteiro;

	void CarregarArquivo(char*);
	void CarregarBios(char*);
	unsigned char* Itoc(int);
	int Ctoi(char*);
	void PrintCache();
	void PrintMemoria();

#endif

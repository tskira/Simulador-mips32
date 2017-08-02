#ifndef UNIDADE_FUNCIONAL_H_
#define UNIDADE_FUNCIONAL_H_

	#include "estacoes.h"
	#include "pipeline.h"
	#include "ula.h"

	typedef struct funit
	{
		alu fu_alu;
		int flag_executou;
	} unidade_funcional;

	extern unidade_funcional functional_unit[15];

#endif

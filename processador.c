#include <stdio.h>
#include <stdlib.h>

#include "processador.h"

	unsigned int program_counter = 0;
	unsigned int cdb_busy = 0;
	unsigned int cdb_er_utilizando;
	int flag_halt = 0;

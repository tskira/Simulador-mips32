#ifndef CDB_H_
#define CDB_H_

	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>

	#include "memoria.h"
	#include "cache.h"

	extern unsigned char cdb[4];

	void JogaNoCdb(unsigned char*);
	unsigned char* PegaNoCdb();

#endif
	

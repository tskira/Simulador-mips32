simulador: simulador.c hash.c buffer.c estruturas.c assembler.tab.c lex.yy.c memoria.c so.c cache.c registradores.c barramento.c cdb.c somador.c pipeline.c processador.c fila.c estacoes.c instructions.c ula.c funcional.c clock.c
	bison -d assembler.y
	flex assembler.l
	cc -o simulador simulador.c assembler.tab.c lex.yy.c hash.c buffer.c estruturas.c memoria.c so.c  cache.c registradores.c barramento.c cdb.c somador.c pipeline.c processador.c fila.c estacoes.c instructions.c ula.c funcional.c clock.c -lfl

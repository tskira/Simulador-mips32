#ifndef FILA_H_
#define FILA_H_

	#include <stdio.h>
	#define Q_SIZE 6

	typedef struct queue
	{
		unsigned int elementos[Q_SIZE];
		int inicio;
		int tamanho;
		int fim;
	}fila;

	void Infileira(fila*, unsigned int);
	unsigned int Desinfileira(fila*);
	void PrintFila(fila);

#endif

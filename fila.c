#include "fila.h"

	void Infileira(fila *fila_alvo, unsigned int value)
	{
		if (fila_alvo->tamanho < Q_SIZE)
		{
			if(fila_alvo->fim == Q_SIZE -1)
			{
				fila_alvo->fim = -1;
			}
			fila_alvo->elementos[++fila_alvo->fim] = value;
			fila_alvo->tamanho++;
		}
	}

	unsigned int Desinfileira(fila *fila_alvo)
	{
		int cabeca_da_fila;
		if(fila_alvo->tamanho > 0)
		{
			cabeca_da_fila = fila_alvo->elementos[fila_alvo->inicio];
			fila_alvo->elementos[fila_alvo->inicio] = 0;
			fila_alvo->inicio++;
			if (fila_alvo->inicio == Q_SIZE)
			{
				fila_alvo->inicio = 0;
			}
			fila_alvo->tamanho--;
			return (cabeca_da_fila);
		}
		return 0;

	}

	void PrintFila(fila fila_alvo)
	{
		int index;

		printf("\n");
		for (index = fila_alvo.inicio; index < (fila_alvo.tamanho + fila_alvo.inicio) ; index++)
		{
			printf("%d ", fila_alvo.elementos[index % Q_SIZE]);
		}
		printf("\n");
	}

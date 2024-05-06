#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

#define N 100

struct fila
{
    type *v;
    int ini;
    int fim;
};

Fila *criaFila()
{
    int size = N;
    Fila *q;
    q = (Fila *)malloc(sizeof(Fila));
    q->v = (type *)malloc(size * sizeof(type));
    q->ini = 0;
    q->fim = 0;
    return q;
}

void insereFila(Fila *q, type x)
{
    q->v[q->fim] = x;
    (q->fim)++;
}

type removeFila(Fila *q)
{
    type x;
    x = q->v[q->ini];
    (q->ini)++;
    return x;
}

int filaVazia(Fila *q)
{
    return q->fim == q->ini;
}

int filaCheia(Fila *q)
{
    return q->fim == N;
}

void imprimeFila(Fila *q)
{
    for (int i = q->ini; i < q->fim; i++)
        printf("%c ", q->v[i]);
    printf("\n");
}

int tamFila(Fila *q)
{
    return q->fim - q->ini;
}

Fila *liberaFila(Fila *q)
{
    free(q->v);
    free(q);
    return NULL;
}

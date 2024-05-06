#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

#define TAM_MAX 100

struct fila
{
    char *vetor;
    int ini;
    int fim;
};

Fila *criaFila()
{
    Fila *q;
    q = (Fila *)malloc(sizeof(Fila));
    q->vetor = (char *)malloc(TAM_MAX * sizeof(char));
    q->ini = 0;
    q->fim = 0;
    return q;
}

void insereFila(Fila *q, char x)
{
    q->vetor[q->fim] = x;
    (q->fim)++;
}

char removeFila(Fila *q)
{
    char x;
    x = q->vetor[q->ini];
    (q->ini)++;
    return x;
}

int filaVazia(Fila *q)
{
    return q->fim == q->ini;
}

int filaCheia(Fila *q)
{
    return q->fim == TAM_MAX;
}

void imprimeFila(Fila *q)
{
    for (int i = q->ini; i < q->fim; i++)
        printf("%c ", q->vetor[i]);
    printf("\n");
}

int tamFila(Fila *q)
{
    return q->fim - q->ini;
}

Fila *liberaFila(Fila *q)
{
    free(q->vetor);
    free(q);
    return NULL;
}

#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

#define TAM_MAX 100

struct fila
{
    type *vetor;
    int ini;
    int fim;
};

Fila *criaFila()
{
    Fila *q;
    q = (Fila *)malloc(sizeof(Fila));
    q->vetor = (type *)malloc(TAM_MAX * sizeof(type));
    // Por que os seguintes valores? Faz diferença?
    q->ini = TAM_MAX / 2;
    q->fim = TAM_MAX / 2;
    return q;
}

void insereFila(Fila *q, type x)
{
    q->vetor[q->fim] = x;
    // (q->fim)++;
    // if (q->fim == TAM_MAX)
    //     q->fim = 0;
    q->fim = (q->fim + 1) % TAM_MAX;
}

type removeFila(Fila *q)
{
    type x;
    x = q->vetor[q->ini];
    // (q->ini)++;
    // if (q->ini == TAM_MAX)
    //     q->ini = 0;
    q->ini = (q->ini + 1) % TAM_MAX;
    return x;
}

int filaVazia(Fila *q)
{
    return q->fim == q->ini;
}

int filaCheia(Fila *q)
{
    // return (q->fim + 1 == q->ini || (q->fim + 1 == TAM_MAX && q->ini == 0));
    return (q->fim + 1) % TAM_MAX == q->ini;
}

void imprimeFila(Fila *q)
{
    int i;
    // note que os prints dependem do tipo
    if (q->ini <= q->fim)
        for (i = q->ini; i < q->fim; i++)
            printf("%c ", q->vetor[i]);
    else // q->fim < q->ini
    {
        for (i = q->ini; i < TAM_MAX; i++)
            printf("%c ", q->vetor[i]);
        for (i = 0; i < q->fim; i++)
            printf("%c ", q->vetor[i]);
    }
    printf("\n");
}

void imprimeFila2(Fila *q)
{
    int i;
    // Quiz2: note que os prints dependem do tipo
    for (i = q->ini; i != q->fim; i = (i + 1) % TAM_MAX)
        printf("%c ", q->vetor[i]);
    printf("\n");
}

int tamFila(Fila *q)
{
    if (q->ini <= q->fim)
        return q->fim - q->ini;
    return (TAM_MAX - q->ini) + (q->fim - 0);
}

Fila *liberaFila(Fila *q)
{
    free(q->vetor);
    free(q);
    return NULL;
}

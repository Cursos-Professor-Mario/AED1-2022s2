#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"

#define TAM_MAX 100

struct pilha
{
    char *vetor;
    int topo;
};

Pilha *criaPilha()
{
    Pilha *s;
    s = (Pilha *)malloc(sizeof(Pilha));
    s->vetor = (char *)malloc(TAM_MAX * sizeof(char));
    s->topo = 0;
    return s;
}

void empilha(Pilha *s, char x)
{
    s->vetor[s->topo] = x;
    (s->topo)++;
}

char desempilha(Pilha *s)
{
    (s->topo)--;
    return s->vetor[s->topo];
}

char consultaTopo(Pilha *s)
{
    return s->vetor[(s->topo) - 1];
}

int pilhaVazia(Pilha *s)
{
    return s->topo <= 0;
}

int pilhaCheia(Pilha *s)
{
    return s->topo == TAM_MAX;
}

void imprimePilha(Pilha *s)
{
    for (int i = (s->topo) - 1; i >= 0; i--)
        printf("%c ", s->vetor[i]);
    printf("\n");
}

int tamPilha(Pilha *s)
{
    return s->topo;
}

Pilha *liberaPilha(Pilha *s)
{
    free(s->vetor);
    free(s);
    return NULL;
}

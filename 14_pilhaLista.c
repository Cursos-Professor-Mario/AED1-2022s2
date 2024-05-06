#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"

typedef struct celula
{
    char conteudo;
    struct celula *prox;
} Celula;

struct pilha
{
    Celula *lst;
    int tam;
};

Pilha *criaPilha()
{
    Pilha *s;
    s = (Pilha *)malloc(sizeof(Pilha));
    s->lst = NULL;
    s->tam = 0;
    return s;
}

void empilha(Pilha *s, char x)
{
    Celula *nova;
    nova = malloc(sizeof(Celula));
    nova->conteudo = x;
    nova->prox = s->lst;
    s->lst = nova;
    s->tam++;
}

char desempilha(Pilha *s)
{
    char x;
    Celula *morta;
    morta = s->lst;
    x = morta->conteudo;
    s->lst = morta->prox;
    free(morta);
    morta = NULL;
    (s->tam)--;
    return x;
}

char consultaTopo(Pilha *s)
{
    return s->lst->conteudo;
}

int pilhaVazia(Pilha *s)
{
    return s->lst == NULL;
    // return s->tam == 0;
}

int pilhaCheia(Pilha *s)
{
    return 0;
}

void imprimePilha(Pilha *s)
{
    Celula *p;
    p = s->lst;
    while (p != NULL)
    {
        printf("%c ", p->conteudo);
        p = p->prox;
    }
    printf("\n");
}

int tamPilha(Pilha *s)
{
    // Celula *p;
    // int tam = 0;
    // p = s->lst;
    // while (p != NULL)
    // {
    //     p = p->prox;
    //     tam++;
    // }
    // return tam;
    return s->tam;
}

Pilha *liberaPilha(Pilha *s)
{
    Celula *p, *morta;
    p = s->lst;
    while (p != NULL)
    {
        morta = p;
        p = p->prox;
        free(morta);
    }
    free(s);
    return NULL;
}

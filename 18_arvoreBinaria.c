#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int Cont;

typedef struct noh
{
    Cont conteudo;
    struct noh *pai; // opcional
    struct noh *esq;
    struct noh *dir;
} Noh;

typedef Noh *Arvore;

int altura(Arvore r)
{
    int hesq, hdir;
    // atenção para o valor devolvido no caso base
    if (r == NULL)
        return -1;
    hesq = altura(r->esq);
    hdir = altura(r->dir);
    if (hesq > hdir)
        return hesq + 1;
    return hdir + 1;
}

// Percurso in-ordem
void inOrdem(Arvore r)
{
    if (r != NULL)
    {
        inOrdem(r->esq);
        printf("(%d) ", r->conteudo);
        inOrdem(r->dir);
    }
}

void inOrdemI(Arvore r)
{
    Noh *p;
    Noh *pilha[100];
    int topo = 0; // inicializa a pilha
    p = r;        // começa pela raiz
    // enquanto nó corrente não for nulo
    // e ainda houverem nós por imprimir na pilha
    while (p != NULL || topo > 0)
    {
        if (p != NULL)
        {
            pilha[topo++] = p; // empilha p
            p = p->esq;        // visita filho esquerdo de p
        }
        else // p == NULL
        {
            p = pilha[--topo]; // desempilha
            printf("(%d) ", p->conteudo);
            p = p->dir; // visita o filho direito de p
        }
    }
}

// Percurso pós-ordem
void posOrdem(Arvore r)
{
    if (r != NULL)
    {
        posOrdem(r->esq);
        posOrdem(r->dir);
        printf("%d\n", r->conteudo);
    }
}

// Percurso pré-ordem
void preOrdem(Arvore r)
{
    if (r != NULL)
    {
        printf("%d\n", r->conteudo);
        preOrdem(r->esq);
        preOrdem(r->dir);
    }
}

Noh *predecessor(Noh *x)
{
    Noh *p;
    if (x->esq != NULL)
    {
        p = x->esq;
        while (p->dir != NULL)
            p = p->dir;
    }
    else
    {
        p = x->pai;
        while (p != NULL && p->esq == x)
        {
            x = p;
            p = p->pai;
        }
    }
    return p;
}

Noh *sucessor(Noh *x)
{
    Noh *p;
    if (x->dir != NULL)
    {
        p = x->dir;
        while (p->esq != NULL)
            p = p->esq;
    }
    else
    {
        p = x->pai;
        while (p != NULL && p->dir == x)
        {
            x = p;
            p = p->pai;
        }
    }
    return p;
}

int main()
{
    return 0;
}
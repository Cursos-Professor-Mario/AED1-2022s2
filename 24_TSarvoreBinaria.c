#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "TSarvoreBinaria.h"

typedef Noh *Arvore;

int altura(Arvore r)
{
    int hesq, hdir;
    if (r == NULL)
        return -1;
    hesq = altura(r->esq);
    hdir = altura(r->dir);
    if (hesq > hdir)
        return hesq + 1;
    return hdir + 1;
}

void imprimeSimbolos(int n, char c)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%c", c);
}

// Percurso pre-ordem destacando altura de cada subárvore
void preOrdemHierarquico(Arvore r, int altura, char t_filho)
{
    if (r != NULL)
    {
        imprimeSimbolos(altura, t_filho);
        printf("%d\n", r->chave);
        preOrdemHierarquico(r->esq, altura + 1, '>');
        preOrdemHierarquico(r->dir, altura + 1, '<');
    }
}

// Percurso in-ordem
void inOrdemR(Arvore r)
{
    if (r != NULL)
    {
        inOrdemR(r->esq);
        printf("(%d, %d) ", r->chave, r->tam);
        inOrdemR(r->dir);
    }
}

void inOrdemI(Arvore r)
{
    Noh *x;
    Noh *p[100];
    int t = 0; // inicializa a pilha
    x = r;     // começa pela raiz
    // enquanto nó corrente não for nulo
    // e ainda houverem nós por imprimir na pilha
    while (x != NULL || t > 0)
    {
        if (x != NULL)
        {
            p[t++] = x; // empilha x
            x = x->esq; // visita filho esquerdo de x
        }
        else
        {
            x = p[--t]; // desempilha x
            printf("(%d, %d) ", x->chave, x->tam);
            x = x->dir; // visita o filho direito de x
        }
    }
}

// Percurso pré-ordem
void preOrdem(Arvore r)
{
    if (r != NULL)
    {
        printf("%d\n", r->chave);
        preOrdem(r->esq);
        preOrdem(r->dir);
    }
}

// Percurso pós-ordem
void posOrdem(Arvore r)
{
    if (r != NULL)
    {
        posOrdem(r->esq);
        posOrdem(r->dir);
        printf("%d\n", r->chave);
    }
}

void TSperc(TS *tab)
{
    inOrdemR(tab);
    printf("\n");
}

// supõe que r não é vazia
Noh *TSmin(Arvore r)
{
    while (r->esq != NULL)
        r = r->esq;
    return r;
}

// supõe que r não é vazia
Noh *TSmax(Arvore r)
{
    while (r->dir != NULL)
        r = r->dir;
    return r;
}

Noh *TSsuc(TS *tab, Chave x)
{
    Noh *q, *p;
    q = TSbusca(tab, x);
    if (q == NULL)
        return NULL;
    if (q->dir != NULL)
        return TSmin(q->dir);
    p = q->pai;
    while (p != NULL && p->dir == q)
    {
        q = p;
        p = p->pai;
    }
    return p;
}

Noh *TSpred(TS *tab, Chave x)
{
    Noh *q, *p;
    q = TSbusca(tab, x);
    if (q == NULL)
        return NULL;
    if (q->esq != NULL)
        return TSmax(q->esq);
    p = q->pai;
    while (p != NULL && p->esq == q)
    {
        q = p;
        p = p->pai;
    }
    return p;
}

Noh *TSpredSemPai(TS *tab, Chave x)
{
    Noh *q, *p = NULL;
    q = tab;
    while (q != NULL && q->chave != x)
    {
        if (x < q->chave)
            q = q->esq;
        else
        {
            p = q; // guarda o antepassado mais recente que é menor
            q = q->dir;
        }
    }
    if (q == NULL)
        return NULL;
    if (q->esq != NULL)
        return TSmax(q->esq);
    return p;
}

Noh *TSbuscaR(Arvore r, Chave chave)
{
    if (r == NULL)
        return r;
    if (r->chave == chave)
        return r;
    if (chave < r->chave)
        return TSbuscaR(r->esq, chave);
    // r->chave < chave
    return TSbuscaR(r->dir, chave);
}

Noh *TSbusca(Arvore r, Chave chave)
{
    while (r != NULL && r->chave != chave)
    {
        if (chave < r->chave)
            r = r->esq;
        else
            r = r->dir;
    }
    return r;
}

Noh *TSselec(Arvore r, int pos)
{
    int tam_esq;
    if (r == NULL)
        return NULL;
    if (r->esq != NULL)
        tam_esq = r->esq->tam;
    else
        tam_esq = 0;
    if (pos == tam_esq + 1)
        return r;
    if (pos < tam_esq + 1)
        return TSselec(r->esq, pos);
    // pos > tam_esq + 1
    return TSselec(r->dir, pos - tam_esq - 1);
}

int TSrank(Arvore r, Chave chave)
{
    int rank = 0, tam_esq;
    while (r != NULL && r->chave != chave)
    {
        if (chave < r->chave)
            r = r->esq;
        else // chave > r->chave
        {
            if (r->esq != NULL)
                tam_esq = r->esq->tam;
            else
                tam_esq = 0;
            rank += tam_esq + 1;
            r = r->dir;
        }
    }
    if (r != NULL)
    {
        if (r->esq != NULL)
            rank += r->esq->tam;
        rank++;
    }
    return rank;
}

Noh *novoNoh(Chave chave, Cont conteudo)
{
    Noh *novo;
    novo = (Noh *)malloc(sizeof(Noh));
    novo->chave = chave;
    novo->conteudo = conteudo;
    novo->tam = 1;
    novo->esq = NULL;
    novo->dir = NULL;
    //    novo->pai = ??
    return novo;
}

Arvore insereRsimples(Arvore r, Noh *novo)
{
    if (r == NULL)
        return novo;
    if (novo->chave <= r->chave)
        r->esq = insereR(r->esq, novo);
    else // novo->chave > r->chave
        r->dir = insereR(r->dir, novo);
    return r;
}

Arvore insereIsimples(Arvore r, Noh *novo)
{
    Noh *corr, *ant = NULL;
    if (r == NULL)
        return novo;
    corr = r;
    // desce na árvore até encontrar apontador NULL
    while (corr != NULL)
    {
        ant = corr;
        if (novo->chave <= corr->chave)
            corr = corr->esq;
        else // novo->chave > corr->chave
            corr = corr->dir;
    }
    // insere novo noh como filho do último noh do caminho
    if (novo->chave <= ant->chave)
        ant->esq = novo;
    else // novo->chave > ant->chave
        ant->dir = novo;
    return r;
}

Arvore insereI(Arvore r, Noh *novo)
{
    Noh *corr, *ant = NULL;
    if (r == NULL)
    {
        novo->pai = NULL;
        return novo;
    }
    corr = r;
    while (corr != NULL)
    {
        ant = corr;
        corr->tam++;
        if (novo->chave <= corr->chave)
            corr = corr->esq;
        else // novo->chave > corr->chave
            corr = corr->dir;
    }
    novo->pai = ant;
    if (novo->chave <= ant->chave)
        ant->esq = novo;
    else
        ant->dir = novo;
    return r;
}

Arvore insereR(Arvore r, Noh *novo)
{
    if (r == NULL)
    {
        novo->pai = NULL;
        return novo;
    }
    if (novo->chave <= r->chave)
    {
        r->esq = insereR(r->esq, novo);
        r->esq->pai = r;
    }
    else // novo->chave > r->chave
    {
        r->dir = insereR(r->dir, novo);
        r->dir->pai = r;
    }
    r->tam++;
    return r;
}

TS *TSinserir(TS *tab, Chave chave, Cont conteudo)
{
    Noh *novo = novoNoh(chave, conteudo);
    return insereI(tab, novo);
    // return insereR(tab, novo);
}

Arvore removeRaizSimples(Arvore alvo)
{
    Noh *aux, *pai;
    if (alvo->esq == NULL && alvo->dir == NULL)
    { // Caso 1: é folha
        free(alvo);
        return NULL;
    }
    if (alvo->esq == NULL || alvo->dir == NULL)
    { // Caso 2: só tem 1 filho
        if (alvo->esq == NULL)
            aux = alvo->dir;
        else // alvo->dir == NULL
            aux = alvo->esq;
        free(alvo);
        return aux;
    }
    // Caso 3: tem 2 filhos
    aux = alvo->esq;
    pai = alvo;
    while (aux->dir != NULL)
    {
        pai = aux;
        aux = aux->dir;
    }
    // substitui o nó alvo pelo predecessor dele
    alvo->chave = aux->chave;
    alvo->conteudo = aux->conteudo;
    if (pai == alvo)
        pai->esq = removeRaizSimples(aux);
    else // aux->pai != alvo
        pai->dir = removeRaizSimples(aux);
    return alvo;
}

TS *TSremoverSimples(TS *tab, Chave chave)
{
    Noh *alvo, *pai, *aux;
    alvo = tab;
    pai = NULL;
    while (alvo != NULL && alvo->chave != chave)
    {
        pai = alvo;
        if (chave < alvo->chave)
            alvo = alvo->esq;
        else
            alvo = alvo->dir;
    }
    if (alvo == NULL) // nada a remover
        return tab;
    aux = removeRaizSimples(alvo);
    if (pai == NULL) // aux é a nova raiz
        return aux;
    // atualizando o campo do pai corretamente
    if (pai->esq == alvo)
        pai->esq = aux;
    if (pai->dir == alvo)
        pai->dir = aux;
    return tab;
}

Arvore removeRaiz(Arvore alvo)
{
    Noh *aux, *pai, *p;
    if (alvo->esq == NULL && alvo->dir == NULL)
    { // Caso 1: é folha
        p = alvo->pai;
        free(alvo);

        while (p != NULL)
        {
            p->tam--;
            p = p->pai;
        }

        return NULL;
    }
    if (alvo->esq == NULL || alvo->dir == NULL)
    { // Caso 2: só tem 1 filho
        if (alvo->esq == NULL)
            aux = alvo->dir;
        else // alvo->dir == NULL
            aux = alvo->esq;
        aux->pai = alvo->pai;
        p = alvo->pai;
        free(alvo);

        while (p != NULL)
        {
            p->tam--;
            p = p->pai;
        }

        return aux;
    }
    // Caso 3: tem 2 filhos
    aux = TSmax(alvo->esq);
    // substitui o nó alvo pelo predecessor dele
    alvo->chave = aux->chave;
    alvo->conteudo = aux->conteudo;
    pai = aux->pai;
    if (pai == alvo)
        pai->esq = removeRaiz(aux);
    else // aux->pai != alvo
        pai->dir = removeRaiz(aux);

    p = aux->pai;
    while (p != NULL)
    {
        p->tam--;
        p = p->pai;
    }

    return alvo;
}

Arvore removeRaiz2(Arvore alvo)
{
    Noh *aux, *p;
    if (alvo->esq == NULL && alvo->dir == NULL)
    {
        printf("Caso 1\n");
        p = alvo->pai;
        free(alvo);

        while (p != NULL)
        {
            p->tam--;
            p = p->pai;
        }

        return NULL;
    }
    if (alvo->esq == NULL || alvo->dir == NULL)
    {
        printf("Caso 2\n");
        if (alvo->esq == NULL)
            aux = alvo->dir;
        else // alvo->dir == NULL
            aux = alvo->esq;
        aux->pai = alvo->pai;

        p = alvo->pai;

        free(alvo);

        while (p != NULL)
        {
            p->tam--;
            p = p->pai;
        }

        return aux;
    }
    printf("Caso 3\n");
    aux = TSmax(alvo->esq);
    printf("chave do predecessor do alvo = %d\n", aux->chave);
    p = aux->pai;
    if (p != alvo)
    {
        p->dir = aux->esq;
        aux->esq = alvo->esq;
        aux->dir = alvo->dir;
        aux->tam = aux->esq->tam + aux->dir->tam + 1;
        free(alvo);
    }
    else // p == alvo
    {
        aux->dir = alvo->dir;
        aux->tam = 1 + aux->dir->tam + 1;
        p = aux;
        free(alvo);
    }

    while (p != NULL)
    {
        p->tam--;
        p = p->pai;
    }

    return aux;
}

TS *TSremover(TS *tab, Chave chave)
{
    Noh *alvo, *pai, *aux;
    alvo = TSbusca(tab, chave);
    if (alvo == NULL) // nada a remover
        return tab;
    pai = alvo->pai;
    aux = removeRaiz(alvo);
    if (pai == NULL) // aux é a nova raiz
        return aux;
    // atualizando o campo do pai corretamente
    if (pai->esq == alvo)
        pai->esq = aux;
    if (pai->dir == alvo)
        pai->dir = aux;
    return tab;
}
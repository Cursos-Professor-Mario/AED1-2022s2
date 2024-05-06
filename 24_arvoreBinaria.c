#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int Chave;
typedef int Cont;

typedef struct noh
{
    Chave chave;
    Cont conteudo;
    int tam;
    struct noh *pai; // opcional
    struct noh *esq;
    struct noh *dir;
} Noh;

typedef Noh *Arvore;

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
void inOrdem(Arvore r)
{
    if (r != NULL)
    {
        inOrdem(r->esq);
        printf("(%d, %d) ", r->chave, r->tam);
        inOrdem(r->dir);
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

Noh *min(Arvore r)
{
    while (r->esq != NULL)
        r = r->esq;
    return r;
}

Noh *max(Arvore r)
{
    while (r->dir != NULL)
        r = r->dir;
    return r;
}

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

Noh *sucessor(Noh *x)
{
    Noh *p;
    if (x->dir != NULL)
        return min(x->dir);
    p = x->pai;
    while (p != NULL && p->dir == x)
    {
        x = p;
        p = p->pai;
    }
    return p;
}

Noh *predecessor(Noh *x)
{
    Noh *p;
    if (x->esq != NULL)
        return max(x->esq);
    p = x->pai;
    while (p != NULL && p->esq == x)
    {
        x = p;
        p = p->pai;
    }
    return p;
}

Noh *buscaR(Arvore r, Chave chave)
{
    if (r == NULL)
        return r;
    if (r->chave == chave)
        return r;
    if (chave < r->chave)
        return buscaR(r->esq, chave);
    // r->chave > chave
    return buscaR(r->dir, chave);
}

Noh *buscaI(Arvore r, Chave chave)
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
    else
    {
        r->dir = insereR(r->dir, novo);
        r->dir->pai = r;
    }
    r->tam++;
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
        else
            corr = corr->dir;
    }
    novo->pai = ant;
    if (novo->chave <= ant->chave)
        ant->esq = novo;
    else
        ant->dir = novo;
    return r;
}

Arvore inserir(Arvore r, Chave chave, Cont conteudo)
{
    Noh *novo = novoNoh(chave, conteudo);
    // return insereR(r, novo);
    return insereI(r, novo);
}

Arvore removeRaiz(Arvore alvo)
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
    aux = max(alvo->esq);
    printf("chave do predecessor do alvo = %d\n", aux->chave);
    alvo->chave = aux->chave;
    alvo->conteudo = aux->conteudo;
    p = aux->pai;
    if (p == alvo)
        p->esq = removeRaiz(aux);
    else // aux->pai != alvo
        p->dir = removeRaiz(aux);

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
    aux = max(alvo->esq);
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

Arvore removeI(Arvore r, Chave chave)
{
    Noh *alvo, *p, *aux;
    alvo = buscaI(r, chave);
    // if (alvo != NULL)
    //     printf("chave do alvo = %d\n", alvo->chave);
    // else
    //     printf("nao encontrou a chave alvo\n");
    if (alvo == NULL)
        return r;
    p = alvo->pai;
    aux = removeRaiz2(alvo);
    if (p == NULL)
        return aux;
    if (p->esq == alvo)
        p->esq = aux;
    if (p->dir == alvo)
        p->dir = aux;
    return r;
}

Noh *selecao(Arvore r, int i)
{
    int t_esq;
    if (r == NULL)
        return NULL;
    if (r->esq != NULL)
        t_esq = r->esq->tam;
    else
        t_esq = 0;
    if (i == t_esq + 1)
        return r;
    if (i < t_esq + 1)
        return selecao(r->esq, i);
    // i > t_esq + 1
    return selecao(r->dir, i - t_esq - 1);
}

int rank(Arvore r, Chave chave)
{
    int tam = 0, t_esq;
    while (r != NULL && r->chave != chave)
    {
        if (chave < r->chave)
            r = r->esq;
        else
        {
            if (r->esq != NULL)
                t_esq = r->esq->tam;
            else
                t_esq = 0;
            tam += t_esq + 1;
            r = r->dir;
        }
    }
    if (r != NULL)
    {
        if (r->esq != NULL)
            tam += r->esq->tam;
        tam++;
    }
    return tam;
}

int main(int argc, char *argv[])
{
    int i, n;
    Arvore r = NULL;
    Noh *aux;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros. Ex: arvoreBinaria 10\n");
        return 0;
    }

    n = atoi(argv[1]);

    // inserção em ordem crescente
    for (i = 0; i < n; i++)
        r = inserir(r, i, i);

    // inserção em ordem decrescente
    // for (i = n - 1; i >= 0; i--)
    //     r = inserir(r, i, i);

    // inserção alternada
    // for (i = 0; i < n / 2; i++)
    //     r = inserir(r, 2 * i, 2 * i);
    // for (i = 0; i < n / 2; i++)
    //     r = inserir(r, 2 * i + 1, 2 * i + 1);

    // inserção alternando positivos e negativos
    // for (i = 0; i < n; i++)
    // {
    //     r = inserir(r, i * pow(-1, i % 2), i * pow(-1, i % 2));
    //     inOrdem(r);
    //     printf("\n");
    // }

    inOrdem(r);
    printf("\n");

    preOrdemHierarquico(r, 0, ' ');

    aux = min(r);
    printf("min = %d\n", aux->chave);

    aux = max(r);
    printf("max = %d\n", aux->chave);

    printf("altura = %d\n", altura(r));

    aux = buscaR(r, n / 2);
    if (aux != NULL)
        printf("chave de n/2 = %d\n", aux->chave);
    else
    {
        printf("nao encontrou n/2\n");
        aux = r;
    }
    aux = predecessor(aux);
    if (aux != NULL)
        printf("chave do predecessor de n / 2 = % d\n ", aux->chave);
    else
        printf("n/2 nao tem predecessor\n ");
    aux = buscaI(r, n / 2);
    if (aux != NULL)
        printf("chave de n/2 = %d\n", aux->chave);
    else
    {
        printf("nao encontrou n/2\n");
        aux = r;
    }
    aux = sucessor(aux);
    if (aux != NULL)
        printf("chave do sucessor de n/2 = %d\n", aux->chave);
    else
        printf("n/2 nao tem sucessor\n");

    inOrdem(r);
    printf("\n");

    r = removeI(r, n / 2);
    inOrdem(r);
    printf("\n");

    for (i = 0; i < n; i += 3)
    {
        r = removeI(r, i);
        inOrdem(r);
        printf("\n");
    }

    preOrdemHierarquico(r, 0, ' ');
    inOrdem(r);
    printf("\n");

    i = 1;
    aux = selecao(r, i);
    printf("chave do %d-esimo = %d\n", i, aux->chave);
    printf("rank do %d-esimo = %d\n", i, rank(r, aux->chave));

    i = 5;
    aux = selecao(r, i);
    printf("chave do %d-esimo = %d\n", i, aux->chave);
    printf("rank do %d-esimo = %d\n", i, rank(r, aux->chave));

    return 0;
}
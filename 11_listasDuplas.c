#include <stdio.h>
#include <stdlib.h>

typedef struct celula Celula;
struct celula
{
    int conteudo;
    Celula *ante;
    Celula *prox;
};

void imprime(Celula *lst)
{
    Celula *p = lst->prox;
    while (p != NULL)
    {
        printf("%d ", p->conteudo);
        p = p->prox;
    }
    printf("\n");
}

Celula *busca(Celula *lst, int x)
{
    Celula *p = lst->prox;
    while (p != NULL && p->conteudo != x)
        p = p->prox;
    return p;
}

Celula *selecao(Celula *lst, int k)
{
    Celula *p = lst->prox;
    int pos = 0;
    while (p != NULL && pos < k)
    {
        p = p->prox;
        pos++;
    }
    return p;
}

void insere(Celula *lst, int x)
{
    Celula *nova;
    nova = malloc(sizeof(Celula));
    nova->conteudo = x;
    nova->prox = lst->prox;
    if (nova->prox != NULL)
        nova->prox->ante = nova;
    lst->prox = nova;
    nova->ante = lst;
}

// remove a celula sucessora de p
// supõe que p != NULL e p->prox != NULL
void remover(Celula *p)
{
    Celula *morta;
    morta = p->prox;
    p->prox = morta->prox;
    if (p->prox != NULL)
        p->prox->ante = p;
    free(morta);
}

// busca x na lista lst e insere y logo antes de x
// se x não está na lista insere y no final
void buscaInsere(Celula *lst, int x, int y)
{
    Celula *p, *q, *nova;
    nova = malloc(sizeof(Celula));
    nova->conteudo = y;
    p = lst;
    q = p->prox;
    while (q != NULL && q->conteudo != x)
    {
        p = q;
        q = p->prox;
    }
    p->prox = nova;
    nova->ante = p;
    nova->prox = q;
    if (nova->prox != NULL)
        nova->prox->ante = nova;
}

void buscaRemove(Celula *lst, int x)
{
    Celula *p, *e, *d;
    p = busca(lst, x);
    if (p != NULL)
    {
        e = p->ante;
        d = p->prox;
        e->prox = d;
        if (d != NULL)
            d->ante = e;
        free(p);
    }
}

int main(int argc, char *argv[])
{
    int i, n;

    Celula *ini;

    // Celula cabeca;
    // ini = &cabeca;
    // cabeca.ante = NULL; // necessario?
    // cabeca.prox = NULL;

    ini = malloc(sizeof(Celula));
    ini->ante = NULL; // necessario?
    ini->prox = NULL;

    if (argc != 2)
    {
        printf("Numero de parametros incorreto. Ex.: .\\listasEncadeadas 10\n");
        return 0;
    }

    n = atoi(argv[1]);

    printf("Insere n elementos na lista\n");
    for (i = 0; i < n; i++)
        insere(ini, i);
    imprime(ini);

    printf("Buscando elementos\n");
    Celula *p = busca(ini, 10);
    if (p != NULL)
        printf("%d\n", p->conteudo);
    else
        printf("nao encontrou\n");

    printf("Selecionando elementos\n");
    Celula *q = selecao(ini, 10);
    if (q != NULL)
        printf("%d\n", q->conteudo);
    else
        printf("nao existe\n");

    printf("remover(ini)\n");
    remover(ini);
    imprime(ini);
    printf("remover(ini->prox)\n");
    remover(ini->prox);
    imprime(ini);

    printf("buscaInsere(ini, 2, 3)\n");
    buscaInsere(ini, 2, 3);
    imprime(ini);
    printf("buscaInsere(ini, ini->prox->conteudo, 49)\n");
    buscaInsere(ini, ini->prox->conteudo, 49);
    imprime(ini);
    printf("buscaInsere(ini, 15, 17)\n");
    buscaInsere(ini, 15, 17);
    imprime(ini);

    printf("buscaRemove(ini, 2)\n");
    buscaRemove(ini, 2);
    imprime(ini);
    printf("buscaRemove(ini, ini->prox->conteudo)\n");
    buscaRemove(ini, ini->prox->conteudo);
    imprime(ini);
    printf("buscaRemove(ini, 17)\n");
    buscaRemove(ini, 17);
    imprime(ini);
}

#include <stdio.h>
#include <stdlib.h>

typedef struct celula Celula;
struct celula
{
    int conteudo;
    Celula *prox;
};

void imprime(Celula *lst)
{
    Celula *p = lst;
    while (p != NULL)
    {
        printf("%d ", p->conteudo);
        p = p->prox;
    }
    printf("\n");
}

Celula *busca(Celula *lst, int x)
{
    Celula *p = lst;
    while (p != NULL && p->conteudo != x)
        p = p->prox;
    return p;
}

Celula *selecao(Celula *lst, int k)
{
    Celula *p = lst;
    int pos = 0;
    while (p != NULL && pos < k)
    {
        p = p->prox;
        pos++;
    }
    return p;
}

void insereErrado1(Celula *lst, int x)
{
    Celula nova;
    nova.conteudo = x;
    nova.prox = lst;
    lst = &nova;
}

void insereErrado2(Celula *lst, int x)
{
    Celula *nova;
    nova = malloc(sizeof(Celula));
    nova->conteudo = x;
    nova->prox = lst;
    lst = nova;
}

Celula *insere1(Celula *lst, int x)
{
    Celula *nova;
    nova = malloc(sizeof(Celula));
    nova->conteudo = x;
    nova->prox = lst;
    return nova;
}

void insere2(Celula **plst, int x)
{
    Celula *nova;
    nova = malloc(sizeof(Celula));
    nova->conteudo = x;
    nova->prox = *plst;
    *plst = nova;
}

// remove a celula sucessora de p
// supõe que p != NULL e p->prox != NULL
void remove1(Celula *p)
{
    Celula *morta;
    morta = p->prox;
    p->prox = morta->prox;
    free(morta);
}

// remove a celula apontada por *pp
// supõe que *pp != NULL
void remove2(Celula **pp)
{
    Celula *morta;
    morta = *pp;
    *pp = morta->prox;
    free(morta);
}

// remove a celula apontada por p
// supõe que p != NULL
Celula *remove3(Celula *p)
{
    Celula *morta;
    morta = p;
    p = morta->prox;
    free(morta);
    return p;
}

// busca x na lista lst e insere y logo antes de x
// se x não está na lista insere y no final
Celula *buscaInsere1(Celula *lst, int x, int y)
{
    Celula *p, *q, *nova; // q sempre aponta para p->prox
    nova = malloc(sizeof(Celula));
    nova->conteudo = y;
    if (lst == NULL || lst->conteudo == x)
    {
        nova->prox = lst;
        return nova;
    }
    p = lst;
    q = p->prox;
    while (q != NULL && q->conteudo != x)
    {
        p = q;
        q = p->prox;
    }
    p->prox = nova;
    nova->prox = q;
    return lst;
}

// busca x na lista lst e insere y logo antes de x
// se x não está na lista insere y no final
void buscaInsere2(Celula **plst, int x, int y)
{
    Celula **pp, *nova;
    nova = malloc(sizeof(Celula));
    nova->conteudo = y;
    pp = plst;
    while (*pp != NULL && (*pp)->conteudo != x)
        pp = &(*pp)->prox;
    nova->prox = *pp;
    *pp = nova;
}

Celula *buscaRemove(Celula *lst, int x)
{
    Celula *p, *morta;
    p = lst;
    if (p == NULL) 
        return p;
    if (p->conteudo == x){
        morta = p;
        p = morta->prox;
        free(morta);
        return p;
    }
    while (p->prox != NULL && p->prox->conteudo != x)
        p = p->prox;
    if (p->prox != NULL)
    {
        morta = p->prox;
        p->prox = morta->prox;
        free(morta);
    }
    return lst;
}

int main(int argc, char *argv[])
{
    int i, n;

    Celula *ini = NULL; // lista vazia

    if (argc != 2)
    {
        printf("Numero de parametros incorreto. Ex.: .\\listasEncadeadas 10\n");
        return 0;
    }

    n = atoi(argv[1]);

    printf("Insere n elementos na lista\n");
    for (i = 0; i < n; i++)
    {
        // ini = insere1(ini, i);
        insere2(&ini, i);
    }
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

    printf("remove1(ini)\n");
    remove1(ini);
    imprime(ini);
    printf("remove1(ini->prox)\n");
    remove1(ini->prox);
    imprime(ini);

    printf("remove2(&ini)\n");
    remove2(&ini);
    imprime(ini);
    printf("remove2(&ini->prox)\n");
    remove2(&ini->prox);
    imprime(ini);

    printf("ini = remove3(ini)\n");
    ini = remove3(ini);
    imprime(ini);
    printf("ini->prox = remove3(ini->prox)\n");
    ini->prox = remove3(ini->prox);
    imprime(ini);

    printf("buscaInsere1(ini, 2, 3)\n");
    ini = buscaInsere1(ini, 2, 3);
    imprime(ini);
    printf("buscaInsere1(ini, ini->conteudo, 49)\n");
    ini = buscaInsere1(ini, ini->conteudo, 49);
    imprime(ini);
    printf("buscaInsere1(ini, 15, 17)\n");
    ini = buscaInsere1(ini, 15, 17);
    imprime(ini);

    printf("buscaInsere2(ini, 2, 3)\n");
    buscaInsere2(&ini, 2, 3);
    imprime(ini);
    printf("buscaInsere2(ini, ini->conteudo, 49)\n");
    buscaInsere2(&ini, ini->conteudo, 49);
    imprime(ini);
    printf("buscaInsere2(ini, 15, 17)\n");
    buscaInsere2(&ini, 15, 17);
    imprime(ini);

    printf("buscaRemove(ini, 2)\n");
    ini = buscaRemove(ini, 2);
    imprime(ini);
    printf("buscaRemove(ini, ini->prox->conteudo)\n");
    ini = buscaRemove(ini, ini->prox->conteudo);
    imprime(ini);
    printf("buscaRemove(ini, 17)\n");
    ini = buscaRemove(ini, 17);
    imprime(ini);
    printf("buscaRemove(ini, 49)\n");
    ini = buscaRemove(ini, 49);
    imprime(ini);
}
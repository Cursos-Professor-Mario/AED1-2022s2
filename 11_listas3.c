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
    Celula *p = lst->prox;
    while (p != lst)
    {
        printf("%d ", p->conteudo);
        p = p->prox;
    }
    printf("\n");
}

Celula *busca(Celula *lst, int x)
{
    Celula *p = lst->prox;
    while (p != lst && p->conteudo != x)
        p = p->prox;
    return p;
}

Celula *selecao(Celula *lst, int k)
{
    Celula *p = lst->prox;
    int q = 0;
    while (p != lst && q < k)
    {
        p = p->prox;
        q++;
    }
    return p;
}

void inserir(Celula *lst, int x)
{
    Celula *nova;
    nova = malloc(sizeof(Celula));
    nova->conteudo = x;
    nova->prox = lst->prox;
    lst->prox = nova;
}

// remove a celula sucessora de p
// supõe que p != NULL e p->prox != NULL
void remover(Celula *p)
{
    Celula *morta;
    morta = p->prox;
    p->prox = morta->prox;
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
    while (q != lst && q->conteudo != x)
    {
        p = q;
        q = p->prox;
    }
    p->prox = nova;
    nova->prox = q;
}

void buscaRemove(Celula *lst, int x)
{
    Celula *p, *morta;
    p = lst;
    while (p->prox != lst && p->prox->conteudo != x)
        p = p->prox;
    if (p->prox != NULL)
    {
        morta = p->prox;
        p->prox = morta->prox;
        free(morta);
    }
}


int main(int argc, char *argv[])
{
    int i, n;

    // lista vazia
    Celula *ini = (Celula *)malloc(sizeof(Celula)); // noh cabeca
    ini->prox = ini;

    if (argc != 2)
    {
        printf("Numero de parametros incorreto. Ex.: .\\listas2 10\n");
        return 0;
    }

    n = atoi(argv[1]);

    printf("Insere n elementos na lista\n");
    for (i = 0; i < n; i++)
    {
        inserir(ini, i);
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

    printf("remove(ini)\n");
    remover(ini);
    imprime(ini);
    printf("remove(ini->prox)\n");
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
    printf("buscaRemove(ini, ini->prox->prox->conteudo)\n");
    buscaRemove(ini, ini->prox->prox->conteudo);
    imprime(ini);
    printf("buscaRemove(ini, 17)\n");
    buscaRemove(ini, 17);
    imprime(ini);
    printf("buscaRemove(ini, 49)\n");
    buscaRemove(ini, 49);
    imprime(ini);
}
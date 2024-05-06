#include <stdio.h>
#include <stdlib.h>

#include "TSvetorOrdenado.h"

int main(int argc, char **argv)
{
    int i, n;
    Item *p, *v;
    TS *tab;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros! Ex.: .\\testandoTS 10");
        return 0;
    }

    n = atoi(argv[1]);
    v = (Item *)malloc(n * sizeof(Item));

    for (i = 0; i < n; i++)
    {
        v[i].chave = 2 * i;
        v[i].conteudo = i;
    }

    tab = TScria(v, n);

    printf("Perc:\n");
    TSperc(tab);

    printf("Busca:\n");
    printf("%d: ", n / 2);
    p = TSbusca(tab, n / 2);
    if (p != NULL)
        printf("(%d, %d)\n", p->chave, p->conteudo);
    else
        printf("Nao achou\n");
    printf("%d: ", n / 2 + 1);
    p = TSbusca(tab, n / 2 + 1);
    if (p != NULL)
        printf("(%d, %d)\n", p->chave, p->conteudo);
    else
        printf("Nao achou\n");
    printf("%d: ", n / 2 - 1);
    p = TSbusca(tab, n / 2 - 1);
    if (p != NULL)
        printf("(%d, %d)\n", p->chave, p->conteudo);
    else
        printf("Nao achou\n");

    printf("Min:\n");
    p = TSmin(tab);
    printf("(%d, %d)\n", p->chave, p->conteudo);

    printf("Max:\n");
    p = TSmax(tab);
    printf("(%d, %d)\n", p->chave, p->conteudo);

    printf("Pred:\n");
    p = TSpred(tab, n / 2);
    printf("%d: ", n / 2);
    if (p != NULL)
        printf("(%d, %d)\n", p->chave, p->conteudo);
    else
        printf("Nao achou\n");

    printf("Suc:\n");
    p = TSsuc(tab, n / 2 + 1);
    printf("%d: ", n / 2 + 1);
    if (p != NULL)
        printf("(%d, %d)\n", p->chave, p->conteudo);
    else
        printf("Nao achou\n");

    printf("Perc:\n");
    TSperc(tab);

    printf("Selec:\n");
    p = TSselec(tab, n / 2);
    printf("%d: ", n / 2);
    printf("(%d, %d)\n", p->chave, p->conteudo);
    p = TSselec(tab, 6);
    printf("%d: ", 6);
    printf("(%d, %d)\n", p->chave, p->conteudo);

    printf("Rank:\n");
    printf("chave %d: %d\n", n / 2, TSrank(tab, n / 2));
    printf("chave %d: %d\n", n / 2 - 1, TSrank(tab, n / 2 - 1));
    printf("chave %d: %d\n", n / 2 + 1, TSrank(tab, n / 2 + 1));
    printf("chave %d: %d\n", -1, TSrank(tab, -1));

    return 0;
}

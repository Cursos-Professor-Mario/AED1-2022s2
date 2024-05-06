#include <stdio.h>
#include <stdlib.h>

#include "TSvetorOrdenado.h"

struct ts
{
    Item *v;
    int n;
};

void insertionSort(Item v[], int n)
{
    int i, j;
    Item aux;
    for (j = 1; j < n; j++)
    {
        aux = v[j];
        for (i = j - 1; i >= 0 && aux.chave < v[i].chave; i--)
            v[i + 1] = v[i];
        v[i + 1] = aux; /* por que i+1? */
    }
}

void insertionSortImproved(Item v[], int n)
{
    int i, j;
    Item aux;
    j = n - 1;
    for (i = n - 1; i > 0; i--)
        if (v[i - 1].chave > v[i].chave)
        {
            aux = v[i];
            v[i] = v[i - 1];
            v[i - 1] = aux;
            j = i;
        }
    for (j++; j < n; j++)
    {
        aux = v[j];
        for (i = j - 1;
             aux.chave < v[i].chave; i--)
            v[i + 1] = v[i];
        v[i + 1] = aux; /* por que i+1? */
    }
}

int buscaBinaria(Item v[], int n, Chave x)
{
    int e, m, d;
    e = -1;
    d = n;
    while (e + 1 < d)
    {
        m = (e + d) / 2;
        if (v[m].chave < x)
            e = m;
        else // v[m].chave >= x
            d = m;
    }
    return d;
}

TS *TScria(Item v[], int n)
{
    int i;
    TS *tab;
    tab = (TS *)malloc(sizeof(TS));
    tab->v = (Item *)malloc(n * sizeof(Item));
    tab->n = n;
    for (i = 0; i < n; i++)
        tab->v[i] = v[i];
    insertionSort(tab->v, tab->n);
    return tab;
}

Item *TSbusca(TS *tab, Chave x)
{
    int i;
    i = buscaBinaria(tab->v, tab->n, x);
    if (tab->v[i].chave == x)
        return &(tab->v[i]);
    return NULL;
}

Item *TSmin(TS *tab)
{
    return &(tab->v[0]);
}

Item *TSmax(TS *tab)
{
    return &(tab->v[tab->n - 1]);
}

Item *TSpred(TS *tab, Chave x)
{
    int i;
    i = buscaBinaria(tab->v, tab->n, x);
    if (tab->v[i].chave == x && i != 0)
        return &(tab->v[i - 1]);
    return NULL;
}

Item *TSsuc(TS *tab, Chave x)
{
    int i;
    i = buscaBinaria(tab->v, tab->n, x);
    if (tab->v[i].chave == x && i != tab->n - 1)
        return &(tab->v[i + 1]);
    return NULL;
}

void TSperc(TS *tab)
{
    int i;
    for (i = 0; i < tab->n; i++)
        printf("(%d, %d) ", tab->v[i].chave, tab->v[i].conteudo);
    printf("\n");
}

Item *TSselec(TS *tab, int pos)
{
    return &(tab->v[pos - 1]); // vetor começa em 0
}

int TSrank(TS *tab, Chave x)
{
    int i, pos;
    i = buscaBinaria(tab->v, tab->n, x);
    if (tab->v[i].chave == x)
        pos = i + 1;
    else
        pos = i;
    return pos;
}

#include <stdio.h>
#include <stdlib.h>

int buscaBinaria(int v[], int n, int x)
{
    int e, m, d;
    e = -1;
    d = n;
    while (e < d - 1)
    {
        m = (e + d) / 2;
        if (v[m] < x)
            e = m;
        else
            d = m;
    }
    return d;
}

int *busca(int v[], int n, int x)
{
    int i;
    i = buscaBinaria(v, n, x);
    if (v[i] == x)
        return &v[i];
    return NULL;
}

int *min(int v[], int n)
{
    return &v[0];
}

int *max(int v[], int n)
{
    return &v[n - 1];
}

int *pred(int v[], int n, int x)
{
    int i;
    i = buscaBinaria(v, n, x);
    if (v[i] == x && i != 0)
        return &v[i - 1];
    return NULL;
}

int *suc(int v[], int n, int x)
{
    int i;
    i = buscaBinaria(v, n, x);
    if (v[i] == x && i != n - 1)
        return &v[i + 1];
    return NULL;
}

void perc(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

int *selec(int v[], int n, int i)
{
    return &v[i - 1];
}

int rank(int v[], int n, int x)
{
    int i;
    i = buscaBinaria(v, n, x);
    if (v[i] == x)
        i++;
    return i;
}

int main(int argc, char **argv)
{
    int i, n;
    int *p;
    int *v;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros! Ex.: .\\vetorOrdenado 10");
        return 0;
    }

    n = atoi(argv[1]);

    v = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        v[i] = 2 * i;

    printf("Busca:\n");
    p = busca(v, n, n / 2);
    printf("%d: ", n / 2);
    if (p != NULL)
        printf("%d\n", *p);
    else
        printf("Nao achou\n");
    printf("%d: ", n / 2 + 1);
    p = busca(v, n, n / 2 + 1);
    if (p != NULL)
        printf("%d\n", *p);
    else
        printf("Nao achou\n");
    printf("%d: ", n / 2 - 1);
    p = busca(v, n, n / 2 - 1);
    if (p != NULL)
        printf("%d\n", *p);
    else
        printf("Nao achou\n");

    printf("Min:\n");
    p = min(v, n);
    printf("%d\n", *p);

    printf("Max:\n");
    p = max(v, n);
    printf("%d\n", *p);

    printf("Pred:\n");
    p = pred(v, n, n / 2);
    printf("%d: ", n / 2);
    if (p != NULL)
        printf("%d\n", *p);
    else
        printf("Nao achou\n");

    printf("Suc:\n");
    printf("%d: ", n / 2);
    p = suc(v, n, n / 2);
    if (p != NULL)
        printf("%d\n", *p);
    else
        printf("Nao achou\n");

    printf("Perc:\n");
    perc(v, n);

    printf("Selec:\n");
    p = selec(v, n, n / 2);
    printf("%d: ", n / 2);
    printf("%d\n", *p);
    p = selec(v, n, 6);
    printf("%d: ", 6);
    printf("%d\n", *p);

    printf("Rank:\n");
    printf("chave %d: %d\n", n / 2, rank(v, n, n / 2));
    printf("chave %d: %d\n", n / 2 - 1, rank(v, n, n / 2 - 1));
    printf("chave %d: %d\n", n / 2 + 1, rank(v, n, n / 2 + 1));
    printf("chave %d: %d\n", -1, rank(v, n, -1));

    return 0;
}
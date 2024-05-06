#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int buscaSequencial1(int v[], int n, int x)
{
    int i = 0;
    while (i < n && v[i] != x)
        i++;
    if (i < n)
        return i;
    return -1;
}

int buscaSequencial2(int v[], int n, int x)
{
    int i = 0;
    while (i < n && v[i] < x)
        i++;
    if (i < n && v[i] == x)
        return i;
    return -1;
    // return i;
}

int buscaBinariaR(int v[], int e, int d, int x)
{
    int m;
    if (d < e)
    {
        return -1;
        // return e;
    }
    m = (e + d) / 2;
    if (v[m] == x)
        return m;
    if (v[m] < x)
        return buscaBinariaR(v, m + 1, d, x);
    return buscaBinariaR(v, e, m - 1, x);
}

int buscaBinaria2(int v[], int n, int x)
{
    return buscaBinariaR(v, 0, n - 1, x);
}

int buscaBinaria(int v[], int n, int x)
{
    int e, m, d;
    e = 0;
    d = n - 1;
    while (e <= d)
    {
        m = (e + d) / 2;
        if (v[m] == x)
            return m;
        if (v[m] < x)
            e = m + 1;
        else
            d = m - 1;
    }
    return -1;
    // return e;
}

int main(int argc, char **argv)
{
    int stime, etime;
    int i, n;
    int *v;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros. Ex: buscaVetorOrdenado 200000000");
        return 0;
    }

    n = atoi(argv[1]);

    v = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        v[i] = i;

    stime = time(NULL);
    printf("%d | ", buscaSequencial1(v, n, -1));
    printf("%d | ", buscaSequencial1(v, n, 0));
    printf("%d | ", buscaSequencial1(v, n, 1));
    printf("%d | ", buscaSequencial1(v, n, n / 2));
    printf("%d | ", buscaSequencial1(v, n, n - 1));
    printf("%d\n", buscaSequencial1(v, n, n));
    etime = time(NULL);
    printf("buscaSequencial1 levou tempo = %d\n", etime - stime);

    stime = time(NULL);
    printf("%d | ", buscaSequencial2(v, n, -1));
    printf("%d | ", buscaSequencial2(v, n, 0));
    printf("%d | ", buscaSequencial2(v, n, 1));
    printf("%d | ", buscaSequencial2(v, n, n / 2));
    printf("%d | ", buscaSequencial2(v, n, n - 1));
    printf("%d\n", buscaSequencial2(v, n, n));
    etime = time(NULL);
    printf("buscaSequencial1 levou tempo = %d\n", etime - stime);

    stime = time(NULL);
    printf("%d | ", buscaBinaria(v, n, -1));
    printf("%d | ", buscaBinaria(v, n, 0));
    printf("%d | ", buscaBinaria(v, n, 1));
    printf("%d | ", buscaBinaria(v, n, n / 2));
    printf("%d | ", buscaBinaria(v, n, n - 1));
    printf("%d\n", buscaBinaria(v, n, n));
    etime = time(NULL);
    printf("buscaSequencial1 levou tempo = %d\n", etime - stime);

    stime = time(NULL);
    printf("%d | ", buscaBinaria2(v, n, -1));
    printf("%d | ", buscaBinaria2(v, n, 0));
    printf("%d | ", buscaBinaria2(v, n, 1));
    printf("%d | ", buscaBinaria2(v, n, n / 2));
    printf("%d | ", buscaBinaria2(v, n, n - 1));
    printf("%d\n", buscaBinaria2(v, n, n));
    etime = time(NULL);
    printf("buscaSequencial1 levou tempo = %d\n", etime - stime);

    return 0;
}
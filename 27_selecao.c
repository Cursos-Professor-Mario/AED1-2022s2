#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAI(i) (i - 1) / 2
#define FILHO_ESQ(i) (2 * i + 1)
#define FILHO_DIR(i) (2 * i + 2)

void imprime(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void troca(int *a, int *b)
{
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

// devolve o k-ésimo menor elemento
int selecao1(int v[], int n, int k)
{
    int i, j, ind_min;
    // em cada iteração encontra o i-ésimo menor
    for (i = 0; i <= k; i++)
    {
        ind_min = i;
        for (j = i + 1; j < n; j++)
            if (v[j] < v[ind_min])
                ind_min = j;
        troca(&v[i], &v[ind_min]);
    }
    return v[k];
}

void desceHeap(int v[], int m, int k)
{
    int p = k, f;
    while (FILHO_ESQ(p) < m && (v[FILHO_ESQ(p)] > v[p] || (FILHO_DIR(p) < m && v[FILHO_DIR(p)] > v[p])))
    {
        f = FILHO_ESQ(p);
        if (FILHO_DIR(p) < m &&
            v[FILHO_DIR(p)] > v[f])
            f = FILHO_DIR(p);
        troca(&v[p], &v[f]);
        p = f;
    }
}

int selecao2(int v[], int n, int k)
{
    int i, m;
    for (i = n / 2; i >= 0; i--)
        desceHeap(v, n, i);
    // em cada iteração encontra o (m-1)-ésimo menor
    for (m = n; m > k; m--)
    {
        troca(&v[0], &v[m - 1]);
        desceHeap(v, m - 1, 0);
    }
    return v[k];
}

int selecao(int v[], int n, int k)
{
    if (k < n)
    {
        return selecao1(v, n, k);
        // return selecao2(v, n, k);
    }
    printf("Erro! k = %d >= %d = n\n", k, n);
    exit(1);
}

int main(int argc, char *argv[])
{
    int i, n, k;
    int stime, etime;

    if (argc != 3)
    {
        printf("Numero incorreto de parametros. Ex: selecao 10 4\n");
        return 0;
    }

    n = atoi(argv[1]);
    k = atoi(argv[2]);

    int *v = (int *)malloc(n * sizeof(int));

    // ordem direta
    printf("ordem direta\n");
    for (i = 0; i < n; i++)
        v[i] = i * 10;
    imprime(v, n);

    stime = time(NULL);
    printf("%d-esimo = %d\n", k, selecao(v, n, k));
    etime = time(NULL);
    printf("selecao com n = %d leva tempo = %d\n", n, etime - stime);

    // ordem alternada
    printf("ordem alternada\n");
    for (i = 0; i < n; i += 2)
        v[i] = (i / 2) * 10;
    for (i = 1; i < n; i += 2)
        v[i] = (n - i / 2 - 1) * 10;
    imprime(v, n);

    stime = time(NULL);
    printf("%d-esimo = %d\n", k, selecao(v, n, k));
    etime = time(NULL);
    printf("selecao com n = %d leva tempo = %d\n", n, etime - stime);

    // ordem inversa
    printf("ordem inversa\n");
    for (i = 0; i < n; i++)
        v[i] = (n - i - 1) * 10;
    imprime(v, n);

    stime = time(NULL);
    printf("%d-esimo = %d\n", k, selecao(v, n, k));
    etime = time(NULL);
    printf("selecao com n = %d leva tempo = %d\n", n, etime - stime);

    return 0;
}

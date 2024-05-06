#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_MAX 1000000

void imprime(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

int selecao(int v[], int n, int k)
{
    return v[k];
}

int buscaI(int v[], int n, int x)
{
    int k;
    k = n - 1;
    while (k >= 0 && v[k] != x)
        k -= 1;
    return k;
}

int buscaIneficiente(int v[], int n, int x)
{
    int k = 0; // deselegante
    int sol = -1;
    for (k = n - 1; k >= 0; --k) // ineficiente
        if (v[k] == x)
            sol = k; // deselegante
    return sol;
}

int buscaR(int v[], int n, int x)
{
    if (n == 0)
        return -1;
    if (x == v[n - 1])
        return n - 1;
    return buscaR(v, n - 1, x);
}

int removeI(int v[], int n, int k)
{
    int j;
    for (j = k + 1; j < n; j++)
        v[j - 1] = v[j];
    return n - 1;
}

int removeR(int v[], int n, int k)
{
    if (k == n - 1)
        return n - 1;
    v[k] = v[k + 1];
    return removeR(v, n, k + 1);
}

int insereI(int v[], int n, int x, int k)
{
    int j;
    for (j = n; j > k; j--)
        v[j] = v[j - 1];
    v[k] = x;
    return n + 1;
}

int insereR(int v[], int n, int x, int k)
{
    if (k == n)
        v[n] = x;
    else
    {
        v[n] = v[n - 1];
        insereR(v, n - 1, x, k);
    }
    return n + 1;
}

int removeTodos(int v[], int n, int x)
{
    int k;
    while ((k = buscaI(v, n, x)) != -1)
        n = removeI(v, n, k);
    return n;
}

int removeTodos2(int v[], int n, int x)
{
    int i = 0, j;
    for (j = 0; j < n; j++)
        if (v[j] != x)
        {
            v[i] = v[j];
            i++;
        }
    return i;
}

int main(int argc, char *argv[])
{
    int i, n, aux;
    int stime, etime;

    int v[TAM_MAX];

    // int *v = (int *)malloc(TAM_MAX * sizeof(int));

    if (argc != 2)
    {
        printf("Numero incorreto de parametros. Ex: vetor 10\n");
        return 0;
    }

    n = atoi(argv[1]);
    aux = n;

    // for (i = 0; i < n; i++)
    //     v[i] = i;

    // imprime(v, n);

    // printf("buscaI de %d = %d\n", n / 2, buscaI(v, n, n / 2));
    // printf("buscaR de %d = %d\n", n / 2, buscaR(v, n, n / 2));

    // n = removeI(v, n, n / 2);
    // imprime(v, n);
    // n = removeR(v, n, n / 2);
    // imprime(v, n);

    // n = insereI(v, n, 0, 0);
    // imprime(v, n);
    // n = insereR(v, n, n, n);
    // imprime(v, n);

    // n = removeTodos2(v, n, 0);
    // imprime(v, n);
    // n = removeTodos(v, n, 9);
    // imprime(v, n);
    // n = removeTodos2(v, n, 3);
    // imprime(v, n);

    n = aux;
    for (i = 0; i < n / 2; i++)
        v[i] = 0;
    for (i = n / 2 + 1; i < n; i++)
        v[i] = 1;
    // imprime(v, n);
    stime = time(NULL);
    n = removeTodos2(v, n, 0);
    etime = time(NULL);
    // imprime(v, n);
    printf("tempo de removeTodos2 = %d\n", etime - stime);

    n = aux;
    for (i = 0; i < n / 2; i++)
        v[i] = 0;
    for (i = n / 2 + 1; i < n; i++)
        v[i] = 1;
    // imprime(v, n);
    stime = time(NULL);
    n = removeTodos(v, n, 0);
    etime = time(NULL);
    // imprime(v, n);
    printf("tempo de removeTodos = %d\n", etime - stime);

    return 0;
}
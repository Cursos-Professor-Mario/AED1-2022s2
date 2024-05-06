#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long int fibonacciR(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fibonacciR(n - 1) + fibonacciR(n - 2);
}

long long int fibonacciI(int n)
{
    int i;
    long long int proximo, anterior, atual;
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    anterior = 0; // Fi-1
    atual = 1;    // Fi
    for (i = 1; i < n; i++)
    {
        proximo = anterior + atual;
        anterior = atual;
        atual = proximo;
    }
    return atual;
}

int main(int argc, char *argv[])
{
    int stime, etime;
    int n;
    if (argc != 2)
    {
        printf("Numero incorreto de parametros. Ex.: fibonacci 45");
        return 0;
    }

    n = atoi(argv[1]);

    printf("Testando fibonacciR:\n");
    stime = time(NULL);
    printf("%d\n", fibonacciR(n));
    etime = time(NULL);
    printf("%d segundos\n", etime - stime);

    printf("Testando fibonacciI:\n");
    stime = time(NULL);
    printf("%d\n", fibonacciI(n));
    etime = time(NULL);
    printf("%d segundos\n", etime - stime);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int maximoRend(int v[], int n)
{
    int x; // auxiliar que guarda o máximo do subproblema
    if (n == 1)
        return v[0];
    x = maximoRend(v, n - 1);
    if (x > v[n - 1])
        return x;
    return v[n - 1];
}

int maximoRbegin(int v[], int inicio, int n)
{
    int x; // auxiliar que guarda o máximo do subproblema
    if (inicio == n - 1)
        return v[inicio];
    x = maximoRbegin(v, inicio + 1, n);
    if (x > v[inicio])
        return x;
    return v[inicio];
}

int maximo(int v[], int n)
{
    return maximoRbegin(v, 0, n);
}

int maximoI(int v[], int n)
{
    int max, i;
    max = v[0];
    for (i = 1; i < n; i++)
        if (max < v[i])
            max = v[i];
    return max;
}

int maximoR(int v[], int n)
{
    if (n == 1)
        return v[0];
    if (maximoR(v, n - 1) > v[n - 1])
        return maximoR(v, n - 1);
    return v[n - 1];
}

int main(int argc, char **argv)
{
    int stime, etime;
    int i, n = 32;
    printf("Digite o tamanho do vetor\n");
    scanf("%d", &n);
    int v[n];
    for (i = 0; i < n; i++)
        v[i] = i;

    stime = time(NULL);
    printf("%d\n", maximoRend(v, n));
    printf("%d\n", maximo(v, n));
    printf("%d\n", maximoI(v, n));
    etime = time(NULL);
    printf("%d seconds\n", etime - stime);
    stime = time(NULL);
    printf("%d\n", maximoR(v, n));
    etime = time(NULL);
    printf("%d seconds\n", etime - stime);

    for (i = 0; i < n; i++)
        v[i] = n - 1 - i;

    stime = time(NULL);
    printf("%d\n", maximoRend(v, n));
    printf("%d\n", maximo(v, n));
    printf("%d\n", maximoI(v, n));
    etime = time(NULL);
    printf("%d seconds\n", etime - stime);
    stime = time(NULL);
    printf("%d\n", maximoR(v, n));
    etime = time(NULL);
    printf("%d seconds\n", etime - stime);
    return 0;
}
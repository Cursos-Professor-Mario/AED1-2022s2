#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG 0

void imprime(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void selectionSort(int v[], int n)
{
    int i, j, ind_min, aux;
    for (i = 0; i < n - 1; i++)
    {
        ind_min = i;
        for (j = i + 1; j < n; j++)
            if (v[j] < v[ind_min])
                ind_min = j;
        aux = v[i];
        v[i] = v[ind_min];
        v[ind_min] = aux;
    }
}

int main(int argc, char *argv[])
{
    int i, n, desloc, aux;
    int stime, etime;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros. Ex: .\\selectionSort 10\n");
        return 0;
    }

    n = atoi(argv[1]);

    int *v = (int *)malloc(n * sizeof(int));

    // ordem direta
    for (i = 0; i < n; i++)
        v[i] = i;
    if (DEBUG == 1)
        imprime(v, n);

    stime = time(NULL);
    selectionSort(v, n);
    etime = time(NULL);
    if (DEBUG == 1)
        imprime(v, n);
    printf("tempo selectionSort ordem direta = %d\n", etime - stime);

    // ordem aleatória - Knuth shuffle
    for (i = 0; i < n; i++)
        v[i] = i;
    for (i = 0; i < n; i++)
    {
        // número pseudoaleatório entre 0 e n - i - 1
        desloc = (int)((double)rand() / ((double)RAND_MAX + 1) * (n - i));
        aux = v[i + desloc];
        v[i + desloc] = v[i];
        v[i] = aux;
    }
    if (DEBUG == 1)
        imprime(v, n);

    stime = time(NULL);
    selectionSort(v, n);
    etime = time(NULL);
    if (DEBUG == 1)
        imprime(v, n);
    printf("tempo selectionSort ordem aleatoria = %d\n", etime - stime);

    // ordem inversa
    for (i = 0; i < n; i++)
        v[i] = n - i - 1;
    if (DEBUG == 1)
        imprime(v, n);

    stime = time(NULL);
    selectionSort(v, n);
    etime = time(NULL);
    if (DEBUG == 1)
        imprime(v, n);
    printf("tempo selectionSort ordem inversa = %d\n", etime - stime);

    return 0;
}

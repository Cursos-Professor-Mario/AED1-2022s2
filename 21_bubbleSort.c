#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void imprime(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void bubbleSort1(int v[], int n)
{
    int i, aux, mudou;
    do
    {
        mudou = 0;
        for (i = 1; i < n; i++)
            if (v[i - 1] > v[i])
            {
                aux = v[i - 1];
                v[i - 1] = v[i];
                v[i] = aux;
                mudou = 1;
            }
    } while (mudou == 1);
}

void bubbleSort2(int v[], int n)
{
    int j, i, aux;
    for (j = 0; j < n; j++)
        for (i = 1; i < n; i++)
            if (v[i - 1] > v[i])
            {
                aux = v[i - 1];
                v[i - 1] = v[i];
                v[i] = aux;
            }
}

void bubbleSort3(int v[], int n)
{
    int j, i, aux;
    for (j = 0; j < n; j++)
        for (i = 1; i < n - j; i++)
            if (v[i - 1] > v[i])
            {
                aux = v[i - 1];
                v[i - 1] = v[i];
                v[i] = aux;
            }
}

void bubbleSort4(int v[], int n)
{
    int j, i, aux, pos_ult_inv, lim_dir;
    lim_dir = n;
    for (j = 0; j < n; j++)
    {
        pos_ult_inv = 0;
        for (i = 1; i < lim_dir; i++)
            if (v[i - 1] > v[i])
            {
                aux = v[i - 1];
                v[i - 1] = v[i];
                v[i] = aux;
                pos_ult_inv = i;
            }
        lim_dir = pos_ult_inv;
    }
}

void bubbleSort(int v[], int n)
{
    bubbleSort4(v, n);
}

int main(int argc, char *argv[])
{
    int i, n, desloc, aux;
    int stime, etime;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros. Ex: .\\bubblesort 10\n");
        return 0;
    }

    n = atoi(argv[1]);

    int *v = (int *)malloc(n * sizeof(int));

    // ordem direta
    for (i = 0; i < n; i++)
        v[i] = i;
    // imprime(v, n);

    stime = time(NULL);
    bubbleSort(v, n);
    etime = time(NULL);
    // imprime(v, n);
    printf("tempo bubbleSort ordem direta = %d\n", etime - stime);

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
    // imprime(v, n);

    stime = time(NULL);
    bubbleSort(v, n);
    etime = time(NULL);
    // imprime(v, n);
    printf("tempo bubbleSort ordem aleatoria = %d\n", etime - stime);

    // ordem inversa
    for (i = 0; i < n; i++)
        v[i] = n - i - 1;
    // imprime(v, n);

    stime = time(NULL);
    bubbleSort(v, n);
    etime = time(NULL);
    // imprime(v, n);
    printf("tempo bubbleSort ordem inversa = %d\n", etime - stime);

    return 0;

    for (i = 0; i < n; i++)
        v[i] = n - i - 1;
    stime = time(NULL);
    bubbleSort1(v, n);
    etime = time(NULL);
    printf("Tempo do bubblesort1 para %d = %d\n", n, etime - stime);

    for (i = 0; i < n; i++)
        v[i] = n - i - 1;
    stime = time(NULL);
    bubbleSort2(v, n);
    etime = time(NULL);
    printf("Tempo do bubblesort2 para %d = %d\n", n, etime - stime);

    for (i = 0; i < n; i++)
        v[i] = n - i - 1;
    stime = time(NULL);
    bubbleSort3(v, n);
    etime = time(NULL);
    printf("Tempo do bubblesort3 para %d = %d\n", n, etime - stime);

    for (i = 0; i < n; i++)
        v[i] = n - i - 1;
    stime = time(NULL);
    bubbleSort4(v, n);
    etime = time(NULL);
    printf("Tempo do bubblesort4 para %d = %d\n", n, etime - stime);

    return 0;
}

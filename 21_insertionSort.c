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

void insertionSort1(int v[], int n)
{
    int i, j, aux;
    for (j = 1; /* 1 */ j < n; j++)
    {
        aux = v[j];
        for (i = j - 1; /* 2 */ i >= 0 && aux < v[i]; i--)
            v[i + 1] = v[i]; // desloca à direita os maiores
        v[i + 1] = aux;      // por que i+1?
    }
}

void insertionSort2(int v[], int n)
{
    int i, j, aux;
    for (i = n - 1; i > 0; i--)
        if (v[i - 1] > v[i])
        {
            aux = v[i];
            v[i] = v[i - 1];
            v[i - 1] = aux;
        }
    for (j = 2; j < n; j++)
    {
        aux = v[j];
        for (i = j - 1; aux < v[i]; i--)
            v[i + 1] = v[i]; // desloca à direita os maiores
        v[i + 1] = aux;      // por que i+1?
    }
}

void insertionSort3(int v[], int n)
{
    int i, j, aux;
    j = n - 1;
    for (i = n - 1; i > 0; i--)
        if (v[i - 1] > v[i])
        {
            aux = v[i];
            v[i] = v[i - 1];
            v[i - 1] = aux;
            j = i; // guarda a posição da troca
        }
    for (j++; j < n; j++)
    {
        aux = v[j];
        for (i = j - 1; aux < v[i]; i--)
            v[i + 1] = v[i]; // desloca à direita os maiores
        v[i + 1] = aux;      // por que i+1?
    }
}

void insertionSort(int v[], int n)
{
    insertionSort1(v, n);
}

int main(int argc, char *argv[])
{
    int i, n, aux, desloc;
    int stime, etime;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros. Ex: .\\insertionsort 10\n");
        return 0;
    }

    n = atoi(argv[1]);

    int *v = (int *)malloc(n * sizeof(int));

    // ordem direta
    for (i = 0; i < n; i++)
        v[i] = i;
    // imprime(v, n);

    stime = time(NULL);
    insertionSort(v, n);
    etime = time(NULL);
    // imprime(v, n);
    printf("tempo insertionSort ordem direta = %d\n", etime - stime);

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
    insertionSort(v, n);
    etime = time(NULL);
    // imprime(v, n);
    printf("tempo insertionSort ordem aleatoria = %d\n", etime - stime);

    // ordem inversa
    for (i = 0; i < n; i++)
        v[i] = n - i - 1;
    // imprime(v, n);

    stime = time(NULL);
    insertionSort(v, n);
    etime = time(NULL);
    // imprime(v, n);
    printf("tempo insertionSort ordem inversa = %d\n", etime - stime);

    // segunda metade invertida
    for (i = 0; i < n / 2; i++)
        v[i] = i;
    for (i = n / 2; i < n; i++)
        v[i] = n + (n / 2 - i) - 1;
    // imprime(v, n);

    stime = time(NULL);
    insertionSort(v, n);
    etime = time(NULL);
    // imprime(v, n);
    printf("tempo insertionSort segunda metade invertida = %d\n", etime - stime);

    return 0;

    for (i = 0; i < n; i++)
        v[i] = n - i - 1;
    stime = time(NULL);
    insertionSort1(v, n);
    etime = time(NULL);
    printf("Tempo do insertionSort1 para %d = %d\n", n, etime - stime);

    for (i = 0; i < n; i++)
        v[i] = n - i - 1;
    stime = time(NULL);
    insertionSort2(v, n);
    etime = time(NULL);
    printf("Tempo do insertionSort2 para %d = %d\n", n, etime - stime);

    for (i = 0; i < n; i++)
        v[i] = n - i - 1;
    stime = time(NULL);
    insertionSort3(v, n);
    etime = time(NULL);
    printf("Tempo do insertionSort3 para %d = %d\n", n, etime - stime);

    return 0;
}

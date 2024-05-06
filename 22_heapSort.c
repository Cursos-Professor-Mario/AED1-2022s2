#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PAI(i) (i - 1) / 2
#define FILHO_ESQ(i) (2 * i + 1)
#define FILHO_DIR(i) (2 * i + 2)

#define IMPRIMIR 0

void troca(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void *mallocSafe(unsigned tam)
{
    void *p = malloc(tam);
    if (p == NULL)
    {
        printf("Deu ruim! malloc devolveu NULL");
        exit(EXIT_FAILURE);
    }
    return p;
}

void imprime(int v[], int n)
{
    if (IMPRIMIR)
    {
        int i;
        for (i = 0; i < n; i++)
            printf("%d ", v[i]);
        printf("\n");
    }
}

void imprimeHieraquico(int v[], int n)
{
    if (IMPRIMIR)
    {
        int i;
        for (i = 0; i < n; i++)
        {
            if (log2(i + 1) == floor(log2(i + 1)))
                printf("\n");
            printf("%d ", v[i]);
        }
        printf("\n");
    }
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

// sobe o elemento em v[pos] até restaurar a propriedade do heap
void sobeHeap(int v[], int pos)
{
    int corr = pos;
    while (corr > 0 && v[PAI(corr)] < v[corr])
    {
        troca(&v[corr], &v[PAI(corr)]);
        corr = PAI(corr);
    }
}

int insereHeap(int v[], int m, int x)
{
    v[m] = x;
    sobeHeap(v, m);
    return m + 1;
}

// desce o elemento em v[pos] até restaurar a propriedade do heap
void desceHeap(int v[], int m, int pos)
{
    int corr = pos, filho;
    while (FILHO_ESQ(corr) < m && (v[FILHO_ESQ(corr)] > v[corr] || (FILHO_DIR(corr) < m && v[FILHO_DIR(corr)] > v[corr])))
    {
        filho = FILHO_ESQ(corr);
        if (FILHO_DIR(corr) < m && v[FILHO_DIR(corr)] > v[filho])
            filho = FILHO_DIR(corr);
        troca(&v[corr], &v[filho]);
        corr = filho;
    }
}

int removeHeap(int v[], int m, int *px)
{
    *px = v[0];
    troca(&v[0], &v[m - 1]);
    desceHeap(v, m, 0);
    return m - 1;
}

void heapSort1(int v[], int n)
{
    int i, m;
    for (i = 1; i < n; i++) // construindo o heap em tempo O(n lg n)
        sobeHeap(v, i);
    for (m = n; m > 0; m--)
    {
        troca(&v[0], &v[m - 1]); // colocando o máximo no final
        desceHeap(v, m - 1, 0);  // restaurando o Heap
    }
}

void heapSort2(int v[], int n)
{
    int i, m;
    for (i = n / 2; i >= 0; i--) // construindo o Heap em tempo O(n)
        desceHeap(v, n, i);
    for (m = n; m > 0; m--)
    {
        troca(&v[0], &v[m - 1]); // colocando o máximo no final
        desceHeap(v, m - 1, 0);  // restaurando o Heap
    }
}

void heapSort3(int v[], int n)
{
    int i, m, *w;
    w = mallocSafe(sizeof(int) * n);
    for (i = 0; i < n; i++) // copiando para o vetor do heap
        w[i] = -v[i];
    for (i = 1; i < n; i++) // construindo heap de mínimo em w
        sobeHeap(w, i);
    for (m = n; m > 0; m--)
    {
        v[n - m] = -w[0];       // colocando o mínimo no vetor original
        w[0] = w[m - 1];        // colocando o último na raiz do heap
        desceHeap(w, m - 1, 0); // restaurando o heap
    }
    free(w);
}

int main(int argc, char *argv[])
{
    int i, n, m, *v;
    int stime, etime;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros. Ex.: .\\heapSort 10\n");
        return 0;
    }

    n = atoi(argv[1]);

    v = mallocSafe(sizeof(int) * 2 * n);
    m = n;

    printf("Preenchendo vetor em ordem direta\n");
    for (i = 0; i < m; i++)
        v[i] = i;
    imprime(v, m);

    printf("Criando um max heap mandando todos subirem da esquerda pra direita\n");
    stime = time(NULL);
    for (i = 1; i < m; i++)
        sobeHeap(v, i);
    etime = time(NULL);
    printf("Tempo = %d\n", etime - stime);
    imprime(v, m);
    imprimeHieraquico(v, m);

    printf("Preenchendo vetor em ordem direta\n");
    for (i = 0; i < m; i++)
        v[i] = i;
    imprime(v, m);

    printf("Heapify: criando um max heap mandando todos descerem da direita pra esquerda\n");
    stime = time(NULL);
    for (i = m / 2; i >= 0; i--)
        desceHeap(v, m, i);
    etime = time(NULL);
    printf("Tempo = %d\n", etime - stime);
    imprime(v, m);
    imprimeHieraquico(v, m);

    // return 0;

    printf("Preenchendo vetor em ordem direta\n");
    for (i = 0; i < n; i++)
        v[i] = i;
    imprime(v, n);

    // printf("Preenchendo vetor em ordem reversa\n");
    // for (i = 0; i < n; i++)
    //     v[i] = n - i - 1;
    // imprime(v, n);

    stime = time(NULL);
    printf("Ordenando com heapSort1\n");
    heapSort1(v, n);
    imprime(v, n);
    etime = time(NULL);
    printf("Tempo = %d\n", etime - stime);

    printf("Preenchendo vetor em ordem direta\n");
    for (i = 0; i < n; i++)
        v[i] = i;
    imprime(v, n);

    // printf("Preenchendo vetor em ordem reversa\n");
    // for (i = 0; i < n; i++)
    //     v[i] = n - i - 1;
    // imprime(v, n);

    stime = time(NULL);
    printf("Ordenando com heapSort2\n");
    heapSort2(v, n);
    imprime(v, n);
    etime = time(NULL);
    printf("Tempo = %d\n", etime - stime);

    printf("Preenchendo vetor em ordem direta\n");
    for (i = 0; i < n; i++)
        v[i] = i;
    imprime(v, n);

    // printf("Preenchendo vetor em ordem reversa\n");
    // for (i = 0; i < n; i++)
    //     v[i] = n - i - 1;
    // imprime(v, n);

    stime = time(NULL);
    printf("Ordenando com heapSort3\n");
    heapSort3(v, n);
    imprime(v, n);
    etime = time(NULL);
    printf("Tempo = %d\n", etime - stime);

    printf("Preenchendo vetor em ordem direta\n");
    for (i = 0; i < n; i++)
        v[i] = i;
    imprime(v, n);

    // printf("Preenchendo vetor em ordem reversa\n");
    // for (i = 0; i < n; i++)
    //     v[i] = n - i - 1;
    // imprime(v, n);

    stime = time(NULL);
    printf("Ordenando com selectionSort\n");
    selectionSort(v, n);
    imprime(v, n);
    etime = time(NULL);
    printf("Tempo = %d\n", etime - stime);

    free(v);

    return 0;
}
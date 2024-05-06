#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define FILHO_ESQ(i) (2 * i + 1)
#define FILHO_DIR(i) (2 * i + 2)
#define PAI(i) ((i - 1) / 2)

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
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void imprimeHieraquico(int v[], int n)
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
    desceHeap(v, m - 1, 0);
    return m - 1;
}

int main(int argc, char *argv[])
{
    int i, n, m, *v;
    int stime, etime;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros. Ex.: .\\testaHeap 10\n");
        return 0;
    }

    n = atoi(argv[1]);

    i = 1;
    printf("%d\n", i);
    printf("%d\n", PAI(i));
    printf("%d\n", FILHO_ESQ(i));
    printf("%d\n", FILHO_DIR(i));

    v = mallocSafe(sizeof(int) * 2 * n);
    m = n;

    printf("Preenchendo vetor em ordem direta\n");
    for (i = 0; i < m; i++)
        v[i] = i;
    imprime(v, m);

    printf("Testando sobeHeap com elemento da ultima posicao\n");
    sobeHeap(v, m - 1);
    imprime(v, m);

    stime = time(NULL);
    printf("Criando um max heap mandando todos subirem da esquerda pra direita\n");
    for (i = 1; i < m; i++)
        sobeHeap(v, i);
    imprime(v, m);
    imprimeHieraquico(v, m);
    etime = time(NULL);
    printf("Tempo para criar heap de tamanho %d com sobeHeap = %d\n", m, etime - stime);

    printf("Inserindo novo elemento no max heap\n");
    m = insereHeap(v, m, 999);
    imprime(v, m);

    printf("Criando novo max heap usando insereHeap - ordem direta\n");
    m = 0;
    for (i = 0; i < n; i++)
        m = insereHeap(v, m, i);
    imprime(v, m);
    imprimeHieraquico(v, m);

    printf("Criando novo max heap usando insereHeap - ordem inversa\n");
    m = 0;
    for (i = 0; i < n; i++)
        m = insereHeap(v, m, n - i - 1);
    imprime(v, m);
    // imprimeHieraquico(v, m);

    printf("Testando desceHeap com elemento da primeira posicao\n");
    v[0] = 0;
    desceHeap(v, m, 0);
    imprime(v, m);

    int x;

    printf("Removendo o maior elemento do vetor usando removeHeap\n");
    m = removeHeap(v, m, &x);
    printf("maior = %d\n", x);
    imprime(v, m);

    printf("Preenchendo vetor em ordem direta\n");
    for (i = 0; i < m; i++)
        v[i] = i;
    imprime(v, m);

    stime = time(NULL);
    printf("Criando um max heap mandando todos descerem da direita pra esquerda\n");
    for (i = m / 2; i >= 0; i--)
        desceHeap(v, m, i);
    imprime(v, m);
    imprimeHieraquico(v, m);
    etime = time(NULL);
    printf("Tempo para criar heap de tamanho %d usando desceHeap = %d\n", m, etime - stime);

    free(v);

    return 0;
}
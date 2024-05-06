#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

// A função recebe um inteiro x, uma matriz de inteiros A e a dimensão da matriz n, sendo 0 <= x < n.
// Ela devolve um vetor contendo a distância de x até cada elemento entre 0 e n-1.
int *distancias(int **A, int n, int x)
{
    int i, y;
    int *dist;
    Fila *q;

    dist = malloc(n * sizeof(int));
    /* inicializa a fila */
    q = criaFila();
    /* inicializa todos como não encontrados, exceto pelo x */
    for (i = 0; i < n; i++)
        dist[i] = -1;
    dist[x] = 0;
    /* colocando x na fila */
    insereFila(q, x);
    /* enquanto a fila dos ativos (encontrados 
    mas não visitados) não estiver vazia */
    while (!filaVazia(q))
    {
        /* remova o mais antigo da fila */
        y = removeFila(q);
        /* para cada vizinho deste que ainda não foi encontrado */
        for (i = 0; i < n; i++)
            if (A[y][i] == 1 && dist[i] == -1)
            {
                /* calcule a distancia do vizinho 
                e o coloque na fila */
                dist[i] = dist[y] + 1;
                insereFila(q, i);
            }
    }
    q = liberaFila(q);
    return dist;
}

int main(int argc, char *argv[])
{
    int **A, i, j, n, *dist;

    printf("Digite o numero de cidades.\n");
    scanf("%d", &n);

    A = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        A[i] = malloc(n * sizeof(int));

    printf("Digite a matriz da rede.\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    dist = distancias(A, n, 0);
    dist = distancias(A, n, n / 2);

    printf("cidades:    ");
    for (i = 0; i < n; i++)
        printf("%d ", i);
    printf("\n");
    printf("distancias: ");
    for (i = 0; i < n; i++)
        printf("%d ", dist[i]);
    printf("\n");

    free(dist);
    return 0;
}
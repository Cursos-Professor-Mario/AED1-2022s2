#include <stdio.h>
#include <stdlib.h>

// A função recebe uma matriz de inteiros Rede de dimensão n e um
// inteiro origem, sendo 0 <= origem < n. Ela devolve um vetor
// contendo a distância de origem até cada elemento entre 0 e n-1.
int *distancias(int **Rede, int n, int origem)
{
    int i, corr; // auxiliar que guarda a cidade corrente
    int *dist;
    int *fila;
    int ini, fim;

    dist = malloc(n * sizeof(int));
    /* inicializa a fila */
    fila = malloc(n * sizeof(int));
    ini = 0;
    fim = 0;
    /* inicializa todos como não encontrados, exceto pela origem */
    for (i = 0; i < n; i++)
        dist[i] = -1;
    dist[origem] = 0;
    /* colocando origem na fila */
    fila[fim++] = origem;
    /* enquanto a fila dos ativos (encontrados mas não visitados) não estiver vazia */
    while (fim != ini)
    {
        /* remova o mais antigo da fila */
        corr = fila[ini++];
        /* para cada vizinho deste que ainda não foi encontrado */
        for (i = 0; i < n; i++)
            if (Rede[corr][i] == 1 && dist[i] == -1)
            {
                /* calcule a distancia do vizinho e o coloque na fila */
                dist[i] = dist[corr] + 1;
                fila[fim++] = i;
            }
    }
    free(fila);
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

    printf("cidades:    ");
    for (i = 0; i < n; i++)
        printf("%d ", i);
    printf("\n");
    printf("distancias: ");
    for (i = 0; i < n; i++)
        printf("%d ", dist[i]);
    printf("\n");
    // liberando A e seus vetores
    for (i = 0; i < n; i++)
        free(A[i]);
    free(A);
    free(dist);
    return 0;
}
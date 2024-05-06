#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

typedef struct celula
{
    int indice;
    struct celula *prox;
} Celula;

// A função recebe um inteiro origem, uma lista de adjacências Rede
// e o número de cidades da Rede n, com 0 <= origem < n. Ela devolve
// um vetor com a distância de origem até cada elemento entre 0 e n-1.
int *distancias(Celula **Rede, int n, int origem)
{
    int i, corr; // auxiliar que guarda a cidade corrente
    int *dist;
    Fila *fila;
    Celula *p;

    dist = malloc(n * sizeof(int));
    /* inicializa a fila */
    fila = criaFila();
    /* inicializa todos como não encontrados, exceto pela origem */
    for (i = 0; i < n; i++)
        dist[i] = -1;
    dist[origem] = 0;
    /* colocando origem na fila */
    insereFila(fila, origem);
    /* enquanto a fila dos ativos (encontrados mas não visitados) não estiver vazia */
    while (!filaVazia(fila))
    {
        /* remova o mais antigo da fila */
        corr = removeFila(fila);
        /* para cada vizinho deste que ainda não foi encontrado */
        p = Rede[corr];
        while (p != NULL)
        {
            i = p->indice;
            if (dist[i] == -1)
            {
                /* calcule a distancia do vizinho e o coloque na fila */
                dist[i] = dist[corr] + 1;
                insereFila(fila, i);
            }
            p = p->prox;
        }
    }
    fila = liberaFila(fila);
    return dist;
}

int main(int argc, char *argv[])
{
    Celula **Rede, *p;
    int i, j, aux, n, *dist;

    printf("Digite o numero de cidades.\n");
    scanf("%d", &n);
    Rede = (Celula **)malloc(n * sizeof(Celula *));
    for (i = 0; i < n; i++)
        Rede[i] = NULL;
    // lendo a matriz e convertendo para listas de adjacências
    printf("Digite a matriz da rede.\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            scanf("%d", &aux);
            if (aux != 0)
            {
                p = (Celula *)malloc(sizeof(Celula));
                p->indice = j;
                p->prox = Rede[i];
                Rede[i] = p;
            }
        }
    // imprimindo a rede como lista de adjacências
    printf("Imprimindo a rede lida como listas de adjacencias:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d: ", i);
        p = Rede[i];
        while (p != NULL)
        {
            printf("%d ", p->indice);
            p = p->prox;
        }
        printf("\n");
    }
    // dist = distancias(Rede, n, 0);
    dist = distancias(Rede, n, n / 2);
    // imprimindo distâncias calculadas
    printf("cidades:    ");
    for (i = 0; i < n; i++)
        printf("%d ", i);
    printf("\n");
    printf("distancias: ");
    for (i = 0; i < n; i++)
        printf("%d ", dist[i]);
    printf("\n");
    // liberando Rede e suas listas
    for (i = 0; i < n; i++)
    {
        while (Rede[i] != NULL)
        {
            p = Rede[i];
            Rede[i] = Rede[i]->prox;
            free(p);
        }
    }
    free(Rede);
    free(dist);
    return 0;
}
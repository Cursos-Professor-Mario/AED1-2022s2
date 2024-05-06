#include <stdio.h>
#include <stdlib.h>

#define NUM_MOV 4

int desLin[NUM_MOV] = {0, 1, 0, -1};
int desCol[NUM_MOV] = {1, 0, -1, 0};

typedef struct labirinto
{
    int numLins;
    int numCols;
    int **pos;
} * Labirinto;

Labirinto geraLabirinto(int numLins, int numCols, double density)
{
    int i, j;
    Labirinto lab;
    lab = malloc(sizeof(*lab));
    lab->numLins = numLins;
    lab->numCols = numCols;
    lab->pos = malloc(numLins * sizeof(int *));
    for (i = 0; i < numLins; i++)
        lab->pos[i] = malloc(numCols * sizeof(int));
    for (i = 0; i < numLins; i++)
        for (j = 0; j < numCols; j++)
            if ((double)rand() / (RAND_MAX + 1) < density)
                lab->pos[i][j] = 2;
            else
                lab->pos[i][j] = 0;
    lab->pos[0][0] = 0;
    lab->pos[numLins - 1][numCols - 1] = 0;
    return lab;
}

Labirinto liberaLabirinto(Labirinto lab)
{
    int i;
    for (i = 0; i < lab->numLins; i++)
    {
        free(lab->pos[i]);
        lab->pos[i] = NULL;
    }
    free(lab->pos);
    lab->pos = NULL;
    free(lab);
    return NULL;
}

void imprimeLabirinto(Labirinto lab)
{
    int i, j;
    for (i = 0; i < lab->numLins; i++)
    {
        printf("linha %d:", i);
        for (j = 0; j < lab->numCols; j++)
            printf(" %d", lab->pos[i][j]);
        printf("\n");
    }
}

int posValida(Labirinto lab, int lin, int col)
{
    if (lin >= 0 && lin < lab->numLins &&
        col >= 0 && col < lab->numCols)
        if (lab->pos[lin][col] == 0)
            return 1;
    return 0;
}

int resolveLabirintoR(Labirinto lab, int lin, int col,
                      int linDest, int colDest)
{
    int achou = 0, cont = 0;
    if (posValida(lab, lin, col))
    {
        lab->pos[lin][col] = 1;
        if (lin == linDest && col == colDest)
        {
            imprimeLabirinto(lab);
            achou = 1;
        }
        while (achou == 0 && cont < NUM_MOV)
        {
            achou = resolveLabirintoR(lab,
                                      lin + desLin[cont], col + desCol[cont],
                                      linDest, colDest);
            cont++;
        }
        lab->pos[lin][col] = 0;
    }
    return achou;
}

int resolveLabirinto(Labirinto lab)
{
    return resolveLabirintoR(lab, 0, 0, lab->numLins - 1, lab->numCols - 1);
}

int main(int argc, char *argv[])
{
    Labirinto lab;
    int numLins, numCols;
    double density;

    if (argc != 4)
    {
        printf("Numero incorreto de parametros! Ex.: .\\labirinto 10 15 0.03\n");
        return 0;
    }

    numLins = atoi(argv[1]);
    numCols = atoi(argv[2]);
    density = atof(argv[3]);

    lab = geraLabirinto(numLins, numCols, density);
    imprimeLabirinto(lab);
    resolveLabirinto(lab);

    lab = liberaLabirinto(lab);
    return 0;
}

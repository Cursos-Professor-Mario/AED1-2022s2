#include <stdio.h>
#include <stdlib.h>

typedef struct matriz
{
    int numLins;
    int numCols;
    int **pos;
} *Matriz;

void imprimeQLatino(Matriz m)
{
    int i, j;
    for (i = 0; i < m->numLins; i++)
    {
        printf("lin[%2d]:", i);
        for (j = 0; j < m->numCols; j++)
            printf(" %2d", m->pos[i][j]);
        printf("\n");
    }
}

int qLatinoResolvido(Matriz m)
{
    int i, j;
    for (i = 0; i < m->numLins; i++)
        for (j = 0; j < m->numCols; j++)
            if (m->pos[i][j] == 0)
                return 0;
    return 1;
}

int atribValida(Matriz m, int lin, int col, int letra)
{
    int i;
    for (i = 0; i < m->numLins; i++)
        if (m->pos[i][col] == letra ||
            m->pos[lin][i] == letra)
            return 0;
    return 1;
}

int proxPosLin(Matriz m, int lin, int col)
{
    int i, j;
    i = lin;
    j = col + 1;
    for (; i < m->numLins; i++)
    {
        for (; j < m->numCols; j++)
            if (m->pos[i][j] == 0)
                return i;
        j = 0;
    }
    return -1;
}

int proxPosCol(Matriz m, int lin, int col)
{
    int i, j;
    i = lin;
    j = col + 1;
    for (; i < m->numLins; i++)
    {
        for (; j < m->numCols; j++)
            if (m->pos[i][j] == 0)
                return j;
        j = 0;
    }
    return -1;
}

// tenta resolver colocando letra em m[lin][col]
int qLatR(Matriz m, int lin, int col, int letra)
{
    int achou = 0, cont = 1;
    if (atribValida(m, lin, col, letra))
    {
        m->pos[lin][col] = letra;
        if (qLatinoResolvido(m))
        {
            imprimeQLatino(m);
            achou = 1;
        }
        while (achou == 0 && cont <= m->numLins)
        {
            achou = qLatR(m,
                          proxPosLin(m, lin, col),
                          proxPosCol(m, lin, col), cont);
            cont++;
        }
        m->pos[lin][col] = 0;
    }
    return achou;
}

int resolveQLatino(Matriz m)
{
    int achou = 0, k = 1;
    if (qLatinoResolvido(m))
    {
        imprimeQLatino(m);
        achou = 1;
    }
    while (achou == 0 && k <= m->numLins)
    {
        achou = qLatR(m, proxPosLin(m, 0, -1),
                      proxPosCol(m, 0, -1), k);
        k++;
    }
    return achou;
}

Matriz geraQLatino(int n, double density)
{
    int i, j, l;
    Matriz m;
    m = malloc(sizeof(*m));
    m->numLins = n;
    m->numCols = n;
    m->pos = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        m->pos[i] = malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if ((double)rand() / (RAND_MAX + 1) < density)
            {
                while (1)
                {
                    l = 1 + (int)((double)rand() / (RAND_MAX + 1) * n);
                    if (atribValida(m, i, j, l))
                    {
                        m->pos[i][j] = l;
                        break;
                    }
                }
            }
            else
                m->pos[i][j] = 0;
    return m;
}

Matriz liberaQLatino(Matriz m)
{
    int i;
    for (i = 0; i < m->numLins; i++)
    {
        free(m->pos[i]);
        m->pos[i] = NULL;
    }
    free(m->pos);
    m->pos = NULL;
    free(m);
    return NULL;
}

int main(int argc, char *argv[])
{
    Matriz m;
    int n;
    double density;

    if (argc != 3)
    {
        printf("Numero incorreto de parametros! Ex.: .\\quadradoLatino 10 0.3\n");
        return 0;
    }

    n = atoi(argv[1]);
    density = atof(argv[2]);

    m = geraQLatino(n, density);
    imprimeQLatino(m);
    resolveQLatino(m);

    m = liberaQLatino(m);
    return 0;
}
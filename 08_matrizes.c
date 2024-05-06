#include <stdio.h>
#include <stdlib.h>

void *mallocSafe(unsigned nbytes)
{
    void *p;
    if (nbytes <= 0)
    {
        printf("Deu ruim! Numero de bytes nao eh positivo!\n");
        exit(EXIT_FAILURE);
    }
    p = malloc(nbytes);
    if (p == NULL)
    {
        printf("Deu ruim! malloc devolveu NULL!\n");
        exit(EXIT_FAILURE);
    }
    return p;
}

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        printf("Numero de parametros incorreto. Ex.: matrizes 5 8 10\n");
        return 0;
    }

    int *v;
    int i, j, k, n, m, l;

    n = atoi(argv[1]);
    m = atoi(argv[2]);
    l = atoi(argv[3]);

    printf("alocacao dinamica de vetor\n");

    v = mallocSafe(n * sizeof(int));

    // preenchendo o vetor em ordem crescente
    for (i = 0; i < n; i++)
    {
        // v[i] = i;
        *(v + i) = i;
    }

    for (i = 0; i < n; i++)
    {
        printf("endereco de v[%d] = %p e conteudo de v[%d] = %d\n", i, (v + i), i, v[i]);
        // printf("endereco de v[%d] = %p e conteudo de v[%d] = %d\n", i, &v[i], i, *(v + i));
    }

    free(v);
    v = NULL;

    // return 0;

    printf("alocacao dinamica de matriz\n");

    int **a;

    a = mallocSafe(m * sizeof(int *));
    for (i = 0; i < m; i++)
        a[i] = mallocSafe(n * sizeof(int));

    a[4][2] = -1;
    printf("%d\n", a[4][2]);
    printf("%d\n", *(*(a + 4) + 2));
    printf("%d\n", (*(a + 4))[2]);
    printf("%d\n", *(a[4] + 2));

    // return 0;

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            a[i][j] = 1000 * i + j;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%4d ", a[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < m; i++)
    {
        free(a[i]);
        a[i] = NULL;
    }
    free(a);
    a = NULL;

    // return 0;

    printf("alocacao estatica de matriz\n");

    int b[3][4];
    b[1][2] = 7;
    printf("%d\n", b[1][2]);
    printf("%d\n", *((int *)b + 4 * 1 + 2));
    printf("%d\n", *(int *)((void *)b + 4 * sizeof(int) * 1 + sizeof(int) * 2));

    // return 0;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 4; j++)
            b[i][j] = 1000 * i + j;

    printf("imprimindo enderecos e conteudo do modo tradicional\n");
    for (i = 0; i < 3; i++)
        for (j = 0; j < 4; j++)
            printf("v[%d][%d]: Endereco = %p e conteudo = %4d\n", i, j, &b[i][j], b[i][j]);
    printf("\n");

    printf("imprimindo enderecos e conteudo calculando endereco de inteiros explicitamente\n");
    for (i = 0; i < 3; i++)
        for (j = 0; j < 4; j++)
            printf("v[%d][%d]: Endereco = %p e conteudo = %4d\n", i, j, ((int *)b + 4 * i + j), *((int *)b + 4 * i + j));
    printf("\n");

    printf("imprimindo enderecos e conteudo calculando endereco por byte explicitamente\n");
    for (i = 0; i < 3; i++)
        for (j = 0; j < 4; j++)
            printf("v[%d][%d]: Endereco = %p e conteudo = %4d\n", i, j, ((void *)b + 4 * sizeof(int) * i + sizeof(int) * j), *(int *)((void *)b + 4 * sizeof(int) * i + sizeof(int) * j));
    printf("\n");

    return 0;

    printf("alocacao dinamica de matriz de tres dimensoes\n");

    int ***h;

    // alocação dinâmica
    h = mallocSafe(m * sizeof(int **));
    for (i = 0; i < m; i++)
    {
        h[i] = mallocSafe(n * sizeof(int *));
        for (j = 0; j < n; j++)
        {
            h[i][j] = mallocSafe(l * sizeof(int));
        }
    }

    // preenchimento
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            for (k = 0; k < l; k++)
                h[i][j][k] = 1000000 * i + 1000 * j + k;

    // impressão por camadas
    for (k = 0; k < l; k++)
    {
        printf("camada %d\n", k);
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
            {
                printf("%7d ", h[i][j][k]);
            }
            printf("\n");
        }
    }

    // liberação
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            free(h[i][j]);
            h[i][j] = NULL;
        }
        free(h[i]);
        h[i] = NULL;
    }
    free(h);
    h = NULL;

    return 0;
}

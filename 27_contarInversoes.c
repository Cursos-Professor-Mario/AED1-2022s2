#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define IMPRIME 0

void imprime(int v[], int n)
{
    if (IMPRIME)
    {
        int i;
        for (i = 0; i < n; i++)
            printf("%d ", v[i]);
        printf("\n");
    }
}

unsigned long long contarInversoes1(int v[], int n)
{
    int i, j, aux;
    unsigned long long num_inv = 0;
    for (j = 1; j < n; j++)
    {
        aux = v[j];
        for (i = j - 1; i >= 0 && aux < v[i]; i--)
        {
            v[i + 1] = v[i]; // desloca à direita os maiores
            // num_inv++;
        }
        num_inv += j - 1 - i;
        v[i + 1] = aux; /* por que i+1? */
    }
    return num_inv;
}

unsigned long long contarInversoes2(int v[], int n)
{
    int j, i, aux, pos_ult_inv, lim_dir;
    unsigned long long num_inv = 0;
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
                num_inv++;
            }
        lim_dir = pos_ult_inv;
    }
    return num_inv;
}

int main(int argc, char *argv[])
{
    int i, n;
    int stime, etime;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros. Ex: .\\contarInversoes 10\n");
        return 0;
    }

    n = atoi(argv[1]);

    int *v = (int *)malloc(n * sizeof(int));

    // ordem direta
    printf("ordem direta\n");
    for (i = 0; i < n; i++)
        v[i] = i * 10;
    imprime(v, n);

    stime = time(NULL);
    printf("numero inversoes = %llu\n", contarInversoes1(v, n));
    etime = time(NULL);
    printf("contar inversoes com n = %d leva tempo = %d\n", n, etime - stime);

    // ordem alternada
    printf("ordem alternada\n");
    for (i = 0; i < n; i += 2)
        v[i] = (i / 2) * 10;
    for (i = 1; i < n; i += 2)
        v[i] = (n - i / 2 - 1) * 10;
    imprime(v, n);

    stime = time(NULL);
    printf("numero inversoes = %llu\n", contarInversoes1(v, n));
    etime = time(NULL);
    printf("contar inversoes com n = %d leva tempo = %d\n", n, etime - stime);

    // ordem inversa
    printf("ordem inversa\n");
    for (i = 0; i < n; i++)
        v[i] = (n - i - 1) * 10;
    imprime(v, n);

    stime = time(NULL);
    printf("numero inversoes = %llu\n", contarInversoes1(v, n));
    etime = time(NULL);
    printf("contar inversoes com n = %d leva tempo = %d\n", n, etime - stime);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

void imprima(int *v, int n)
{
    int i;
    for (i = 1; i <= n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

// verifica se x está presente em v[1 .. n]
int presente(int *v, int n, int x)
{
    int i;
    for (i = 1; i <= n; i++)
        if (v[i] == x)
            return 1;
    return 0;
}

// gera todas as permutações de 1, 2, ..., n com prefixo s[1 .. k]
void permR(int *s, int k, int n)
{
    int elem;
    if (k == n)
    {
        imprima(s, n);
        return;
    }
    for (elem = 1; elem <= n; elem++)
        if (!presente(s, k, elem))
        {
            s[k + 1] = elem;
            permR(s, k + 1, n);
        }
}

void perm(int n)
{
    int *s;
    s = malloc((n + 1) * sizeof(int));
    permR(s, 0, n); // gera todas as permutações de 1, 2, ..., n
    free(s);
}

int main(int argc, char *argv[])
{
    int n;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros! Ex.: .\\enumeraPerm 10\n");
        return 0;
    }

    n = atoi(argv[1]);

    perm(n);

    return 0;
}
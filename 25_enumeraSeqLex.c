#include <stdio.h>
#include <stdlib.h>

void imprima(int *v, int n)
{
    int i;
    for (i = 1; i <= n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void subSeqLex(int n)
{
    int *s, k;
    s = malloc((n + 1) * sizeof(int));
    s[0] = 0;
    k = 0;
    while (1)
    {
        if (s[k] < n)
        { // subseq pode ser extendida
            s[k + 1] = s[k] + 1;
            k += 1;
        }
        else // s[k] == n
        {    // reduz subseq e avança valor do anterior
            s[k - 1] += 1;
            k -= 1;
        }
        if (k == 0)
            break;
        imprima(s, k);
    }
    free(s);
}

// gera toda subsequência com prefixo s[1 .. k]
// e sufixos com valores em {m, ..., n}
void subSeqLexR(int *s, int k, int m, int n)
{
    if (m <= n)
    {
        s[k + 1] = m;
        imprima(s, k + 1);
        subSeqLexR(s, k + 1, m + 1, n); // inclui m
        subSeqLexR(s, k, m + 1, n);     // não inclui m
    }
}

void subSeqLex2(int n)
{
    int *s;
    s = malloc((n + 1) * sizeof(int));
    subSeqLexR(s, 0, 1, n);
    free(s);
}

int main(int argc, char *argv[])
{
    int n;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros! Ex.: .\\enumeraSeqLex 10\n");
        return 0;
    }

    n = atoi(argv[1]);

    printf("subSeqLex:\n");
    subSeqLex(n);
    printf("\n");

    printf("subSeqLex2:\n");
    subSeqLex2(n);
    printf("\n");

    return 0;
}
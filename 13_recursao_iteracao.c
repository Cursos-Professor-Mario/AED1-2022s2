#include <stdio.h>
#include <stdlib.h>

int buscaR(int x, int *v, int n)
{
    if (n == 0)
        return -1;
    if (x == v[n - 1])
        return n - 1;
    return buscaR(x, v, n - 1);
}

int buscaI(int x, int *v, int n)
{
    while (1)
    {
        if (n == 0)
            return -1;
        if (x == v[n - 1])
            return n - 1;
        n = n - 1; /* atualiza o valor dos parâmetros que mudam na chamada recursiva */
    }
}

int somaPositivosR(int *v, int n)
{
    int res; /* variável supérflua que ajuda a entender a conversão */
    if (n == 0)
    { /* caso base */
        res = 0;
        return res;
    }
    /* 111 - marcador do inicio da função (após caso base) */
    if (v[n - 1] > 0)
    {
        res = somaPositivosR(v, n - 1); /* 222 - marcador da volta da primeira recursão */
        res += v[n - 1];
        return res;
    }
    else // v[n - 1] <= 0
    {
        res = somaPositivosR(v, n - 1); /* 333 - marcador da volta da segunda recursão */
        return res;
    }
}

int somaPositivosI(int *v, int n)
{
    int res = -1;
    int addr = 111; /* variável auxiliar para saber em que ponto voltar na função */
    int *s, t;      /* variáveis para pilha e topo */
    s = malloc((2 * n + 2) * sizeof(int));
    t = 0;
    s[t++] = 0; // inicializando endereço inicial arbitrário
    s[t++] = 0; // e valor original arbitrário pra começar a pilha
    while (t > 0)
    {
        if (n == 0)
        { /* caso base */
            res = 0;
            n = s[--t];
            addr = s[--t]; /* corresponde ao return */
        }
        else // n > 0
        {
            switch (addr)
            {
            case 111: /* inicio da função (após caso base) */
                if (v[n - 1] > 0)
                {
                    s[t++] = 222;
                    s[t++] = n; /* armazena variáveis na pilha para voltar */
                    addr = 111;
                    n = n - 1; /* atualiza variáveis para chamada recursiva */
                }
                else // v[n - 1] <= 0
                {
                    s[t++] = 333;
                    s[t++] = n; /* armazena variáveis na pilha para voltar */
                    addr = 111;
                    n = n - 1; /* atualiza variáveis para chamada recursiva */
                }
                break;
            case 222: /* volta da primeira recursão */
                res += v[n - 1];
                n = s[--t];
                addr = s[--t]; /* corresponde ao return */
                break;
            case 333:      /* volta da segunda recursão */
                res = res; /* supérfluo para manter o padrão na conversão */
                n = s[--t];
                addr = s[--t]; /* corresponde ao return */
                break;
            }
        }
    }
    free(s);
    return res;
}

int main()
{
    int v[1000];
    for (int i = 0; i < 1000; i++)
        v[i] = i;
    // for (int i = 0; i < 1000; i = i + 2)
    //     v[i] = 2 * i;
    // for (int i = 1; i < 1000; i = i + 2)
    //     v[i] = -2 * i;

    printf("%d\n", somaPositivosR(v, 1000));
    printf("%d\n", somaPositivosI(v, 1000));

    return 0;
}
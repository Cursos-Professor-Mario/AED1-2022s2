// Este programa imprime uma tabela dos valores do
// piso de log N para N = B^1, B^2, ..., B^K.
// Como de hábito, log é o logaritmo na base 2.
// Os valores de B e K são especificados na linha
// de comando: para executar o programa com B = 10
// e K = 6, por exemplo, diga
//
//     ./logaritmos 10 6
//
// Vamos supor que B e K são inteiros, com B >= 2
// e K >= 1.

#include <stdio.h>
#include <stdlib.h>

// A função lgProd recebe um inteiro N > 0
// e devolve o piso de lg N, ou seja,
// o único inteiro x tal que 2^x <= N < 2^(x+1).
int lgProd(int N)
{
    int x, acum;
    x = 0;
    acum = 1;
    while (acum <= N / 2)
    {
        acum = 2 * acum;
        x += 1;
    }
    return x;
}

// A função lgDiv recebe um inteiro N > 0
// e devolve o piso de lg N, ou seja,
// o único inteiro x tal que 2^x <= N < 2^(x+1).
int lgDiv(int N)
{
    int x = 0;
    int resid = N;
    while (resid > 1)
    {
        resid = resid / 2;
        x += 1;
    }
    return x;
}

int main(int numargs, char *args[])
{
    int B = strtol(args[1], NULL, 10);
    int K = strtol(args[2], NULL, 10);
    int N = 1;
    printf("\n          N  lg(N)\n\n");
    for (int i = 1; i <= K; ++i)
    {
        N = B * N;
        printf("%11d %5d\n", N, lgDiv(N));
    }
    return 0;
}

// Exemplo com B = 10 e K = 6:
// $ ./pisolog 10 6
//
//           N  lg(N)
//
//          10     3
//         100     6
//        1000     9
//       10000    13
//      100000    16
//     1000000    19
// $
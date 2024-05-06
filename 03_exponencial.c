#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int expI(int k, int n)
{
    int i, exp = 1;
    for (i = 0; i < n; i++)
        exp *= k; // exp = exp * k
    return exp;
}

int expR(int k, int n)
{
    if (n == 0)
        return 1;
    return k * expR(k, n - 1);
}

int expR2(int k, int n)
{
    int exp;
    if (n == 0)
        return 1;
    if (n % 2 == 0)
    {
        exp = expR2(k, n / 2);
        exp *= exp;
    }
    else // n % 2 == 1
    {
        exp = expR2(k, n / 2);
        exp *= exp;
        exp *= k;
    }
    return exp;
}

int expR3(int k, int n)
{
    int exp;
    if (n == 0)
        return 1;
    exp = expR3(k, n / 2);
    exp *= exp;
    if (n % 2 == 0)
        return exp;
    return k * exp;
}

int expI2(int k, int n)
{
    if (n == 0)
        return 1;
    // invariante: exp = k^i
    int i = 1, exp = k;
    while (i <= n / 2)
    {
        exp *= exp; // exp = exp * exp
        i = 2 * i;
    }
    if (i < n)
        exp *= expI2(k, n - i);
    return exp;
}

int expI3(int k, int n)
{
    int exp_acum = 1, n_falt = n;
    while (n_falt > 0)
    {
        // invariante: exp = k^i
        int i = 1, exp = k;
        while (i <= n_falt / 2)
        {
            exp *= exp; // exp = exp * exp
            i = 2 * i;
        }

        exp_acum *= exp; // exp_acum = exp_acum * exp;
        n_falt -= i;     // n_falt = n_falt - i;
    }
    return exp_acum;
}

int main(int argc, char **argv)
{
    int stime, etime, k, n;

    if (argc != 3)
    {
        printf("Numero incorreto de parametros. Ex: .\\exponencial 1 1000000000");
        return 0;
    }

    k = atoi(argv[1]);
    n = atoi(argv[2]);

    printf("Testando expI com k = %d e n = %d.\n", k, n);
    stime = time(NULL);
    printf("%d\n", expI(k, n));
    etime = time(NULL);
    printf("%d seconds\n", etime - stime);

    printf("Testando expR com k = %d e n = %d.\n", k, n);
    stime = time(NULL);
    printf("%d\n", expR(k, n));
    etime = time(NULL);
    printf("%d seconds\n", etime - stime);

    printf("Testando expR2 com k = %d e n = %d.\n", k, n);
    stime = time(NULL);
    printf("%d\n", expR2(k, n));
    etime = time(NULL);
    printf("%d seconds\n", etime - stime);

    printf("Testando expR3 com k = %d e n = %d.\n", k, n);
    stime = time(NULL);
    printf("%d\n", expR3(k, n));
    etime = time(NULL);
    printf("%d seconds\n", etime - stime);

    printf("Testando expI2 com k = %d e n = %d.\n", k, n);
    stime = time(NULL);
    printf("%d\n", expI2(k, n));
    etime = time(NULL);
    printf("%d seconds\n", etime - stime);

    printf("Testando expI3 com k = %d e n = %d.\n", k, n);
    stime = time(NULL);
    printf("%d\n", expI3(k, n));
    etime = time(NULL);
    printf("%d seconds\n", etime - stime);

    return 0;
}
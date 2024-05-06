#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long int binomialR0(int n, int k)
{
    if (n == 0 && k > 0)
        return 0;
    if (n >= 0 && k == 0)
        return 1;
    return binomialR0(n - 1, k) + binomialR0(n - 1, k - 1);
}

long long int binomialI(int n, int k)
{
    int i, j;
    long long int bin[100][100];
    for (j = 1; j <= k; j++)
        bin[0][j] = 0;
    for (i = 0; i <= n; i++)
        bin[i][0] = 1;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= k; j++)
            bin[i][j] = bin[i - 1][j] + bin[i - 1][j - 1];
    return bin[n][k];
}

long long int binomialR1(int n, int k)
{
    if (n < k)
        return 0;
    if (n == k || k == 0)
        return 1;
    return binomialR1(n - 1, k) + binomialR1(n - 1, k - 1);
}

long long int binomialR2(int n, int k)
{
    if (k == 1)
        return n;
    return binomialR2(n - 1, k - 1) * n / k;
}

long long int binomialI2(int n, int k)
{
    int i;
    long long int bin = 1;
    for (i = 1; i <= k; i++)
    {
        bin *= n - k + i;
        bin = bin / i;
    }
    return bin;
}

int main(int argc, char **argv)
{
    int stime, etime;
    // int n = 30, k = 20;
    int n = 40, k = 30;

    printf("Testando binomialI com n = %d e k = %d.\n", n, k);
    stime = time(NULL);
    printf("%d\n", binomialI(n, k));
    etime = time(NULL);
    printf("%d seconds\n", etime - stime);

    printf("Testando binomialR2 com n = %d e k = %d.\n", n, k);
    stime = time(NULL);
    printf("%d\n", binomialR2(n, k));
    etime = time(NULL);
    printf("%d seconds\n", etime - stime);

    printf("Testando binomialI2 com n = %d e k = %d.\n", n, k);
    stime = time(NULL);
    printf("%d\n", binomialI2(n, k));
    etime = time(NULL);
    printf("%d seconds\n", etime - stime);

    printf("Testando binomialR1 com n = %d e k = %d.\n", n, k);
    stime = time(NULL);
    printf("%d\n", binomialR1(n, k));
    etime = time(NULL);
    printf("%d seconds\n", etime - stime);

    printf("Testando binomialR0 com n = %d e k = %d.\n", n, k);
    stime = time(NULL);
    printf("%d\n", binomialR0(n, k));
    etime = time(NULL);
    printf("%d seconds\n", etime - stime);

    return 0;
}

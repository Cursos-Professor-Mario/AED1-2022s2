#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define min(m, n) (m < n ? m : n)

int mdc(int m, int n)
{
    int d = min(m, n);
    while (m % d != 0 || n % d != 0)
        d--;
    return d;
}

int euclidesR(int m, int n)
{
    if (n == 0)
        return m;
    return euclidesR(n, m % n);
}

int euclidesI1(int m, int n)
{
    int r;
    while (1)
    {
        if (n == 0)
            return m;
        r = m % n;
        m = n;
        n = r;
    }
}

int euclidesI2(int m, int n)
{
    int r;
    while (1)
    {
        if (n == 0)
            break;
        r = m % n;
        m = n;
        n = r;
    }
    return m;
}

int euclidesI3(int m, int n)
{
    int r;
    while (n != 0)
    {
        r = m % n;
        m = n;
        n = r;
    }
    return m;
}

int main(int argc, char *argv[])
{
    int stime, etime;
    int m, n;
    if (argc != 3)
    {
        printf("Numero incorreto de parametros. Ex.: mdc 2147483647 2147483646");
        return 0;
    }

    m = atoi(argv[1]);
    n = atoi(argv[2]);

    printf("Testando mdc simples:\n");
    stime = time(NULL);
    printf("%d\n", mdc(m, n));
    etime = time(NULL);
    printf("%d segundos\n", etime - stime);

    printf("Testando mdc euclidesR:\n");
    stime = time(NULL);
    printf("%d\n", euclidesR(m, n));
    etime = time(NULL);
    printf("%d segundos\n", etime - stime);

    printf("Testando mdc euclidesI1:\n");
    stime = time(NULL);
    printf("%d\n", euclidesI1(m, n));
    etime = time(NULL);
    printf("%d segundos\n", etime - stime);

    printf("Testando mdc euclidesI2:\n");
    stime = time(NULL);
    printf("%d\n", euclidesI2(m, n));
    etime = time(NULL);
    printf("%d segundos\n", etime - stime);

    printf("Testando mdc euclidesI3:\n");
    stime = time(NULL);
    printf("%d\n", euclidesI3(m, n));
    etime = time(NULL);
    printf("%d segundos\n", etime - stime);

    return 0;
}
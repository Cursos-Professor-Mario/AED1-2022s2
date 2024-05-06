#include <stdio.h>
#include <stdlib.h>

long long int fatorialR(long long int n)
{
    if (n == 0)
        return 1;
    return n * fatorialR(n - 1);
}

unsigned long long int fatorialI(unsigned long long int n)
{
    unsigned long long int i, fat = 1;
    for (i = 1; i <= n; i++)
        fat *= i; // fat = fat * i;
    return fat;
}

int main(int numargs, char *args[])
{

    printf("fatorial 0 = %lli \n", fatorialR(0));
    printf("fatorial 1 = %lli \n", fatorialR(1));
    printf("fatorial 3 = %lli \n", fatorialR(3));
    printf("fatorial 5 = %lli \n", fatorialR(5));
    printf("fatorial 10 = %lli \n", fatorialR(10));
    printf("fatorial 15 = %lli \n", fatorialR(15));
    printf("fatorial 18 = %lli \n", fatorialR(18));
    printf("fatorial 20 = %lli \n", fatorialR(20));
    printf("fatorial 22 = %lli \n", fatorialR(22)); // estourou o long long int de 64 bits

    printf("fatorial 0 = %llu \n", fatorialI(0));
    printf("fatorial 1 = %llu \n", fatorialI(1));
    printf("fatorial 3 = %llu \n", fatorialI(3));
    printf("fatorial 5 = %llu \n", fatorialI(5));
    printf("fatorial 10 = %llu \n", fatorialI(10));
    printf("fatorial 15 = %llu \n", fatorialI(15));
    printf("fatorial 18 = %llu \n", fatorialI(18));
    printf("fatorial 20 = %llu \n", fatorialI(20));
    printf("fatorial 22 = %llu \n", fatorialI(22));
    printf("fatorial 24 = %llu \n", fatorialI(24)); // estourou o unsigned long long int de 64 bits

    return 0;
}
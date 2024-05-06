#include <stdio.h>
#include <stdlib.h>

int function1(int vector[], int tam, int element)
{
    int i = 0;
    while (i < tam)
    {
        if (element == vector[i])
            return 1;
        i++;
    }
    return 0;
}

int function2(int vectorA[], int tamA, int vectorB[], int tamB, int element)
{
    int i;
    for (i = 0; i < tamA; i++)
    {
        if (element == vectorA[i])
            return 1;
    }
    for (i = 0; i < tamB; i++)
    {
        if (element == vectorB[i])
            return 1;
    }
    return 0;
}

int function3(int vectorA[], int tamA, int vectorB[], int tamB)
{
    int i, j;
    for (i = 0; i < tamA; i++)
        for (j = 0; j < tamB; j++)
            if (vectorA[i] == vectorB[j])
                return 1;
    return 0;
}

int function4(int vector[], int tam)
{
    int i, j;
    for (i = 0; i < tam; i++)
        for (j = i + 1; j < tam; j++)
            if (vector[i] == vector[j])
                return 1;
    return 0;
}

int main(int argc, char const *argv[])
{
    int i, n1 = 5, n2 = 10;
    int v1[n1], v2[n2];
    for (i = 0; i < n1; i++)
    {
        v1[i] = i;
    }
    for (i = 0; i < n2; i++)
    {
        v2[i] = i;
    }

    printf("Testando function1:\n");
    printf("%d\n", function1(v1, n1, 2));
    printf("%d\n", function1(v1, n1, 7));
    printf("%d\n", function1(v1, n1, 20));

    printf("Testando function2:\n");
    printf("%d\n", function2(v1, n1, v2, n2, 2));
    printf("%d\n", function2(v1, n1, v2, n2, 7));
    printf("%d\n", function2(v1, n1, v2, n2, 20));

    printf("Testando function3:\n");
    printf("%d\n", function3(v1, n1, v2, n2));

    printf("Testando function4:\n");
    printf("%d\n", function4(v1, n1));
    printf("%d\n", function4(v2, n2));

    return 0;
}

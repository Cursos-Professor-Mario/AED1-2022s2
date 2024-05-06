#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int dia, mes, ano;
} Data;

void *mallocSafe(unsigned nbytes)
{
    void *p;
    p = malloc(nbytes);
    printf("endereco do primeiro byte do bloco = %p\n", p);
    if (p == NULL)
    {
        printf("Deu ruim! malloc devolveu NULL!\n");
        exit(EXIT_FAILURE);
    }
    return p;
}

int main(int argc, char *argv[])
{
    // char *p;
    // p = malloc(1);
    // scanf("%c", p);
    // printf("%c\n", *p);
    // return 0;

    Data *d;
    // d = malloc(sizeof(Data));
    d = malloc(sizeof(*d));
    d->dia = 31;
    (*d).mes = 12;
    d->ano = 2019;
    printf("dia = %d, mes = %d, ano = %d\n", (*d).dia, d->mes, (*d).ano);

    // free(d);
    // d = NULL;
    // printf("dia = %d, mes = %d, ano = %d\n", (*d).dia, d->mes, (*d).ano);
    // return 0;

    unsigned long long n;
    int *v;
    printf("sizeof(unsigned long long) = %llu\n", sizeof(n));
    scanf("%llu", &n); // testar n = 1000000000
    v = mallocSafe(n * sizeof(int));

    int i;
    for (i = 0; i < n; i++)
        v[i] = i;

    printf("v[%llu] = %d\n", n - 1, v[n - 1]);
    // return 0;

    free(v);
    // v = NULL;
    printf("v[%llu] = %d\n", n - 1, v[n - 1]);

    return 0;
}
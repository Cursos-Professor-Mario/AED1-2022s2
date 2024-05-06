#include <stdio.h>
#include <stdlib.h>

typedef struct data
{
    int dia;
    int mes;
    int ano;
} Data;

// typedef struct data Data;

// struct data
// {
//     int dia;
//     int mes;
//     int ano;
// };

int main(int argc, char *argv[])
{
    // struct
    // {
    //     int dia;
    //     int mes;
    //     int ano;
    // } aniversario;

    // struct data aniversario;
    // struct data casamento;

    Data aniversario;
    Data casamento;

    aniversario.dia = 20;
    aniversario.mes = 10;
    aniversario.ano = 2010;

    printf("data de aniversario: dia = %d, mes = %d, ano = %d.\n", aniversario.dia, aniversario.mes, aniversario.ano);

    Data *p;
    p = &aniversario;
    (*p).dia = 10;
    printf("%d\n", (*p).dia);
    p->dia = 15;
    printf("%d\n", p->dia);

    return 0;
}

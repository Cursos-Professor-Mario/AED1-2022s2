#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fila.h"

int main(int argc, char *argv[])
{
    Fila *q;
    char x;

    if (argc != 1)
    {
        printf("Numero incorreto de parametros! Ex.: \".\\usaFila\".\n");
        return 0;
    }
    /* inicializa a pilha */
    q = criaFila();

    /* fila vazia? */
    printf("Fila vazia? %d\n", filaVazia(q));

    /* fila cheia? */
    printf("Fila cheia? %d\n", filaCheia(q));

    /* insere abc */
    insereFila(q, 'a');
    insereFila(q, 'b');
    insereFila(q, 'c');

    /* imprime fila */
    imprimeFila(q);

    /* fila vazia? */
    printf("Fila vazia? %d\n", filaVazia(q));

    /* fila cheia? */
    printf("Fila cheia? %d\n", filaCheia(q));

    /* remove e armazena em x */
    x = removeFila(q);
    printf("%c\n", x);

    /* imprime fila */
    imprimeFila(q);

    /* tamanho da fila */
    printf("%d\n", tamFila(q));

    for (int i = 0; i < 1000; i++)
    {
        insereFila(q, (char)(32 + (i) % (126 - 32 + 1)));
        printf("%c ", (char)removeFila(q));
    }

    /* libera a fila */
    q = liberaFila(q);

    printf("\nDeu certo!!!\n");

    return 0;
}

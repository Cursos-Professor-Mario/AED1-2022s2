#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilha.h"

// Esta função recebe uma expressão infixa inf
// e devolve a correspondente expressão posfixa.
// Esta função devolve 1 se a string ASCII s
// contém uma sequência bem-formada de
// parênteses e colchetes e devolve 0 se
// a sequência é malformada.
int bemFormada(char str[])
{
    Pilha *pilha;
    pilha = criaPilha();
    int sol;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        char c;
        switch (str[i])
        {
        case ')':
            if (pilhaVazia(pilha))
                return 0;
            c = desempilha(pilha);
            if (c != '(')
                return 0;
            break;
        case ']':
            if (pilhaVazia(pilha))
                return 0;
            c = desempilha(pilha);
            if (c != '[')
                return 0;
            break;
        default:
            empilha(pilha, str[i]);
        }
    }
    sol = pilhaVazia(pilha);
    pilha = liberaPilha(pilha);
    return sol;
}

int main(int argc, char *argv[])
{
    char *str;
    Pilha *pilha;
    char aux;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros! Ex.: .\\usaPilha \"(()[()])\"");
        return 0;
    }
    str = argv[1];

    /* inicializa a pilha */
    pilha = criaPilha();

    /* empilha abc */
    empilha(pilha, 'a');
    empilha(pilha, 'b');
    empilha(pilha, 'c');

    /* imprime pilha */
    imprimePilha(pilha);

    /* desempilha e armazena em x */
    aux = desempilha(pilha);
    printf("%c\n", aux);

    /* consulta topo da pilha */
    printf("%c\n", consultaTopo(pilha));

    /* imprime pilha */
    imprimePilha(pilha);

    /* tamanho da lista */
    printf("%d\n", tamPilha(pilha));

    /* libera a pilha */
    pilha = liberaPilha(pilha);

    printf("%s eh bem formada? %d\n", str, bemFormada(str));

    return 0;
}
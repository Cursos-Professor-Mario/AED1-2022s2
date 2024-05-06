#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Esta função recebe uma expressão infixa inf
// e devolve a correspondente expressão posfixa.
char *infix2posfix(char *inf)
{
    int n = strlen(inf);
    char *posf; // expressão pósfixa
    posf = malloc((n + 1) * sizeof(char));
    int i; // percorre infixa
    int j; // percorre posfixa
    char *pilha;
    int t; // topo da pilha

    // inicializa a pilha
    pilha = malloc(n * sizeof(char));
    t = 0;

    for (i = j = 0; inf[i] != '\0'; i++)
    {
        switch (inf[i])
        {
            char x; // auxiliar para item do topo da pilha
        case '(':
            pilha[t++] = inf[i]; // empilha
            break;
        case ')':           // move da pilha pra pósfixa até encontrar '('
            x = pilha[--t]; // desempilha
            while (x != '(')
            {
                posf[j++] = x;
                x = pilha[--t]; // desempilha
            }
            break;
        case '+':
        case '-':
            // joga na pósfixa conteúdo da pilha até esta ficar
            // vazia ou encontrar o início do bloco '('
            while (t > 0 && pilha[t - 1] != '(')
            {
                posf[j++] = pilha[--t]; // desempilha
            }
            pilha[t++] = inf[i]; // empilha
            break;
        case '*':
        case '/':
            // joga na pósfixa conteúdo da pilha até esta ficar
            // vazia, encontrar o início do bloco '(', ou
            // encontrar operador de menor precedência '+' ou '-'
            while (t > 0 && (x = pilha[t - 1]) != '(' && x != '+' && x != '-')
            {
                posf[j++] = pilha[--t]; // desempilha
            }
            pilha[t++] = inf[i]; // empilha
            break;
        default:
            if (inf[i] != ' ')      // ignora espaços
                posf[j++] = inf[i]; // copia operandos pra pósfixa
        }
    }
    // desempilha o que sobrou na pilha
    while (t > 0)
        posf[j++] = pilha[--t];
    posf[j] = '\0';
    free(pilha);
    return posf;
}

int main(int argc, char *argv[])
{
    char *inf, *posf;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros. Ex.: .\\infix2posfix '(A+B*(C-D)+E)'\n");
        return 0;
    }

    inf = argv[1];

    printf("Infixa = %s\n", inf);

    posf = infix2posfix(inf);

    printf("Posfixa = %s\n", posf);

    return 0;
}
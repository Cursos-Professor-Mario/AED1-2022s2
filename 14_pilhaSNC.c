#include <stdio.h>
#include <stdlib.h>

typedef struct celula
{
    char conteudo;
    struct celula *prox;
} Celula;

Celula *criaPilha()
{
    return NULL;
}

void empilha(Celula **ppilha, char valor)
{
    Celula *nova;
    nova = malloc(sizeof(Celula));
    nova->conteudo = valor;
    nova->prox = *ppilha;
    *ppilha = nova;
}

// supõe que a pilha não está vazia
char desempilha(Celula **ppilha)
{
    char valor;
    Celula *morta;
    morta = *ppilha;
    valor = morta->conteudo;
    *ppilha = morta->prox;
    free(morta);
    morta = NULL;
    return valor;
}

// supõe que a pilha não está vazia
char consultaTopo(Celula *pilha)
{
    return pilha->conteudo;
}

// devolve 1 se a pilha está vazia e 0 caso contrário
int pilhaVazia(Celula *pilha)
{
    return pilha == NULL;
}

void imprimePilha(Celula *pilha)
{
    Celula *p;
    p = pilha;
    while (p != NULL)
    {
        printf("%c ", p->conteudo);
        p = p->prox;
    }
    printf("\n");
}

int tamPilha(Celula *pilha)
{
    Celula *p;
    int tam = 0;
    p = pilha;
    while (p != NULL)
    {
        tam++;
        p = p->prox;
    }
    return tam;
}

Celula *liberaPilha(Celula *pilha)
{
    Celula *p, *morta;
    p = pilha;
    while (p != NULL)
    {
        morta = p;
        p = p->prox;
        free(morta);
    }
    return NULL;
}

// Esta função devolve 1 se a string ASCII s
// contém uma sequência bem-formada de
// parênteses e colchetes e devolve 0 se
// a sequência é malformada.
int bemFormada(char str[])
{
    Celula *pilha;
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
            c = desempilha(&pilha);
            if (c != '(')
                return 0;
            break;
        case ']':
            if (pilhaVazia(pilha))
                return 0;
            c = desempilha(&pilha);
            if (c != '[')
                return 0;
            break;
        default:
            empilha(&pilha, str[i]);
        }
    }
    sol = pilhaVazia(pilha);
    pilha = liberaPilha(pilha);
    return sol;
}

int main(int argc, char *argv[])
{
    char *str;
    Celula *pilha;
    char aux;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros! Ex.: .\\pilhaSNC \"(()[()])\"");
        return 0;
    }
    str = argv[1];

    /* inicializa a pilha */
    pilha = criaPilha();

    /* empilha abc */
    empilha(&pilha, 'a');
    empilha(&pilha, 'b');
    empilha(&pilha, 'c');

    /* imprime pilha */
    imprimePilha(pilha);

    /* desempilha e armazena em x */
    aux = desempilha(&pilha);
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
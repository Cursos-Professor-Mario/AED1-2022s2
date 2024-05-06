#include <stdio.h>
#include <stdlib.h>

typedef struct celula
{
    char conteudo;
    struct celula *prox;
} Celula;

Celula *criaPilhaCNC()
{
    Celula *pilha;
    pilha = (Celula *)malloc(sizeof(Celula));
    pilha->prox = NULL;
    return pilha;
}

void empilhaCNC(Celula *pilha, char valor)
{
    Celula *nova;
    nova = malloc(sizeof(Celula));
    nova->conteudo = valor;
    nova->prox = pilha->prox;
    pilha->prox = nova;
}

// supõe que a pilha não está vazia
char desempilhaCNC(Celula *pilha)
{
    char valor;
    Celula *morta;
    morta = pilha->prox;
    valor = morta->conteudo;
    pilha->prox = morta->prox;
    free(morta);
    morta = NULL;
    return valor;
}

// supõe que a pilha não está vazia
char consultaTopoCNC(Celula *pilha)
{
    return pilha->prox->conteudo;
}

// devolve 1 se a pilha está vazia e 0 caso contrário
int pilhaVaziaCNC(Celula *pilha)
{
    return pilha->prox == NULL;
}

void imprimePilhaCNC(Celula *pilha)
{
    Celula *p;
    p = pilha->prox; // pula o nó cabeça
    while (p != NULL)
    {
        printf("%c ", p->conteudo);
        p = p->prox;
    }
    printf("\n");
}

int tamPilhaCNC(Celula *pilha)
{
    Celula *p;
    int tam = 0;
    p = pilha->prox; // pula o nó cabeça
    while (p != NULL)
    {
        tam++;
        p = p->prox;
    }
    return tam;
}

Celula *liberaPilhaCNC(Celula *pilha)
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
    pilha = criaPilhaCNC();
    int sol;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        char c;
        switch (str[i])
        {
        case ')':
            if (pilhaVaziaCNC(pilha))
                return 0;
            c = desempilhaCNC(pilha);
            if (c != '(')
                return 0;
            break;
        case ']':
            if (pilhaVaziaCNC(pilha))
                return 0;
            c = desempilhaCNC(pilha);
            if (c != '[')
                return 0;
            break;
        default:
            empilhaCNC(pilha, str[i]);
        }
    }
    sol = pilhaVaziaCNC(pilha);
    pilha = liberaPilhaCNC(pilha);
    return sol;
}

int main(int argc, char *argv[])
{
    char *str;
    Celula *pilha;
    char aux;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros! Ex.: .\\pilhaCNC \"(()[()])\"");
        return 0;
    }
    str = argv[1];

    /* inicializa a pilha */
    pilha = criaPilhaCNC();

    /* empilha abc */
    empilhaCNC(pilha, 'a');
    empilhaCNC(pilha, 'b');
    empilhaCNC(pilha, 'c');

    /* imprime pilha */
    imprimePilhaCNC(pilha);

    /* desempilha e armazena em x */
    aux = desempilhaCNC(pilha);
    printf("%c\n", aux);

    /* consulta topo da pilha */
    printf("%c\n", consultaTopoCNC(pilha));

    /* imprime pilha */
    imprimePilhaCNC(pilha);

    /* tamanho da lista */
    printf("%d\n", tamPilhaCNC(pilha));

    /* libera a pilha */
    pilha = liberaPilhaCNC(pilha);

    printf("%s eh bem formada? %d\n", str, bemFormada(str));

    return 0;
}
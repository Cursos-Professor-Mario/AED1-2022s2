#include <stdio.h>
#include <stdlib.h>

typedef struct celula
{
    char conteudo;
    struct celula *prox;
} Celula;

Celula *criaPilhaSNC()
{
    return NULL;
}

void empilhaSNC(Celula **ps, char x)
{
    Celula *nova;
    nova = malloc(sizeof(Celula));
    nova->conteudo = x;
    nova->prox = *ps;
    *ps = nova;
}

char desempilhaSNC(Celula **ps)
{
    char x;
    Celula *morta;

    morta = *ps;
    x = morta->conteudo;
    *ps = morta->prox;
    free(morta);
    morta = NULL;
    return x;
}

char consultaTopoSNC(Celula *s)
{
    return s->conteudo;
}

int pilhaVaziaSNC(Celula *s)
{
    return s == NULL;
}

void imprimePilhaSNC(Celula *s)
{
    Celula *p;
    p = s;
    while (p != NULL)
    {
        printf("%c ", p->conteudo);
        p = p->prox;
    }
    printf("\n");
}

int tamPilhaSNC(Celula *s)
{
    Celula *p;
    int tam = 0;
    p = s;
    while (p != NULL)
    {
        tam++;
        p = p->prox;
    }
    return tam;
}

Celula *liberaPilhaSNC(Celula *s)
{
    Celula *p, *morta;
    p = s;
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
    Celula *s;
    s = criaPilhaSNC();
    int sol;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        char c;
        switch (str[i])
        {
        case ')':
            if (pilhaVaziaSNC(s))
                return 0;
            c = desempilhaSNC(&s);
            if (c != '(')
                return 0;
            break;
        case ']':
            if (pilhaVaziaSNC(s))
                return 0;
            c = desempilhaSNC(&s);
            if (c != '[')
                return 0;
            break;
        default:
            empilhaSNC(&s, str[i]);
        }
    }
    sol = pilhaVaziaSNC(s);
    s = liberaPilhaSNC(s);
    return sol;
}

int main(int argc, char *argv[])
{
    char *str;
    Celula *s;
    char x;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros! Ex.: .\\pilhaSNC2 \"(()[()])\"");
        return 0;
    }
    str = argv[1];

    /* inicializa a pilha */
    s = criaPilhaSNC();

    /* empilha abc */
    empilhaSNC(&s, 'a');
    empilhaSNC(&s, 'b');
    empilhaSNC(&s, 'c');

    /* imprime pilha */
    imprimePilhaSNC(s);

    /* desempilha e armazena em x */
    x = desempilhaSNC(&s);
    printf("%c\n", x);

    /* consulta topo da pilha */
    printf("%c\n", consultaTopoSNC(s));

    /* imprime pilha */
    imprimePilhaSNC(s);

    /* tamanho da lista */
    printf("%d\n", tamPilhaSNC(s));

    /* libera a pilha */
    s = liberaPilhaSNC(s);

    printf("%s eh bem formada? %d\n", str, bemFormada(str));

    return 0;
}
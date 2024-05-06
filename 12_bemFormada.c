#include <stdio.h>
#include <stdlib.h>

#define N 100
char pilha[N];
int t;

void criapilha()
{
    t = 0;
}

void empilha(char y)
{
    pilha[t++] = y;
}

char desempilha()
{
    return pilha[--t];
}

int pilhavazia(void)
{
    return t <= 0;
}

// Esta função devolve 1 se a string ASCII s
// contém uma sequência bem-formada de
// parênteses e colchetes e devolve 0 se
// a sequência é malformada.
int bemFormada(char string[])
{
    criapilha();
    for (int i = 0; string[i] != '\0'; ++i)
    {
        char c;
        switch (string[i])
        {
        case ')':             // depois de ler um )
            if (pilhavazia()) // dá erro se não tiver alguém pra pareá-lo
                return 0;
            c = desempilha(); // ou se tiver alguém diferente de (
            if (c != '(')
                return 0;
            break;
        case ']':             // depois de ler um ]
            if (pilhavazia()) // dá erro se não tiver alguém pra pareá-lo
                return 0;
            c = desempilha(); // ou se tiver alguém diferente de [
            if (c != '[')
                return 0;
            break;
        default:
            empilha(string[i]); // se leu algum abre empilha pra esperar o fecha
        }
    }
    return pilhavazia(); // verifica se sobrou alguém sem parear
}

int bemFormadaR(char string[], int *pi)
{
    int sol;
    if (string[*pi] == '(') // S = ( S ) S
    {
        *pi = *pi + 1;
        sol = bemFormadaR(string, pi) && string[*pi] == ')';
        *pi = *pi + 1;
        return sol && bemFormadaR(string, pi);
    }
    if (string[*pi] == '[') // S = [ S ] S
    {
        *pi = *pi + 1;
        sol = bemFormadaR(string, pi) && string[*pi] == ']';
        *pi = *pi + 1;
        return sol && bemFormadaR(string, pi);
    }
    return 1; // S = sequência vazia
}

int bemFormada2(char string[])
{
    int i = 0;
    return bemFormadaR(string, &i) && string[i] == '\0';
}

int main(int argc, char *argv[])
{
    char *s;
    if (argc != 2)
    {
        printf("Numero incorreto de parametros! Ex.: .\\bemFormada \"(()[()])\"");
        return 0;
    }

    s = argv[1];

    printf("%s eh bem formada? %d\n", s, bemFormada(s));
    // printf("%s eh bem formada? %d\n", s, bemFormada2(s));

    return 0;
}
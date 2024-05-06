#include <stdio.h>
#include <stdlib.h>

void imprima(int *v, int n)
{
    int i;
    printf("{");
    for (i = 1; i < n; i++)
        printf("%d, ", v[i]);
    if (n > 0)
        printf("%d", v[n]);
    printf("}\n");
}

// função que gera todos os subconjuntos de {1, ..., n}
// de tamanho tam que contém os elementos em s[1 .. k]
void subConjRordemTam(int *s, int k, int tam, int n)
{
    int i;
    if (tam == k)
    {
        imprima(s, tam); // imprime s[1 .. tam]
        return;
    }
    // laço que testa todos os elementos válidos,
    // em ordem crescente, para a posição s[k + 1]
    for (i = s[k] + 1; i <= n - (tam - (k + 1)); i++)
    { // note que (n - i) >= tam - (k + 1)
        s[k + 1] = i;
        subConjRordemTam(s, k + 1, tam, n);
    }
}

void subConjOrdemTam(int n)
{
    int *s, tam;
    s = malloc((n + 1) * sizeof(int));
    s[0] = 0;
    for (tam = 0; tam <= n; tam++)
        subConjRordemTam(s, 0, tam, n); // chamada que gera todos os subconjuntos de {1, ..., n} de tamanho tam
    free(s);
}

typedef struct noh
{
    int *v;  // armazena os elementos do subconjunto
    int tam; // numero de elementos do subconjunto
    struct noh *prox;
} Noh;

void imprimeSubConj(int *v, int n)
{
    int i;
    printf("{");
    for (i = 0; i < n - 1; i++)
        printf("%d, ", v[i]);
    if (n > 0)
        printf("%d", v[n - 1]);
    printf("}");
}

void imprimeLista(Noh *lista)
{
    while (lista != NULL)
    {
        imprimeSubConj(lista->v, lista->tam);
        if (lista->prox != NULL)
            printf(", ");
        lista = lista->prox;
    }
    printf("\n");
}

// funcao que cria um subconjunto vazio e devolve um apontador para o Noh
Noh *criaSubConjVazio()
{
    Noh *subConj = malloc(sizeof(Noh));
    subConj->v = NULL;
    subConj->tam = 0;
    subConj->prox = NULL;
    return subConj;
}

// funcao que cria um novo subconjunto com os elementos de v[0 .. tam - 1] + elem
// e devolve um apontador para o Noh
Noh *criaSubConj(int *v, int tam, int elem)
{
    Noh *subConj = malloc(sizeof(Noh));
    subConj->v = malloc((tam + 1) * sizeof(int));
    subConj->tam = tam + 1;
    subConj->prox = NULL;
    for (int i = 0; i < tam; i++)
        subConj->v[i] = v[i];
    subConj->v[tam] = elem;
    return subConj;
}

// funcao que libera um subconjunto
Noh *liberaSubConj(Noh *subConj)
{
    if (subConj->v != NULL)
        free(subConj->v);
    free(subConj);
    return NULL;
}

Noh *liberaLista(Noh *lista)
{
    Noh *aux;
    while (lista != NULL)
    {
        aux = lista;
        lista = lista->prox;
        liberaSubConj(aux);
    }
    return NULL;
}

// funcao que cria todos os subconjuntos de {1, ..., n} e devolve uma lista com estes
void subConjI(int n)
{
    Noh *lista = criaSubConjVazio();
    Noh *ultimoLista = lista;
    imprimeLista(lista);
    for (int elem = 1; elem <= n; elem++)
    {
        Noh *aux = lista;
        Noh *novaLista = NULL;
        Noh *ultimoNovaLista = NULL;
        while (aux != NULL) // criando nova lista colocando em cada subconjunto da anterior o elem
        {
            Noh *novoSubConj = criaSubConj(aux->v, aux->tam, elem);
            imprimeLista(novoSubConj);
            if (novaLista == NULL)
            {
                novaLista = novoSubConj;
                ultimoNovaLista = novaLista;
            }
            else
            {
                ultimoNovaLista->prox = novoSubConj;
                ultimoNovaLista = ultimoNovaLista->prox;
            }
            aux = aux->prox;
        }
        // conectando novaLista no final de lista
        ultimoLista->prox = novaLista;
        ultimoLista = ultimoNovaLista;
    }
    imprimeLista(lista);
    lista = liberaLista(lista);
}

// funcao que cria todos os subconjuntos de {1, ..., n} e devolve uma lista com estes
Noh *subConjR(int n, Noh **pultimoLista)
{
    if (n == 0)
    {
        Noh *lista = criaSubConjVazio();
        *pultimoLista = lista;
        return lista;
    }

    Noh *lista = subConjR(n - 1, pultimoLista);

    // criando nova lista colocando em cada subconjunto da anterior o elemento n
    Noh *aux = lista;
    Noh *novaLista = NULL;
    Noh *ultimoNovaLista = NULL;
    while (aux != NULL)
    {
        Noh *novoSubConj = criaSubConj(aux->v, aux->tam, n);
        imprimeLista(novoSubConj);
        if (novaLista == NULL)
        {
            novaLista = novoSubConj;
            ultimoNovaLista = novaLista;
        }
        else
        {
            ultimoNovaLista->prox = novoSubConj;
            ultimoNovaLista = ultimoNovaLista->prox;
        }
        aux = aux->prox;
    }
    // conectando novaLista no final de lista
    (*pultimoLista)->prox = novaLista;
    *pultimoLista = ultimoNovaLista;
    return lista;
}

void subConj(int n)
{
    Noh *lista, *ultimoLista;
    lista = subConjR(n, &ultimoLista);
    imprimeLista(lista);
    lista = liberaLista(lista);
}

int main(int argc, char *argv[])
{
    int n;

    if (argc != 2)
    {
        printf("Numero incorreto de parametros! Ex.: .\\enumeraConj 4\n");
        return 0;
    }

    n = atoi(argv[1]);

    subConjI(n);

    // subConj(n);

    return 0;
}
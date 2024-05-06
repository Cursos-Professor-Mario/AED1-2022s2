#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int contaSubconjDivisiveis(int N, int D)
{
    int cont = 0;
    int subConjBin, elem;
    for (subConjBin = 0; subConjBin < (1 << N); subConjBin++) // (1 << N) == 2^N
    {                                                         // subConjBin = 7 --> 00000111 --> {1, 2, 3}
        int soma = 0;
        for (elem = 0; elem < N; elem++)
        {                                 // elem = 2 --> (1 << elem) == 00000010
            if (subConjBin & (1 << elem)) // 00000010 & 00000111 == 00000010
            {                             // {2} cap {1, 2, 3} == {2}
                soma += elem + 1;
            }
        }
        if (soma % D == 0)
        {
            cont++;
        }
    }
    return cont;
}

int main(int argc, char *argv[])
{
    char file_name[MAX];
    FILE *entrada;
    int n, d, num_subconj_div;

    if (argc != 1)
    {
        printf("Numero incorreto de parametros. Ex: .\\nome_arquivo_executavel\n");
        return 0;
    }
    scanf("%s", file_name);
    entrada = fopen(file_name, "r");
    if (entrada == NULL)
    {
        printf("\nNao encontrei o arquivo! Informe o nome da instancia\n");
        exit(EXIT_FAILURE);
    }
    // lendo do arquivo da inst�ncia
    fscanf(entrada, "%d", &n);

    while (n != 0)
    {
        fscanf(entrada, "%d", &d);
        // calcule quantos subconjuntos de [n] = {1, ..., n} tem sua soma divis�vel por d
        num_subconj_div = contaSubconjDivisiveis(n, d);
        printf("Numero de subconjuntos de {1, ..., %d} cuja soma eh divisivel por %d = %d\n", n, d, num_subconj_div);

        fscanf(entrada, "%d", &n);
    }

    fclose(entrada);
    return 0;
}

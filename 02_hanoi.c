#include <stdio.h>
#include <stdlib.h>

void Hanoi(int n, char origem, char auxiliar, char destino)
{
    if (n == 0)
        return;
    Hanoi(n - 1, origem, destino, auxiliar);
    printf("mova o disco %d de %c para %c.\n", n, origem, destino);
    Hanoi(n - 1, auxiliar, origem, destino);
}

int main(int numargs, char *args[])
{
    printf("Hanoi com n = 1\n");
    Hanoi(1, 'A', 'B', 'C');
    printf("\n");
    printf("Hanoi com n = 2\n");
    Hanoi(2, 'A', 'B', 'C');
    printf("\n");
    printf("Hanoi com n = 3\n");
    Hanoi(3, 'A', 'B', 'C');
    printf("\n");
    printf("Hanoi com n = 4\n");
    Hanoi(4, 'A', 'B', 'C');
    printf("\n");
    printf("Hanoi com n = 5\n");
    Hanoi(5, 'A', 'B', 'C');
    printf("\n");
}

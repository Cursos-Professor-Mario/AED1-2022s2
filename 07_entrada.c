#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int n;
    if (argc != 2)
    {
        printf("Parametros incorretos. Ex.: .\\entrada 15\n");
        return 0;
    }
    printf("%s\n", argv[0]);
    n = atoi(argv[1]);
    printf("%d\n", n);

    return 0;
}
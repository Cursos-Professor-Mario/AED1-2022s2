#include <stdio.h>
#include <stdlib.h>

int G(int a, int b)
{
    int x;
    x = a + b;
    return x;
}

int F(int i, int j, int k)
{
    int x;
    x = /*2*/ G(i, j) /*3*/;
    x = x + k;
    return x;
}

int main(void)
{
    int i, j, k, y;
    i = 111;
    j = 222;
    k = 444;
    y = /*1*/ F(i, j, k) /*4*/;
    printf("%d\n", y);
    return EXIT_SUCCESS;
}
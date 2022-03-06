#include <stdio.h>

int main()
{
    int x = 0x00400000;
    printf("%d %d\n", sizeof(float), sizeof(int));
    printf("%f", (float)x);
    return 0;
}
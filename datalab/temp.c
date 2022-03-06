#include <stdio.h>
#include <limits.h>
int isAsciiDigit(int x)
{
    int y = 0x3;
    y = !((x >> 4) ^ y);
    x = x & 0xf;
    x = ((x + (~0x9 + 1)) >> 31) & 1;
    return x & y;
}
int main()
{
    for (int i = 0; i < 0x40; i++)
    {
        int a = isAsciiDigit(i);
        printf("%d\n", a);
    }
    return 0;
}
#include <stdio.h>

// define union-type variant
union floating
{
    int intVal;
    float floatVal;
};

int main(void)
{
    int i = 0;
    // declare union-type variant
    union floating x;

    printf("Please input real value: ");
    scanf("%f", &x.floatVal);
    printf("Your input value: %f\n", x.floatVal);

    for (i = 0; i < 32; i++)
    {
        // print each bit
        if ((x.intVal & 0x80000000) == 0x80000000)
            printf("1");
        else
            printf("0");
        if (i % 8 == 0)
            printf(" ");
        // left-shift the bits
        x.intVal = x.intVal << 1;
    }

    printf("\n");
    return 0;
}

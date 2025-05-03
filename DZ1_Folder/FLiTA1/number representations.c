#include <math.h>
#include <float.h>
#define BITS_IN_BYTE 8
#define TRUE 1
#define FALSE 0

double fractional_part_getting(double dbl_number)
{
    dbl_number -= (double)(int)dbl_number;
    return dbl_number;
}

void double_to_bin_repres(double number)
{
    double integer_part;
    double fractional_part = modf(number, &integer_part);

    if (number < 0.0) { //absolute value of frac and int
        fputs("-", stdout);
        fractional_part = fractional_part * (-1);
        integer_part = abs(integer_part);
    }

    int inted_integer_part = (int)integer_part; //x.00000..... to x

    char* int_part_byte = (char*)(&inted_integer_part);
    char if_once_unit_faced = FALSE;
    for (int i = sizeof(int) - 1; i >= 0; i--) //integer part to binary representation
    {
        int current_bit;

        for (int k = BITS_IN_BYTE - 1; k >= 0; k--)
        {
            current_bit = (*(int_part_byte + i) >> k) & 1;
            if (current_bit == 1)
                if_once_unit_faced = TRUE;
            if (if_once_unit_faced == TRUE)
                printf("%d", current_bit);
        }
    }
    if (if_once_unit_faced == FALSE)
        puts("0");

    fputs(".", stdout); //point between int and frac

    double var1 = fractional_part; //
    int var2;
    for (int i = 1; i <= DBL_DIG; i++) { //fractional part to binary representation
        var1 = (var1 - ((double)(int)var1))*2;
        var2 = (int)var1;
        printf("%d", var2);
    }
    puts("\n");
}

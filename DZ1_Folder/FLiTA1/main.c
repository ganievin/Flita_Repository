#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#include "number representations.c"
#include "input checkers.c"

#define YES 1
#define NO 0

int main(void) {
    setlocale(LC_ALL, "Russian");
    puts("1) Чтобы задавать множество, вводите числа:\n"
         "      a) с плавающей запятой\n"
         "      б) целые\n"
         "2) Введите show для показа элементов\n"
         "3) Введите swap для замены элемента\n"
         "4) Введите exit для выхода\n");

    double input;
    unsigned int successful_inputs = 0;

    double* decimal_set = malloc(sizeof(double));
    if(decimal_set == NULL)
            return 0;

    char end_of_input = NO;
    do {
        if (scanf("%lf", &input)) {
            if (Forbidden_Symbols_Check() == FORBIDDEN_SYMBOL_EXISTS) {
                puts("\n***Forbidden symbol***\n");
                continue;
            }
            if (Duplicate_Check(successful_inputs, input, decimal_set) == DUPLICATE_EXISTS) {
                puts("\n***Duplicate***\n");
                continue;
            }

            double* temporary_set = malloc( sizeof(double) * (successful_inputs + 1) );
            if(temporary_set == NULL)
                return 0;

            for (unsigned int k = 0; k < successful_inputs; k++)
                temporary_set[k] = decimal_set[k];

            temporary_set[successful_inputs] = input;
            free(decimal_set);
            decimal_set = temporary_set;
            printf("%d-й элемент множества записан\n\n", successful_inputs + 1);
            successful_inputs++;

        } else
        {

            char string[4];
            fgets(string, 5, stdin);
            if (strcmp(string, "exit") == 0) {
                if (Forbidden_Symbols_Check() == FORBIDDEN_SYMBOL_DOESNT_EXISTS) {
                    puts("\n----------------------------------DONE----------------------------------\n");
                    end_of_input = YES;
                }
            }else if (strcmp(string, "show") == 0){
                    printf("---------------------------------------------------------------------"
                            "\n размер вашего множества: %d\n", decimal_set[0] != 0 ? successful_inputs : 0);
                    for (int k = 0; k < successful_inputs; k++) {
                        double var = decimal_set[k];
                        printf("\n Элемент %d в десятичном представлении: %f", k+1, decimal_set[k]);
                        printf("\n Элемент %d в двоичном представлении: ", k+1);
                        double_to_bin_repres(var);
                    }

                     puts("---------------------------------------------------------------------");
            }else if (strcmp(string, "swap") == 0) {
                puts("Какой элемент заменить?");
                int elem_num_for_swap;
                scanf("%d", &elem_num_for_swap);

                while (Forbidden_Symbols_Check() == FORBIDDEN_SYMBOL_EXISTS
                       || elem_num_for_swap > successful_inputs || elem_num_for_swap <= 0) {
                    puts("Error! Out of range or forbidden symbol. Try again:\n");
                    scanf("%d", &elem_num_for_swap);
                }

                puts("Отлично, на что будем заменять? (вводите нецелые числа только с запятой или введите целое)\n");

                double swapping_value;
                scanf("%lf", &swapping_value);
                while (Duplicate_Check(successful_inputs, swapping_value, decimal_set) == DUPLICATE_EXISTS || Forbidden_Symbols_Check() == FORBIDDEN_SYMBOL_EXISTS)
                {
                    if (Duplicate_Check(successful_inputs, swapping_value, decimal_set) == DUPLICATE_EXISTS) {
                        puts("Error! Dublicate or forbidden symbol. Try again:\n");
                        Clear_Input_Buffer();
                    }
                    scanf("%lf", &swapping_value);
                }

                printf("%d-й элемент перезаписан с %lf на %lf\n", elem_num_for_swap,
                       decimal_set[elem_num_for_swap - 1], swapping_value);
                decimal_set[elem_num_for_swap - 1] = swapping_value;

            } else {
                Clear_Input_Buffer();
                puts("\n***ERROR: not read***\n");
                continue;
            }
        }


    } while (end_of_input == NO);

    free(decimal_set);
    return 0;
}

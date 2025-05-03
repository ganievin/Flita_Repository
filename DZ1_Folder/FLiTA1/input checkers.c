#define DUPLICATE_EXISTS 1
#define FORBIDDEN_SYMBOL_EXISTS 1

#define FORBIDDEN_SYMBOL_DOESNT_EXISTS 0
#define NO_DUPLICATE 0

void Clear_Input_Buffer(void) {    // Просто съедаем символы, которые не смогла прочитать scanf
    char cleaning_cursor;
    while ((cleaning_cursor = getchar()) != '\n' && cleaning_cursor != EOF) {
    }
}

char Forbidden_Symbols_Check(void) {
    char cleaning_cursor;
    while ((cleaning_cursor = getchar()) != '\n' && cleaning_cursor != EOF) {
        if (cleaning_cursor != '\t' & cleaning_cursor != ',') {
            Clear_Input_Buffer();
            return FORBIDDEN_SYMBOL_EXISTS;
        }
    }
    return FORBIDDEN_SYMBOL_DOESNT_EXISTS;
}

char Duplicate_Check (unsigned int successful_inputs_in_d_set, double inputed_value, double *decimal_set_pointer)
            {
                for (unsigned int k = 0; k < successful_inputs_in_d_set; k++) {
                    if (inputed_value == decimal_set_pointer[k]) {
                        return DUPLICATE_EXISTS;
                    }
                }
                return NO_DUPLICATE;
            }

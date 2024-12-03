#include "functions1.h"

int main(){
    char *str = NULL;
    int sum = 0;

    puts("Введите строку");
    input_line(&str);

    find_numbers(str, &sum);

    printf("Сумма всех чисел в строке: %d\n", sum);

    free(str);
    return 0;
}

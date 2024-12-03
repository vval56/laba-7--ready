#include "functions2.h"

int main(){
    char *str = NULL, *str0 = NULL, *new_str = NULL;
    int k = 0, m = 0;

    input_all(&str, &str0, &k, &m);

    my_task(&new_str, str, str0, k, m);

    print_str(new_str);
}

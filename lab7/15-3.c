#include "functions3.h"

int main(){
    char ** str = NULL;
    int len = 0;

    input_text(&str, &len);

    merge_sort(str, 0, len - 1);

    print_text(str, len);
}

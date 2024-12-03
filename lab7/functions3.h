#include <stdio.h>
#include <stdlib.h>

void input_text(char *** text, int * a) {
    int rows = 0;
    *text = NULL;
    char *line = NULL;

    puts("Введите текст:");
    while (1) {
        size_t length = 0;
        ssize_t read = getline(&line, &length, stdin);

        if (read == -1) {
            puts("Ошибка ввода");
            free(line);
            exit(0);
        }

        if (read == 1 && line[0] == '\n') {
            break;
        }

        char **temp = (char **)realloc(*text, sizeof(char *) * (rows + 1));
        if (temp == NULL) {
            puts("Ошибка перераспределения памяти");
            free(line);
            free(*text);
            exit(0);
        }
        *text = temp;

        (*text)[rows] = (char *)malloc((read + 1) * sizeof(char));
        if ((*text)[rows] == NULL) {
            puts("Ошибка выделения памяти для строки");
            free(line);
            for (int i = 0; i < rows; i++) {
                free((*text)[i]);
            }
            free(*text);
            exit(0);
        }

        for (int i = 0; i < read; i++) {
            (*text)[rows][i] = line[i];
        }
        (*text)[rows][read] = '\0';

        rows++;
    }

    free(line);
    *a = rows;
}

int string_length(char * str){
    int i = 0;
    while(str[i] != '\0')
        i++;

    return i;
}

void swap_line(char * a, char * b){
    char * temp = a;
    a = b;
    b = temp;
}

// Функция для слияния двух подмассивов (сортировка строк по длине в порядке убывания)
void merge(char **array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Временные массивы для слияния
    char **leftArray = (char **)malloc(n1 * sizeof(char *));
    char **rightArray = (char **)malloc(n2 * sizeof(char *));

    if (!leftArray || !rightArray) {
        perror("Ошибка выделения памяти");
        exit(EXIT_FAILURE);
    }

    // Копируем данные во временные массивы
    for (int i = 0; i < n1; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = array[mid + 1 + j];

    // Индексы для итерации
    int i = 0, j = 0, k = left;

    // Слияние временных массивов обратно в оригинальный массив
    while (i < n1 && j < n2) {
        if (string_length(leftArray[i]) >= string_length(rightArray[j])) {
            array[k] = leftArray[i];
            i++;
        } else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы, если есть
    while (i < n1) {
        array[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < n2) {
        array[k] = rightArray[j];
        j++;
        k++;
    }

    // Освобождаем временные массивы
    free(leftArray);
    free(rightArray);
}

// Функция сортировки слиянием (сортировка строк по длине в порядке убывания)
void merge_sort(char **array, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Рекурсивно сортируем обе половины
        merge_sort(array, left, mid);
        merge_sort(array, mid + 1, right);

        // Сливаем отсортированные половины
        merge(array, left, mid, right);
    }
}

void print_text(char ** str, int len){
    puts("\nОтсортированный текст:");

    for(int i = 0; i < len; i++){
        for(int j = 0; j < string_length(str[i]); j++)
            printf("%c", str[i][j]);
    }

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* file = fopen("i", "r");
    char* line = NULL;
    size_t line_len = 0;
    char* number_str;

    int with, height, lenght;
    while(getline(&line, &line_len, file)) {
        number_str = strtok(line, "x");
        lenght = atoi(number_str);
        number_str = strtok(NULL, "x");
        with = atoi(number_str);
        number_str = strtok(NULL, "x");
        height = atoi(number_str);
        printf("l:%d, w:%d, h:%d\n", lenght, with, height);
    }
}

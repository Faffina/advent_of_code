#include <stdio.h>
#include <stdlib.h>

int parse_int(char* line, int* offset);
void sort(int* array, int size);

int main() {
    int left_list[2000], right_list[2000];
    int size = 0;
    size_t line_size = 0;
    char* line = NULL;
    FILE* file = fopen("i1", "r");
    while(getline(&line, &line_size, file) != -1) {
        char* start = line;
        int offset = 0, left, right;
        left = parse_int(line, &offset);
        right = parse_int(line + offset + 3, &offset);
        if(left != 0) {
            left_list[size] = left;
            right_list[size] = right;
            size++;
        }
        printf("*%d-%d*\n", left, right);
    }
    free(line);
    fclose(file);

    int delta = 0;
    
    for(int l = 0; l < size; l++){
        int number = left_list[l];
        int occurence = 0;
        for(int r = 0; r < size; r++)
            if(right_list[r] == number)
                occurence++;
        delta += number * occurence;
    }

    printf("%d\n", delta);
}

void sort(int* array, int size){
    if(size < 2) return;
    int swapped = 0;
    do {
        swapped = 0;
        for(int i = 1; i < size; i++)
            if(array[i-1] > array[i]){
                int temp = array[i-1];
                array[i-1] = array[i];
                array[i] = temp;
                swapped = 1;
            }
        size--;
    } while(swapped); 
}

int parse_int(char* line, int* offset) {
    int number = 0;
    //printf("-o:%d l:%s-",*offset, line);
    while(*line != ' ' && *line != '\n' && *line != EOF && *line != '\0') {
        number *= 10;
        number += *line - '0';
        line++;
        (*offset)++;
    }
    return number;
}

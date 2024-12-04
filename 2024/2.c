#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_int(char* line, int* offset) {
    int number = 0;
    //printf("-o:%d l:%s-",*offset, line);
    while(*line != ' ' && *line != '\n' && *line != EOF && *line != '\0') {
        number *= 10;
        number += *line - '0';
        line++;
        (*offset)++;
    }
    (*offset)++;
    return number;
}

int is_safe(int* report, int size) {
    if (size < 2) 
        return 0; 
    int is_safe = 0;
    int is_decrising = report[0] > report[1];
    for(int i = 0; i < size - 1; i++) {
        if(abs(report[i] - report[i+1]) > 3)
            return 0;
        if(report[i] > report[i+1] && !is_decrising)
            return 0;
        if(report[i] < report[i+1] && is_decrising)
            return 0;
        if(report[i] == report[i+1])
            return 0;
    }
    return 1;
}

int vaildate_report(int* report, int size){
    if(is_safe(report, size)) 
        return 1;

    for(int i = 0; i < size - 1; i++) {
        report[size] = report[i];
        for(int j = i; j < size - 1; j++)
            report[j] = report[j+1];

        if(is_safe(report, size - 1))
            return 1;

        for(int j = size-1; j >= i; j--)
            report[j] = report[j-1];
        report[i] = report[size];
    }
    return is_safe(report, size - 1);
}

int main() {
    FILE* file = fopen("i2", "r");
    char* line = NULL;
    size_t line_size = 0;
    int n_safe_reports = 0;
    int report[100];
    int report_size = 0;
    memset(report, 0, sizeof(report));

    while(getline(&line, &line_size, file) != -1){
        report_size = 0;
        int level = 0;
        int offset = 0;
        for(;level = parse_int(line + offset, &offset); report_size++)
            report[report_size] = level;

        if(vaildate_report(report, report_size)){
            n_safe_reports++;
            printf("safe:%s", line);
        } else {
            printf("not safe:%s", line);
        }

    }
    printf("n: %d\n", n_safe_reports);
    free(line);
    fclose(file);
}

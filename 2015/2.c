#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* file = fopen("i", "r");
    char* line = NULL;
    size_t line_len = 0;
    char* number_str;

    int with, height, lenght;
    int total_need = 0;
    while(getline(&line, &line_len, file) != -1) {
        number_str = strtok(line, "x");
        if(number_str == NULL) break;
        lenght = atoi(number_str);
        number_str = strtok(NULL, "x");
        if(number_str == NULL) break;
        with = atoi(number_str);
        number_str = strtok(NULL, "x");
        if(number_str == NULL) break;
        height = atoi(number_str);
//        printf("l:%d, w:%d, h:%d\n", lenght, with, height);
//        int area_1 = lenght*with;
//        int area_2 = with*height;
//        int area_3 = height*lenght;
//        int smalest_area = area_1 < area_2 ? (area_1 < area_3 ? area_1 : area_3) : (area_2 < area_3 ? area_2 : area_3);
//        total_need += 2*area_1 + 2*area_2 + 2*area_3 + smalest_area;
        int perimeter1 = lenght*2 + with*2;
        int perimeter2 = with*2 + height*2;
        int perimeter3 = height*2 + lenght*2;
        int smalest_perimeter =perimeter1 < perimeter2 ? (perimeter1 < perimeter3 ? perimeter1 : perimeter3) : (perimeter2 < perimeter3 ? perimeter2 : perimeter3); 
        total_need += smalest_perimeter + lenght*with*height;       
    }
    printf("%d", total_need);
}

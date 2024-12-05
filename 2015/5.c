#include <stdio.h>
#include <stdlib.h>

int is_nice(char* str){
    int is_nice = 1;
    char prev_c = 0;
    int number_of_voule = 0;
    int contain_duble = 0;

    while(*str){
        if(*str == prev_c)
            contain_duble = 1;
        switch(*str){
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                number_of_voule++;
                break;
            case 'b': if(prev_c == 'a') {is_nice = 0; goto ret;}
            case 'd': if(prev_c == 'c') {is_nice = 0; goto ret;}
            case 'q': if(prev_c == 'p') {is_nice = 0; goto ret;}
            case 'y': if(prev_c == 'x') {is_nice = 0; goto ret;}
        }
        prev_c = *str;
        str++;
    }

    if(number_of_voule < 3) is_nice = 0;
    if(!contain_duble) is_nice = 0;
ret:
    return is_nice; 
}

int main(){
    char line[128];
    FILE* file = fopen("i", "r");
    int sum = 0;
    while(fgets(line, 128, file) != NULL){
        sum += is_nice(line);
    }
    printf("%d\n", sum);
}

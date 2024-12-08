#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            case 'b': if(prev_c == 'a') {is_nice = 0; goto ret;}; break;
            case 'd': if(prev_c == 'c') {is_nice = 0; goto ret;}; break;
            case 'q': if(prev_c == 'p') {is_nice = 0; goto ret;}; break;
            case 'y': if(prev_c == 'x') {is_nice = 0; goto ret;}; break;
        }
        prev_c = *str;
        str++;
    }

    if(number_of_voule <= 2) is_nice = 0;
    if(!contain_duble) is_nice = 0;
ret:
    return is_nice; 
}

int is_nice2(char* str){
    int size = strlen(str);
    int found = 0;

    for(int i = 0; i < size - 1; i++)
        for(int j = i+2; j < size - 1; j++)
            if(str[i] == str[j] && str[i+1] == str[j+1]) {
                found = 1;
                goto end_stack_for;
            }
end_stack_for:
    if(!found) return 0;

    found = 0;
    for(int i = 2; i < size; i++)
        if(str[i] == str[i-2]){
            found = 1;
            break;
        }
    return found;
}

int main(){
    char line[128];
    FILE* file = fopen("i", "r");
    int sum = 0;
    while(fgets(line, 128, file) != NULL){
        printf("%d-%s", is_nice2(line), line);
        sum += is_nice2(line);
    }
    printf("%d\n", sum);
}

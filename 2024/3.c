#include<stdio.h>
#include<stdlib.h>

int main(){
    size_t buffer_size;
    char* buffer;
    FILE* file_ptr = fopen("i3", "r");
    fseek(file_ptr, 0, SEEK_END);
    buffer_size = ftell(file_ptr);
    fseek(file_ptr, 0, SEEK_SET);
    buffer = malloc(buffer_size);
    if(buffer)
        fread(buffer, 1, buffer_size, file_ptr);
    char* str = buffer;
    int sum = 0;
    int enable = 1;
    printf("%s\n", buffer);
    for(;*str;str++){
        if(*str == 'd' && *(++str) == 'o'){
            if(*(++str) == 'n' && *(++str) == '\'' && *(++str) == 't' && *(++str) == '(' && *(++str) == ')') 
                enable = 0;
            if(*(str) == '(' && *(++str) == ')') 
                enable = 1; 
        }

        if(enable && *str == 'm' && *(++str) == 'u' && *(++str) == 'l' && *(++str) == '('){
            int first_number = 0;
            int is_valid = 1;
            str++;
            for(int i = 0; i < 3; i++){
                if(*str >= '0' && *str <= '9'){
                    first_number *= 10;
                    first_number += *str - '0';
                } else if (*str == ','){
                    break;
                } else {
                    is_valid = 0;
                    break;
                }
                str++;
            }
            if(!is_valid) continue;
            if(*(str) != ',' ) continue;
            str++;
            is_valid = 1;
            int second_number = 0; 
            for(int i = 0; i < 3; i++){
                if(*str >= '0' && *str <= '9'){
                    second_number *= 10;
                    second_number += *str - '0';
                } else if (*str == ')'){
                    break;
                } else {
                    is_valid = 0;
                    break;
                }
                str++;
            }
            if(!is_valid) continue;
            if(*(str) != ')' ) continue;
            printf("%d-%d\n", first_number, second_number);
            sum += first_number * second_number;
        } 
    }
    free(buffer);
    printf("%d\n", sum);
}

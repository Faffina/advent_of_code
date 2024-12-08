#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

enum instuction { and, or, not, lshift, rshift};

struct wire {
    int64_t name;
    int64_t value;
    int64_t source_a;
    int64_t source_a_value;
    int64_t source_b;
    int64_t source_b_value;
    enum instuction instuction;
};

int is_number(char* str){
    int is_number  = 1;
    for(;*str;str++){
        if(*str == '\n') continue;
        if(*str > '9' || *str < '0') {
            is_number = 0;
            break;
        } 
    } 
    return is_number;
}

int main() {
    struct wire wire_list[500];
    size_t wire_size = 0;

    FILE* file = fopen("i", "r"); 
    char line[128];
    while(fgets(line, 128, file)){
        struct wire new_wire;
        char* token = strtok(line, " ");
        if(token == NULL;)  
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isd(char* c){
    return *c >= '0' && *c <= '9';
}

int isa(char* c){
    return *c >= 'a' && *c <= 'f' || *c >= 'A' && *c <= 'F';
}

void count(char* line, int* cs, int * ss){
    char* str = line;
    for(;*str != '\n'; str++);
    *str = '\0';
    *cs += strlen(line);


    for(;*line;line++){
        if(*line == '\\') {
            if(*(line+1) == '\\' || *(line+1) == '"') {
                line += 1;
            } else if(*(line+1) == 'x' && (isd(line+2) || isa(line+2)) && (isd(line+3) || isa(line+3))){
                line += 3; 
            }
            (*ss)++;
        } else if(*line != '"') (*ss)++;
    }
}


int main(){
    FILE* file = fopen("i", "r");
    char line[1000];
    int code_size = 0;
    int storage_size = 0;
    while(fgets(line, sizeof(line), file)){
        count(line, &code_size, &storage_size);
    }

    printf("%d %d\n", code_size, storage_size);
}






#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* file = fopen("i", "r");
    char* buffer = NULL; 
    size_t size = 0;
    
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = malloc(size);
    if(buffer == NULL) exit(EXIT_FAILURE);
    fread(buffer, 1, size, file);

    int floor = 0;
    for(int i = 0; i < size; i++) {
        if(floor == -1) printf("b at: %d\n", i);
        if(buffer[i] == '(') floor++;
        if(buffer[i] == ')') floor--;
    }
    printf("f:%d\n", floor);
}

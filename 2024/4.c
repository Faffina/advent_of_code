#include <stdio.h>
#include <stdlib.h>

int whit = 0, height = 0;
char* buffer = NULL;
size_t buffer_size = 0;
char xmas[5] = "XMAS"; 

char get(int x,int y){
    if(x >= 0 && x < whit && y >= 0 && y < height)
        return buffer[whit*y + x];
    return '0';
}

int find_xmas(int xmas_index, int possition_x, int possition_y, int delta_x, int delta_y){
    if(xmas_index == 4) return 1;
    if(get(possition_x, possition_y) != xmas[xmas_index]) return 0;
    return find_xmas(xmas_index+1, possition_x+delta_x, possition_y+delta_y, delta_x, delta_y); 
}

int is_oppose(char a, char b){
    if(a == 'M' && b == 'S') return 1;
    if(a == 'S' && b == 'M') return 1;
    return 0;   
}

int find_x_mas(int x, int y){
    char upper_left  = get(x-1, y-1);
    char upper_right = get(x+1, y-1);
    char lower_left  = get(x-1, y+1);
    char lower_right = get(x+1, y+1);
    return is_oppose(upper_left, lower_right) && is_oppose(upper_right, lower_left); 
}

int main(){
    FILE* file = fopen("i4", "r");
    fseek(file, 0, SEEK_END);
    buffer_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = malloc(buffer_size);
    if(buffer == NULL)
        return -1;
    fread(buffer, 1, buffer_size, file);
    buffer[buffer_size - 1] = '\0';
    for(;buffer[whit] != '\n';whit++);

    for(int i = 0; i < buffer_size; i++){
        if(buffer[i] == '\n') {
            height++;
            for(int j = i+1; j < buffer_size; j++)
                buffer[j-1] = buffer[j];
        }
    }
    fclose(file);
    int sum = 0;
    for(int y = 0; y < height; y++){
        for(int x = 0; x < whit; x++){
            if(get(x, y) == 'A' && find_x_mas(x, y))
                sum++;

//            if(get(x, y) == 'X'){
//                sum += find_xmas(0, x, y, 0, -1);
//                sum += find_xmas(0, x, y, 1, -1);
//                sum += find_xmas(0, x, y, 1, 0);
//                sum += find_xmas(0, x, y, 1, 1);
//                sum += find_xmas(0, x, y, 0, 1);
//                sum += find_xmas(0, x, y, -1, 1);
//                sum += find_xmas(0, x, y, -1, 0);
//                sum += find_xmas(0, x, y, -1, -1);
//            }
        }
    }
    printf("sum:%d w:%d h:%d\n",sum ,whit, height);
}

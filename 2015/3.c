#include <stdio.h>
#include <stdlib.h>

struct house{
    int x, y, n_presnts;
};

int main() {
    FILE* file = fopen("i", "r");
    char* buffer = NULL;
    struct house* house_list = NULL;
    size_t size = 0;
    fseek(file, 0, SEEK_END); size = ftell(file); fseek(file, 0, SEEK_SET);
    buffer = malloc(size);
    house_list = malloc(sizeof(struct house)*size);
    fread(buffer, 1, size, file);
    
    int number_of_houses = 0;
    house_list[number_of_houses].x = 0;
    house_list[number_of_houses].y = 0;
    house_list[number_of_houses].n_presnts = 2;
    number_of_houses++;

    int x = 0, y = 0;
    int sx = 0, sy = 0;
    int rx = 0, ry = 0;
    int is_santa_turn = 1;

    for(int i = 0; i < size; i++) {
        if(is_santa_turn) {
            x = sx; 
            y = sy;
        } else {
            x = rx;
            y = ry;
        }
        int valid = 1;
        switch(buffer[i]){
            case '^': y++; break;
            case 'v': y--; break;
            case '>': x++; break;
            case '<': x--; break;
            default: valid = 0; break;
        }
        if(valid) {
            int not_found = 1;
            for(int j = 0; j < number_of_houses; j++)
                if(house_list[j].x == x && house_list[j].y == y){
                    not_found = 0;
                    house_list[j].n_presnts++;
                    break;
                }
            if(not_found) {
                house_list[number_of_houses].x = x;
                house_list[number_of_houses].y = y;
                house_list[number_of_houses].n_presnts = 1;
                number_of_houses++;
            }
        }
        if(is_santa_turn) {
            sx = x;
            sy = y;
        } else {
            rx = x;
            ry = y;
        }
        is_santa_turn = !is_santa_turn;
    }
    printf("%d", number_of_houses);
}

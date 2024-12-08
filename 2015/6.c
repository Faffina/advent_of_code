#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum opreation {none, on, off, tolgge};
typedef struct {
    int x, y;
} positon;

int main() {
    FILE* file = fopen("i", "r");
    char line[128];
    char line_back[128];
    char* token;
    int** map;
    map = malloc(sizeof(int*)*1000);
    for(int i = 0; i < 1000; i++){
        map[i] = malloc(sizeof(int)*1000);
        for(int j = 0; j < 1000; j++)
            map[i][j] = 0;
    }    

    while(fgets(line, 128, file) != NULL){
        strncpy(line_back, line, 128);
        enum opreation oper = none;
        positon start, end;

        token = strtok(line, " ");
        if(token == NULL) continue;

        if(!strcmp(token, "turn")){
            token = strtok(NULL, " ");
            if(token == NULL) continue;

            if(!strcmp(token, "off")) oper = off;
            if(!strcmp(token, "on")) oper = on;
        }
        if(!strcmp(token, "toggle")) oper = tolgge;

        if(oper == none) continue;

        token = strtok(NULL, ",");
        if(token == NULL) continue;
        start.x = atoi(token);
        token = strtok(NULL, " ");
        if(token == NULL) continue;
        start.y = atoi(token);

        token = strtok(NULL, " ");
        if(token == NULL) continue;

        token = strtok(NULL, ",");
        if(token == NULL) continue;
        end.x = atoi(token);
        token = strtok(NULL, " ");
        if(token == NULL) continue;
        end.y = atoi(token);

        for(int x = start.x; x <= end.x; x++)
            for(int y = start.y; y <= end.y; y++)
                switch(oper) {
                    case on: map[y][x] += 1; break;
                    case off: map[y][x] -= 1; if(map[y][x] < 0) map[y][x] = 0; break;
                    case tolgge: map[y][x] += 2; break;
                    case none:
                    default:
                        break;
                }

    }

    int sum = 0;
    for(int x = 0; x < 1000; x++)
        for(int y = 0; y < 1000; y++)
            sum += map[y][x];
    printf("%d\n", sum);

    FILE* image = fopen("image.pbm", "w");
    fprintf(image, "P1\n1000 1000\n");
    for(int y = 0; y < 1000; y++){
        for(int x = 0; x < 1000; x++)
            fprintf(image, "%d ", !map[y][x]);
        fprintf(image, "\n");
    }
}

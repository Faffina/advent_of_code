#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "md5/md5.h"

const char key[] = "ckczppom";



int check_v2(int n) {
    char string [128] = "\0";
    char n_str [64];
    sprintf(n_str, "%d", n);
    strcat(string, key);
    strcat(string, n_str);
    uint8_t ris[16];
    md5String(string, ris);
    string[0] = 0;
    for(int i = 0; i < 16; i++)
        sprintf(&string[i*2], "%02x\n", ris[i]);
     
    int all_zero = 1;
    for(int i = 0; i < 6; i++)
        if(string[i] != '0'){
            all_zero = 0;
            break;
        }
    if(all_zero)
        printf("found:%d-%s", n, string);
    return all_zero;
}

int check(int n) {
    char cmd[128];
    cmd[0] = '\0';
    char pre[] = "echo -n ";
    char n_str[20];
    char post[] = " | md5sum";
    strcat(cmd, pre);
    strcat(cmd, key);
    sprintf(n_str, "%d", n);
    strcat(cmd, n_str);
    strcat(cmd, post);

    FILE* file = popen(cmd, "r");
    char ris[128];
    fgets(ris, 128, file);
    
    int all_zero = 1;
    for(int i = 0; i < 5; i++)
        if(ris[i] != '0'){
            all_zero = 0;
            break;
        }
    if(all_zero)
        printf("found: %d\n", n);
    pclose(file);
    return all_zero;
}

int main(){
    int i = 0;
    while (i < 10000000){
        if(check_v2(i)) {
            break;
        }
        if(i % 100 == 0) 
            printf("%d\n", i);
        i++;
    }
}

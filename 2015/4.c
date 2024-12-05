#include <stdio.h>
#include <openssl/md5.h>
#include <string.h>
#include <pthread.h>

const char key[] = "abcdef";

void* check(void* arg) {
    int n = *(int*)(arg);
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
    return NULL;
}

int main(){
    int i = 0;
    pthread_t therds[4];
    int arg[4];
    for(int j = 0; j < 4; j++){
        arg[j] = i++;
        pthread_create(&therds[j], NULL, check, &arg[j]);
    }
    while(1) {
        for(int j = 0; j < 4; j++) {
            if(pthread_detach(therds[j]) == 0) {
                pthread_join(therds[j], NULL);
                arg[j] = i++;   
                pthread_create(&therds[j], NULL, check, &arg[j]);
            }
        }
        int temp = i % 1000;
        if(temp >= 0 && temp <= 10) printf("%d\n", i);
    } 
}

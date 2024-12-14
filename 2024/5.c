#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_PAGES_PER_ORDER 100
#define MAX_NUMBER_OF_ORDERS 500
#define MAX_NUMBER_OF_RULES 500

typedef struct {
    int befor;
    int after;
} printing_rule;

typedef struct {
    int pages[MAX_PAGES_PER_ORDER];
    size_t number_of_pages;
    int is_vaild;
} printing_order;

int main() {
    printing_rule rules[MAX_NUMBER_OF_RULES];
    size_t rule_len = 0;
    printing_order orders[MAX_NUMBER_OF_ORDERS];
    size_t order_len = 0;

    FILE* file = fopen("i", "r");
    char line[1000];
    int i = 0;
    while(fgets(line, sizeof(line), file) != NULL){
        if(strstr(line, "|") != NULL){
            sscanf(line, "%d|%d", &rules[rule_len].befor, &rules[rule_len].after);
            rule_len++;
        } else if(strstr(line, ",") != NULL) {
            char* token = strtok(line, ",");
            printing_order* new_order = &orders[order_len++];
            new_order->number_of_pages = 0;
            new_order->pages[new_order->number_of_pages++] = atoi(token);
            while((token = strtok(NULL, ",")) != NULL)
                new_order->pages[new_order->number_of_pages++] = atoi(token);
        }
        i++;
    }
    fclose(file);

    for(int o = 0; o < order_len; o++){
        printing_order* order = &orders[o];
        order->is_vaild = 1;
        for(int p = 0; p < order->number_of_pages; p++)
            for(int r = 0; r < rule_len; r++){
                printing_rule* rule = &rules[r];
                if(order->pages[p] == rule->after)
                    for(int np = p+1; np < order->number_of_pages; np++)
                        if(order->pages[np] == rule->befor){
                            order->is_vaild = 0;
                            goto next_order;
                        }
            }
    next_order:
    }

    int sum = 0;
    for(int o = 0; o < order_len; o++){
        if(orders[o].is_vaild){
             sum += orders[o].pages[orders[o].number_of_pages/2];
        }
    }
    printf("%d\n", sum);
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

enum instuction { and, or, not, lshift, rshift, transfer, no_instrucion};
enum source_state {no_input = '.', value_present = '/'};


struct wire {
    char name[4];
    int is_done;
    uint16_t value;
    char source_a[4];
    uint16_t source_a_value;
    char source_b[4];
    uint16_t source_b_value;
    enum instuction instuction;
};

int is_number(char* str){
    int is_number  = 1;
    for(;*str;str++){
        if(*str == '\n') {*str = '\0'; return is_number;}
        if(*str > '9' || *str < '0') return 0;
    } 
    return is_number;
}

int is_lower_case(char* str) {
    int is_lower = 1;
    for(;*str;str++){
        if(*str == '\n') {*str = '\0'; return is_lower;}
        if(*str < 'a' | *str > 'z') return 0;
    }
    return is_lower;
}

int evaluate(struct wire* w) {
    if(w->is_done) return 0;
    if(w->instuction == not && w->source_a[0] != value_present) return 0;
    if(w->instuction == transfer && w->source_a[0] != value_present) return 0;
    if(w->instuction != not && w->instuction != transfer && (w->source_a[0] != value_present || w->source_b[0] != value_present)) return 0;
    switch(w->instuction){
        case and:    w->value = w->source_a_value & w->source_b_value; break;
        case or:     w->value = w->source_a_value | w->source_b_value; break;
        case not:    w->value = ~w->source_a_value; break;
        case lshift: w->value = w->source_a_value << w->source_b_value; break;
        case rshift: w->value = w->source_a_value >> w->source_b_value; break;
        case transfer: w->value = w->source_a_value; break;
        case no_instrucion: return 0;
    }
    w->is_done = 1;
    return 1;
}


int insert_name(int64_t* dest, char* sour){
    size_t size = strlen(sour);
    if(size > 2) return 0;
    *dest = sour[0];
    if(size == 2) *dest += sour[1] << 8;
    return 1;
}

#define get_token() strtok(NULL, " "); if(token == NULL) {printf("error parsing:%d\n", i); continue;}

int main() {
    struct wire wire_list[500];
    size_t wire_size = 0;

    FILE* file = fopen("i", "r"); 
    char line[128];
    for(int i = 0; fgets(line, 128, file); i++){
        struct wire new_wire;

        char* token = strtok(line, " ");
        if(token == NULL) continue;
        if(token[0] == '\n') break;

        // evaluate if first isnstuctoins is not
        if(strcmp(token, "NOT") == 0){
            new_wire.instuction = not;
            new_wire.source_b[0] = no_input;
            new_wire.source_b_value = 0;

            // if the first operand of the not instuction is numericm, the wire is evaluate and mark as done
            token = get_token();
            if(is_number(token)) {
                new_wire.source_a[0] = value_present;
                new_wire.source_a_value = atoi(token);
                new_wire.is_done = 0;
                if(!evaluate(&new_wire)) {printf("error eveal:%d\n",i); continue;}

                token = get_token();
                token = get_token();
                if(!is_lower_case(token)) {printf("error insert:%d\n", i); continue;}
                strncpy(new_wire.name, token, 3);

            // if the fist opernd of the not istructon is not numeric we just seve the id
            } else if(is_lower_case(token)){ 
                new_wire.value = 0; 
                new_wire.is_done = 0;
                new_wire.source_a_value = 0;
                strncpy(new_wire.source_a, token, 3);
                token = get_token();
                token = get_token();
                if(!is_lower_case(token) ) {printf("error insert:%d\n", i); continue;}
                strncpy(new_wire.name, token, 3);
            } else {
                printf("parsing error: %d\n", i); continue;
            }
        // the case the instuction isnt "not"
        } else {
            // ceck if the fist operand is numeric or not and dose the usual stuff
            if(is_lower_case(token)) {
                new_wire.source_a_value = 0;
                if(strcmp(token, "a") == 0) 
                    printf("test");
                strncpy(new_wire.source_a, token, 3);
            } else if(is_number(token)) {
                new_wire.source_a[0] = value_present;
                new_wire.source_a_value = atoi(token);
            } else {
                printf("parsing error: %d\n", i); continue;
            }
            
            // checks if the expresion is an assigment
            token = get_token();
            if(strcmp(token, "->") == 0) {
                token = get_token();
                if(!is_lower_case(token) ) {printf("error insert:%d\n", i); continue;}
                strncpy(new_wire.name, token, 3);
                if(new_wire.source_a[0] == value_present) {
                    new_wire.value = new_wire.source_a_value;
                    new_wire.is_done = 1;
                    new_wire.source_a_value = 0;
                    new_wire.source_a[0] = no_input;
                    new_wire.source_b_value = 0;
                    new_wire.source_b[0] = no_input;
                    new_wire.instuction = no_instrucion;
                } else {
                    new_wire.value = 0;
                    new_wire.is_done = 0;
                    new_wire.source_b_value = 0;
                    new_wire.source_b[0] = no_input;
                    new_wire.instuction = transfer;
                }

            // if the expresion is not an assigment we preced to ceck the rest
            }else {
                if(strcmp(token, "AND") == 0) new_wire.instuction = and; 
                else if(strcmp(token, "OR") == 0) new_wire.instuction = or; 
                else if(strcmp(token, "LSHIFT") == 0) new_wire.instuction = lshift; 
                else if(strcmp(token, "RSHIFT") == 0) new_wire.instuction = rshift;
                else {printf("error parsing: %d\n", i); continue;}
                
                token = get_token();
                if(is_lower_case(token)) {
                    new_wire.source_b_value = 0;
                    strncpy(new_wire.source_b, token, 3);
                } else if(is_number(token)) {
                    new_wire.source_b[0] = value_present;
                    new_wire.source_b_value = atoi(token);
                } else {
                    printf("parsing error: %d\n", i); continue;
                }

                token = get_token();
                token = get_token();
                new_wire.is_done = 0;
                new_wire.value = 0;
                if(!is_lower_case(token) ) {printf("error insert:%d\n", i); continue;}
                strncpy(new_wire.name, token, 3);
            }
        }   
        wire_list[wire_size++] = new_wire;
    }

//    printf("\n=====================\n");
//    for(int i = 0; i < wire_size; i++) {
//        struct wire w = wire_list[i];
//        printf("n:%s, d:%d, v:%d, a:%s, av:%d, b:%s, bv:%d, opr:%d\n", w.name, w.is_done, w.value, w.source_a, w.source_a_value, w.source_b, w.source_b_value, w.instuction);
//    }
    for(int i = 0; i < wire_size; i++)
        if(strcmp(wire_list[i].name, "b") == 0){
            struct wire* b = &wire_list[i];
            b->is_done = 1;
            b->value = 16076;
            b->instuction = no_instrucion;
            b->source_a[0] = no_input;
            b->source_a_value = 0;
            b->source_b[0] = no_input;
            b->source_b_value = 0;
        }
    
    int all_done = 1;
    do {
        all_done = 1;
        for(int i = 0; i < wire_size; i++)
            if(wire_list[i].is_done)
                for(int j = 0; j < wire_size; j++)
                    if(!wire_list[j].is_done){
                        struct wire *a = &wire_list[i];
                        struct wire *b = &wire_list[j];
                        if(strcmp(a->name, b->source_a) == 0) {
                            b->source_a[0] = value_present;
                            b->source_a_value = a->value;
                        } else if(strcmp(a->name, b->source_b) == 0) {
                            b->source_b[0] = value_present;
                            b->source_b_value = a->value;
                        }
                    }
        int temp;
        for(int i = 0; i < wire_size; i++)
            if(evaluate(&wire_list[i]))
                all_done = 0;
    } while(!all_done );

    for(int i = 0; i < wire_size; i++)
        if(strcmp(wire_list[i].name, "a") == 0)
            printf("%d\n", wire_list[i].value);

//    printf("\n=====================\n");
//    for(int i = 0; i < wire_size; i++){
//        printf("%s, %hu\n", wire_list[i].name, wire_list[i].value);
//    }

}

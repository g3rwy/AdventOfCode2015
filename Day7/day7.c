#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "map.h"

typedef unsigned short ushort;
typedef map_t(ushort) map_ushort_t;

struct instr_line{
    char out[3];
    char in1[7];
    char in2[7];
    char instruction[7];
};

struct instr_line nodes[400]; // oh no globals aaaagh
map_ushort_t wires;

int get_instr(const char* s){
    const char* instructions[5] = {
        "AND",
        "OR",
        "LSHIFT",
        "RSHIFT",
        "NOT"
    };
         
    for(int i=0;i<5;i++){
        if(strcmp(instructions[i],s) == 0) return i;
    }
    return 10; // won't reach it anyway lol
}

struct instr_line find_line(const char out[3]){
    for(int i=0;i<400;++i){
        if(strcmp(nodes[i].out,out) == 0) return nodes[i];
    }
    printf("something went wrong\n");
    struct instr_line t; // idk
    return t;
}

struct instr_line find_fucking(char out[3]){
    for(int i=0;i<400;++i){
        if(strcmp(nodes[i].in1,out) == 0 || strcmp(nodes[i].in2,out) == 0 ) return nodes[i];
    }
    
    struct instr_line t; // idk
    return t;
}

ushort find_wire(const char wire[3]){
    struct instr_line l = find_line(wire);
    //printf("%s %s %s -> %s\n",l.in1,l.instruction,l.in2,l.out);
    ushort res = 0;
    
    ushort n1;
    ushort n2;
    
    if(isdigit(l.in1[0])) n1 = (ushort)atoi(l.in1);
    else{
        ushort* t = map_get(&wires,l.in1);
        if(t == NULL){
            n1 = find_wire(l.in1);
            map_set(&wires,l.in1,n1);    
        }
        else n1 = *t;
        } 
    
    
    if(strlen(l.in2) > 0){
        if(isdigit(l.in2[0])) n2 = (ushort)atoi(l.in2);
        else{
        ushort* t = map_get(&wires,l.in2);
        if(t == NULL){
            n2 = find_wire(l.in2);
            map_set(&wires,l.in2,n2);    
        }
        else n2 = *t;
        } 
    }
    //NOTE put values in mapT
    
    switch(get_instr(l.instruction)){
        case 0:
                return n1 & n2;
                //map_set(&wires,token[3], values[0] & values[2]);
        case 1:
                //map_set(&wires,token[3], values[0] | values[2]);
                return n1 | n2;
        case 2:
                //map_set(&wires,token[3], values[0] << values[2]);
                return n1 << n2;
        case 3:
                //map_set(&wires,token[3], values[0] >> values[2]);
                return n1 >> n2;
        case 4:
                return ~n1;
        default:
                return n1;
    }
    
    return 42069;
}

int main() {
    map_init(&wires);
    
    FILE* f = fopen("input.in","r");
    char buff[50];
    
    int idx = 0;
    
    while(fgets(buff,sizeof(buff),f)){
        char line[50];
        strncpy(line,buff,sizeof(buff));
        line[(strchr(line,'\n')- line)] = '\0';
          
        
        if(line[0] == 'N'){
            //NOT
            char in[7],out[3];
            sscanf(line,"NOT %s -> %s",in,out);
            strcpy(nodes[idx].out,out);
            strcpy(nodes[idx].in1,in);
            strcpy(nodes[idx].instruction,"NOT");
            idx++;
        }
        else{
            if(*(strchr(line,' ')+1) == '-'){
                //ASSIGN
                char value[7];
                char key[3];
                sscanf(line,"%s -> %s",value,key);
                strcpy(nodes[idx].out,key);
                strcpy(nodes[idx].in1,value);
                strcpy(nodes[idx].instruction,"\t");
                idx++;
            }
            else{
               // BASIC INSTRUCTION
                char* p;
                p = strtok(line," ->");
                char token[4][8];
                int i = 0;
                
                while(p != NULL){
                    strncpy(token[i++],p,sizeof(token[i-1]));
                    p = strtok(NULL," ->");
                }
                
                strcpy(nodes[idx].in1,token[0]);
                strcpy(nodes[idx].instruction,token[1]);
                strcpy(nodes[idx].in2,token[2]);
                strcpy(nodes[idx].out,token[3]);
                idx++;
            }
        }
    }
    
    //struct instr_line findme = find_line("lc");
    //printf("%s %s %s -> %s\n",findme.in1,findme.instruction,findme.in2,findme.out);
    
    ushort result = find_wire("a");
    printf("%u\n",result);
    //result = find_wire("i");
    //printf("%u\n",result);
    
finish:
    fclose(f);
    map_deinit(&wires);
    
    return 0;
}


      
        //printf("%s\n",line);
        /*
        if(line[0] == 'N'){
            char in[3],out[3];
            sscanf(line,"NOT %s -> %s",in,out);
            ushort* t = map_get(&wires, in);
            if(t != NULL) map_set(&wires,out,~(*t));
            else map_set(&wires,out,0);
        }
        else{
            if(*(strchr(line,' ')+1) == '-'){
                ushort t;
                char key[3];
                sscanf(line,"%hu -> %s",&t,key);
                map_set(&wires,key,t);
            }
            else{
                char* p;
                p = strtok(line," ->");
                char token[4][9];
                int i = 0;
                ushort values[4];
                
                while(p != NULL){
                    strncpy(token[i++],p,sizeof(token[i-1]));
                    p = strtok(NULL," ->");
                }
                for(i = 0;i < 4;++i){
                    if(i == 1) continue;
                    if(isdigit(token[i][0])){
                        values[i] = (ushort)atoi(token[i]);
                    }
                    else{
                        ushort* t = map_get(&wires, token[i]);
                        if(t != NULL) values[i] = (ushort)atoi(token[i]);
                        else{
                            values[i] = 0;
                            map_set(&wires,token[i],0);
                        }
                    }
                }
                
                switch(get_instr(token[1])){
                case 0:
                        map_set(&wires,token[3], values[0] & values[2]);
                        break;
                case 1:
                        map_set(&wires,token[3], values[0] | values[2]);
                        break;
                case 2:
                        map_set(&wires,token[3], values[0] << values[2]);
                        break;
                case 3:
                        map_set(&wires,token[3], values[0] >> values[2]);
                        break;
                default:
                        printf("cringe %s\n",token[1]);
                }
            }
        }
        */

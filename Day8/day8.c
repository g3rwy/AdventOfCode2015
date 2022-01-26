#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Part 1
int get_mem_len(char t[50]){
    int res = 0;
    for(int i=0; i < strlen(t)-1;++i){
        if(t[i] == '\\'){
            ++res; 
            i += (t[i+1] == 'x' ? 3 : 1);
            continue;
        }
        else if(t[i] == '\"')
            continue;
        ++res; 
    }
    return res;
}
*/

//Part 2
int get_string_len(char t[50]){
    int res = 0;
    for(int i=0; i < strlen(t)-1;++i){
        if(i == 0 || i == strlen(t)-2)        res += 2;
        else if(t[i] == '\\' || t[i] == '\"') ++res;
        ++res; 
    }
    return res;
}

int main(){
    FILE* f = fopen("input.in","r");
    char buff[50];
    unsigned int code_ccount = 0;
    unsigned int mem_ccount = 0;
    while(fgets(buff,sizeof(buff),f)){
        code_ccount += strlen(buff)-1;
        //mem_ccount += get_mem_len(buff);
        mem_ccount += get_string_len(buff);
    }
    fclose(f);
    //printf("%u\n",code_ccount - mem_ccount);
    printf("%u\n",mem_ccount - code_ccount);
    return 0;
};

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vec.h" // why not, who cares

struct Node {
    int id;
    uint distance;
    char name[20];
    vec_int_t paths;
    bool visited;
};
typedef vec_t(struct Node) node_vec_t;

int get_name_id(node_vec_t nodes, char name[20]){ // nevermind, should take index in vector as id
    /*int i = -1;
    int last_city = -1;
    for(;i<nodes.length;++i){
        if(strcmp(t[i].name,name) == 0) return i;
    }
    return last_city;<
    */
    return 0;
}

int main(){
    FILE* f = fopen("input.in","r");
    node_vec_t nodes;
    vec_init(&nodes);
    char buff[50];
    char curr_name[20]; char prev_name[20];
    int id = 0;
    char cities[20][20];
    
    while(fgets(buff,sizeof(buff),f)){
        struct Node start_node;
        struct Node dest_node;
        char start[20]; char dest[20]; uint distance = 0;
        sscanf(buff,"%s to %s = %u\n",start,dest,&distance);
        vec_init(&start_node.paths);
        vec_init(&dest_node.paths);
        
        id = get_name_id(nodes,dest);
        dest_node.distance = distance;
        dest_node.visited = false;
        dest_node.id = id;
        strcpy(dest_node.name,dest);
        
        id = get_name_id(nodes,start);
        start_node.distance = distance;
        start_node.visited = false;
        start_node.id = id;
        strcpy(start_node.name,start);
        
        vec_push(&nodes,dest_node);
    }
    int i; struct Node n;
    vec_foreach(&nodes,n,i){ // free vectors in all nodes
        printf("%d %s\n",n.id,n.name);
    }
    
    fclose(f);
    vec_foreach(&nodes,n,i){ // free vectors in all nodes
        vec_deinit(&n.paths);
    }
    vec_deinit(&nodes);
}
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "../common/heap.h"
#include "../common/inputHandler.h"



void relax(int u, int v, int weight, qList *q){
    int position = q->elementPosition[v];
    if(weight < q->heap[position]->key){
        decreaseKey(position, weight, u, q);
    }
}



int *dijkstra(int vertices, int root, adjList **adjLists){
    qList *q = initHeap(vertices, root);
    int *s = (int*) malloc((vertices+1)*sizeof(int));

    while(q->size){
        qElement * u = pop(q);
        s[u->vertex] = u->key;
        adjVertex * v = adjLists[u->vertex]->head;
        while (v){
            int vPosition = q->elementPosition[v->vertex];
            if(vPosition != -1){
                int weight = v->weight;
                if(u->vertex != root){
                    weight += u->key;
                }
                relax(u->vertex, v->vertex, weight, q);
            }
            
            v = v->next;
        }        
    }

    freeQ(q);
    return s;
}









void main(int argc, char *argv[]){

    int vertices, edges, i, root = 1;
    char *fileName = (char*)malloc(100 * sizeof(char));
    char *execCommand = (char*)malloc(100 * sizeof(char));
    
    for (i = 0; i < argc; i++){
        if(!strcmp(argv[i], "-f")) fileName = argv[++i];
        else if(!strcmp(argv[i], "-i")) root = atoi(argv[++i]);
        else if(!strcmp(argv[i], "-h")) execCommand = argv[i];
    }
    FILE *file = fopen(fileName, "r");
     if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    fscanf(file, "%d%d", &vertices, &edges);
    adjList **adjLists = createAdjLists(file, vertices, edges);
    qList *q = initHeap(vertices, root);
    int *s = dijkstra(vertices, root, adjLists);
    

    if(!strcmp(execCommand, "-h")){}
    else {
        for (i = 1; i <= vertices; i++){
            printf("%d:%d ", i, s[i] < INT_MAX ? s[i] : -1);
        }
    };

    free(s);
    freeLists(adjLists, vertices);
}







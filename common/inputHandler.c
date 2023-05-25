#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inputHandler.h"



 FILE *openFile(char *fileName, char command[]){
    FILE *f = fopen(fileName, command);
     if (f == NULL) {
        printf("Failed to open the file.\n");
        exit(-1);
    }
    return f;
}

void readCommands(int *h, int *s, int *root, char **inputFile, char **outputFile, int size, char *commandLine[]) {
    int i;
    for (i = 0; i < size; i++) {
        if (!strcmp(commandLine[i], "-f")) 
            *inputFile = commandLine[++i];       
        if (!strcmp(commandLine[i], "-o"))
            *outputFile = commandLine[++i];
        else if (!strcmp(commandLine[i], "-i")) {
            if(root == NULL) {
                printf("este programa não suporta a flag -i\n");
                exit(-1);
            }
            *root = atoi(commandLine[++i]);
            if (!(*root)) {
                printf("paramêtro inválido para o comando -i. Valor 0/não numérico não é válido para a raiz!\n");
                exit(-1);
            }
        } else if (!strcmp(commandLine[i], "-h"))
            *h = 1;
        else if (!strcmp(commandLine[i], "-s")){
            if(s)*s = 1;
        }
    }
}

void readFirstLine(int *vertices, int *edges, FILE *f){
    fscanf(f, "%d%d", vertices, edges);
}



void addVertex(adjList *list, int v, int weight){
    adjVertex *vertex = (adjVertex*) malloc(sizeof(addVertex));
    vertex->next = list->head;
    vertex->vertex = v;
    vertex->weight = weight;

    list->size++;
    list->head = vertex;
}

adjList **createAdjLists(FILE *file, int vertices, int edges){
    adjList **lists = (adjList**) malloc((vertices+1) * sizeof(adjList));
    int i, u, v, weight;
    for(i = 1; i <= vertices; i++){
        lists[i] = (adjList*) malloc(sizeof(adjList));
        lists[i]->head = NULL;
        lists[i]->size = 0;
    }
    

    for (i = 0; i < edges; i++){
        fscanf(file, "%d%d%d", &u, &v, &weight);
        addVertex(lists[u], v, weight);
        addVertex(lists[v], u, weight);
    }
    return lists;
}


void freeLists(adjList **adjLists, int vertices){
    int i, j;
    for (i = 1; i <= vertices; i++){
        adjVertex * aux = adjLists[i]->head;
        while(adjLists[i]->head){
            adjLists[i]->head = adjLists[i]->head->next;
            free(aux);
            aux = adjLists[i]->head;
        }
        free(adjLists[i]);
    }
    free(adjLists);
}















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



char printHelp(){
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        printf("menu de ajuda do algoritmo Dijkstra:\n");
        printf("- ao adiciona a flag '-f' seguido de uma string, define-se o nome do arquivo o qual será utilizado para retirar os dados de entrada.\n");
        printf("Caso o nome do arquivo esteja errado ou não exista, o programa irá ser encerrado com erro -1.\n");
        printf("- caso haja uma flag -s, o programa ignorará a mesma.\n");
        printf("- ao adiciona a flag '-o' seguido de uma string, a saída será escrita em um arquivo com o nome da string. Caso não, será printado no console\n");
        printf("- ao adiciona a flag '-i' seguido de um número, define-se o vértice raiz da árvore. Caso não, o vertice padrão definido é o v = 1.\n");
        printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}



char *getCosts(int *s, int vertices){
    char *output = (char*) calloc((vertices + 1) * 10, sizeof(char));
    char aux[10];
    int i;
    for (i = 1; i <= vertices; i++){
    sprintf(aux, "%d:%d ", i, s[i] != INT_MAX ? s[i] : -1);
    strcat(output, aux);    
    }
    return output;
}






void main(int argc, char *argv[]){

    int vertices, edges, i, root = 1, hFlag = 0;
    char *inputFileName;
    char *outputFileName = "";

    readCommands(&hFlag, NULL, &root, &inputFileName, &outputFileName, argc, argv);
    FILE *inputFile = openFile(inputFileName, "r");
    readFirstLine(&vertices, &edges, inputFile);

    adjList **adjLists = createAdjLists(inputFile, vertices, edges);
    qList *q = initHeap(vertices, root);
    int *s = dijkstra(vertices, root, adjLists);
    char *output = getCosts(s, vertices);
    if(hFlag){
        printHelp();
    } 
    if(strcmp(outputFileName, "")){
        FILE *outputFile = openFile(outputFileName,"w");
        fprintf(outputFile,"%s\n",output);
        fclose(outputFile);
    
    }else{
        printf("%s\n", output);
    }

    free(s);
    freeLists(adjLists, vertices);
}
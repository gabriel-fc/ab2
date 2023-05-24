#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/heap.h"
#include "../common/inputHandler.h"


qElement **prim(int root, int vertices, qList *q, adjList **adjLists){
    int i;
    qElement **mst = (qElement**) malloc(vertices*sizeof(qElement));


    while(q->size){
        int mstIndex = vertices - q->size;
        qElement *u = pop(q);
        adjVertex *v = adjLists[u->vertex]->head;
        while(v){
            int vIndexAtQ = q->elementPosition[v->vertex]; 
            if(vIndexAtQ != -1 && q->heap[vIndexAtQ]->key  >= v->weight){
                decreaseKey(vIndexAtQ, v->weight, u->vertex, q);
            }
            v = v->next;
        }
        mst[mstIndex] = u;
    }
    return mst;
}

char *getMSTRep(qElement **mst, int vertices){
    int i;
    char *output = (char*) calloc(vertices*10, sizeof(char));
    char aux[12];
    for (i = 1; i < vertices; i++){
        sprintf(aux,"(%d,%d) ", mst[i]->vertex, mst[i]->neighbor);
        strcat(output, aux);
    }
    return output;
}

char *getMSTCost(qElement **mst, int vertices){
    int i, count = 0;
    char *output = (char*) calloc(11, sizeof(char));
    for (i = 0; i < vertices; i++){
        count += mst[i]->key; 
    }
    sprintf(output, "%d", count);
    return output ;
}



char printHelp(){
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        printf("menu de ajuda do algoritmo prim:\n");
        printf("- ao adiciona a flag '-f' seguido de uma string, define-se o nome do arquivo o qual será utilizado para retirar os dados de entrada.\n");
        printf("Caso o nome do arquivo esteja errado ou não exista, o programa irá ser encerrado com erro -1.\n");
        printf("- ao adicionar uma flag '-s' ao comando de execução, o programa retornará os vértices da AGM.\n Caso não, será retornado o custo da árvore.\n");
        printf("- ao adiciona a flag '-o' seguido de uma string, a saída será escrita em um arquivo com o nome da string. Caso não, será printado no console\n");
        printf("- ao adiciona a flag '-i' seguido de um número, define-se o vértice raiz da árvore. Caso não, o vertice padrão definido é o v = 1.\n");
        printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}

void main(int argc, char *argv[]){
    int vertices, edges, i, root = 1, hFlag = 0, sFlag = 0;
    char *inputFileName;
    char *outputFileName = "";
    char *output;

    readCommands(&hFlag, &sFlag, &root, &inputFileName, &outputFileName, argc, argv);
    FILE *inputFile = openFile(inputFileName, "r");
    readFirstLine(&vertices, &edges, inputFile);

    adjList **adjLists = createAdjLists(inputFile, vertices, edges);
    qList *q = initHeap(vertices, root);
    qElement **mst = prim(root, vertices, q, adjLists);


    if(hFlag){
        printHelp();
    } 
    if(sFlag) output = getMSTRep(mst, vertices);
    else output = getMSTCost(mst, vertices);
    if(strcmp(outputFileName, "")){
        FILE *outputFile = openFile(outputFileName,"w");
        fprintf(outputFile,"%s\n",output);
        fclose(outputFile);
    
    }else{
        printf("%s\n", output);
    }

    fclose(inputFile);
    freeLists(adjLists, vertices);
    freeQ(q);
    free(mst);
    free(output);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quickSort.h"
#include "../common/inputHandler.h"

FILE *inputFile; 
int vertices, edges, mstSize = 0;

void freeEdgesList(edge **edgesList){
    int i;
    for ( i = 0; i < edges; i++){
        free(edgesList[i]);
    }
    free(edgesList);
}

void freeVerticesList(vertex **verticesList){
    int i;
    for ( i = 0; i < vertices; i++){
        free(verticesList[i]);
    }
    free(verticesList);
}



edge **readEdges(){
    edge **edgesList = (edge**) malloc(edges * sizeof(edge));
    int i, u, v, weight;
    
    for (i = 0; i < edges; i++){
        fscanf(inputFile, "%d%d%d", &u, &v, &weight);

        edgesList[i] = (edge*) malloc(sizeof(edge*));
        edgesList[i]->u = u;
        edgesList[i]->v = v;
        edgesList[i]->weight = weight;
    }
    return edgesList;
}

vertex **_makeSet(){
    vertex **verticesList = (vertex**) malloc((vertices + 1) * sizeof(vertex));
    int i;
    for (i = 1; i <= vertices; i++){
        verticesList[i] = (vertex*) malloc(sizeof(vertex));
        verticesList[i]->parent = i;
        verticesList[i]->rank = 0;
    }
    return verticesList;
}


void _union(int u, int v, vertex **verticesList){
    int uParent = verticesList[u]->parent, vParent = verticesList[v]->parent; 
    if(verticesList[uParent]->rank >= verticesList[vParent]->rank){
        verticesList[vParent]->parent = uParent;
        if(verticesList[uParent]->rank == verticesList[vParent]->rank) verticesList[uParent]->rank++;
    }
    else verticesList[uParent]->parent = vParent;
}

int _find(int u, vertex **verticesList){
    int parent = verticesList[u]->parent;
    if(parent != u) 
        verticesList[u]->parent = _find(parent, verticesList);

    return verticesList[u]->parent;

}




edge **kruskal(edge **edgesList){
    edge **mst = (edge **) malloc((vertices-1) * sizeof(edge*));
    int i;
    vertex **verticesList = _makeSet();

    for (i = 0; i < edges; i++){
        int u = edgesList[i]->u;
        int v = edgesList[i]->v;
        if(_find(u, verticesList) != _find(v, verticesList)){
            mst[mstSize++] = edgesList[i];
            _union(u, v, verticesList);
        }
    }

    freeVerticesList(verticesList);
    return mst;
}


char *getMSTRep(edge **mst, int vertices){
    int i;
    char *output = (char*) calloc(vertices*10, sizeof(char));
    char aux[12];
    for (i = 1; i < mstSize; i++){
        sprintf(aux,"(%d,%d) ", mst[i]->u, mst[i]->v);
        strcat(output, aux);
    }
    return output;
}

char *getMSTCost(edge **mst, int vertices){
    int i, count = 0;
    char *output = (char*) calloc(11, sizeof(char));
    for (i = 0; i < mstSize; i++){
        count += mst[i]->weight; 
    }
    sprintf(output, "%d", count);
    return output ;
}




void printHelp(){
     printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        printf("menu de ajuda do algoritmo kruskal:\n");
        printf("- ao adiciona a flag '-f' seguido de uma string, define-se o nome do arquivo o qual será utilizado para retirar os dados de entrada.\n");
        printf("Caso o nome do arquivo esteja errado ou não exista, o programa irá ser encerrado com erro -1.\n");
        printf("- ao adicionar uma flag '-s' ao comando de execução, o programa retornará os vértices da AGM.\n Caso não, será retornado o custo da árvore.\n");
        printf("- ao adiciona a flag '-o' seguido de uma string, a saída será escrita em um arquivo com o nome da string. Caso não, será printado no console\n");
        printf("- caso haja uma flag -i, o programa retornará uma messagem de erro de execução pois o mesmo não suporta este comando");
        printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

}

void main(int argc, char *argv[]){
    int hFlag = 0, sFlag = 0;
    char *inputFileName;
    char *outputFileName = "";
    char *output;
    
    readCommands(&hFlag, &sFlag, NULL, &inputFileName, &outputFileName, argc, argv);
    inputFile = openFile(inputFileName, "r");
    readFirstLine(&vertices, &edges, inputFile);

    edge **edgesList = readEdges();
    sort(edgesList, 0, edges);
    edge **mst = kruskal(edgesList);
    
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

    freeEdgesList(edgesList);
    free(mst);
}
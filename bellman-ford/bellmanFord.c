#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#include "edgeList.h"
#include "../common/inputHandler.h"

#define INF INT_MAX


int vertices, edges;



void relax(int u, int v, int weight, int *distance){
    if(distance[u] != INF){
        if(distance[u] + weight < distance[v]) distance[v] = distance[u] + weight;
    }
}






bool bf(int root, edge **edgesList, int *distance){
    int i, j, currentU, currentV, u, v, weight;
    for (i = 1; i <= vertices; i++){
        if(i != root) distance[i] = INT_MAX;
        else distance[i] = 0;
    }

    for (j = 1; j < vertices; j++){
       for (i = 0; i < edges; i++){
            u = edgesList[i]->u;
            v = edgesList[i]->v;
            weight = edgesList[i]->weight;
            relax(u, v, weight, distance); 
       }
    }

    for (i = 0; i < edges; i++){
        u = edgesList[i]->u;
        v = edgesList[i]->v;
        weight = edgesList[i]->weight;
        if(distance[u] != INF && (distance[u] + weight < distance[v])) return false;
    }
    return true;
}

char printHelp(){
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        printf("menu de ajuda do algoritmo Bellman-Ford:\n");
        printf("- ao adiciona a flag '-f' seguido de uma string, define-se o nome do arquivo o qual será utilizado para retirar os dados de entrada.\n");
        printf("Caso o nome do arquivo esteja errado ou não exista, o programa irá ser encerrado com erro -1.\n");
        printf("- caso haja uma flag -s, o programa adicionará uma string após a linha com custos de cada vértice.\n Esta string informará a existência, ou não, de ciclos negativos.\n");
        printf("- ao adiciona a flag '-o' seguido de uma string, a saída será escrita em um arquivo com o nome da string. Caso não, será printado no console\n");
        printf("- ao adiciona a flag '-i' seguido de um número, define-se o vértice raiz da árvore. Caso não, o vertice padrão definido é o v = 1.\n");
        printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}


char *getCosts(int *distance, int vertices){
    char *output = (char*) calloc((vertices + 1) * 10, sizeof(char));
    char aux[10];
    int i;
    for (i = 1; i <= vertices; i++){
    sprintf(aux, "%d:%d ", i, distance[i] != INF ? distance[i] : -1);
    strcat(output, aux);    
    }
    strcat(output, "\n");
    return output;
}
char *getRes(bool res){
    return res ? "Não existem ciclos negativos.\n" : "Existem ciclos negativos.\n";
}

void main(int argc, char *argv[]){

    int i, root = 1, hFlag = 0, sFlag = 0;
    char *inputFileName;
    char *outputFileName = "";

    readCommands(&hFlag, &sFlag, &root, &inputFileName, &outputFileName, argc, argv);
    FILE *inputFile = openFile(inputFileName, "r");
    readFirstLine(&vertices, &edges, inputFile);
    edge **edgesList =  readEdgeList(edges, inputFile);

    int *distance = (int*) malloc((vertices+1) * sizeof(int));
    bool res = bf(root, edgesList, distance);
    char *output = getCosts(distance, vertices);
    
    if(hFlag){
        printHelp();
    } 
    if(sFlag){
        strcat(output, getRes(res));
    }
    if(strcmp(outputFileName, "")){
        FILE *outputFile = openFile(outputFileName,"w");
        fprintf(outputFile,"%s\n",output);
        fclose(outputFile);
    
    }else{
        printf("%s", output);
    }

    fclose(inputFile);
    free(distance);
    free(output);
    freeEdgeList(edges, edgesList);
    
}
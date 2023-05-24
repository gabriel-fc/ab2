#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE *f;

int **adjMatrix;


int getRandomNumber(int min, int max) {
    int randomNumber = (rand() % (max - min + 1)) + min;
    if(!randomNumber) return getRandomNumber(min, max);
    return randomNumber;
}

void printRandomEdge(int vertices, int min, int max){

    int u = getRandomNumber(1, vertices);
    int v = getRandomNumber(1, vertices);
    int weight = getRandomNumber(min, max);
    while(adjMatrix[u][v]){
        u = getRandomNumber(1, vertices);
        v = getRandomNumber(1, vertices);
    }
    
    fprintf(f, "%d %d %d", u, v, weight);
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;
}


void main() {
    srand(time(NULL));
    int vertices = 200, edges = 13000, i;
    char *fileName = (char*) malloc(50 * sizeof(char));
    fileName;
    printf("enter the numbers of vertices and edges:\n");
    scanf("%d%d", &vertices, &edges);
    printf("enter the file name:\n");
    scanf("%s", fileName);
    
    f = fopen(fileName, "w");
    if (f== NULL) {
        printf("Failed to open the file.\n");
        return;
    }
    
    fprintf(f, "%d %d\n", vertices, edges);
    adjMatrix = (int **) calloc(vertices +1, sizeof(int*));
    for (i = 1; i <= vertices; i++){
        adjMatrix[i] = (int*) calloc(vertices +1, sizeof(int));
    }
    for (i = 0; i < edges; i++){
        printRandomEdge(vertices, -10, 40);
        if(i < edges -1) fprintf(f,"\n");
    }

    fclose(f);
    free(fileName);
    for (i = 1; i <= vertices; i++){
        free(adjMatrix[i]);
    }
    free(adjMatrix);
    
}


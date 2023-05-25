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

void insertRandomEdge(int vertices, int min, int max){

    int u = getRandomNumber(1, vertices);
    int v = getRandomNumber(1, vertices);
    int weight = getRandomNumber(min, max);
    while(adjMatrix[u][v] || u == v){
        u = getRandomNumber(1, vertices);
        v = getRandomNumber(1, vertices);
    }

    adjMatrix[u][v] = weight;
}

void insertRandomNegativeLoop(int vertices, int min, int size){
    int arr[size], i = 0;
    int *buffer = (int*) calloc(vertices+1, sizeof(int));
    while (i < size){
        int u = getRandomNumber(1, vertices);
        if(!buffer[u]){
            arr[i++] = u;
            buffer[u]++;
        }
    }
    for (i = 0; i < size-1; i++){
        adjMatrix[arr[i]][arr[i+1]] = getRandomNumber(min, -1);
    }
    adjMatrix[arr[size-1]][arr[0]] = getRandomNumber(min, -1);
    
}


void main() {
    srand(time(NULL));
    int vertices = 200, edges = 13000, i, j, count = 0, loopSize, loopQuant;
    char *fileName = (char*) malloc(50 * sizeof(char));
    fileName;
    printf("enter the numbers of vertices and edges:\n");
    scanf("%d%d", &vertices, &edges);
    printf("enter the numbers of loops and it's size:\n");
    scanf("%d%d", &loopQuant, &loopSize);
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

    for (i = 0; i < loopQuant; i++){
        insertRandomNegativeLoop(vertices, -10, loopSize);
    }
    
    for (i = 0; i < edges - (loopSize*loopQuant); i++){
        insertRandomEdge(vertices, 1, 40);
    }

    for (i = 1; i <= vertices; i++){
        for (j = 1; j <= vertices; j++){
            if(adjMatrix[i][j]) {
                fprintf(f, "%d %d %d", i, j, adjMatrix[i][j]);
                count++;
                if(count < edges) fprintf(f,"\n");
            }
        }   
    }
    

    fclose(f);
    free(fileName);
    for (i = 1; i <= vertices; i++){
        free(adjMatrix[i]);
    }
    free(adjMatrix);
    
}


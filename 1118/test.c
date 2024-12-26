#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

#define MAX_SIZE 20
#define MALLOC(p,s) \
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory"); \
        exit(EXIT_FAILURE); \
    }

typedef struct node {
    int key;
    struct node* link;
} node, *nodePointer;

typedef struct {
    nodePointer head[MAX_SIZE];
} Graph;

nodePointer createNode(int k);
void initGraph(Graph *graph, int n);
void addEdge(Graph *graph, int i, int j);
void printGraph(Graph *graph, int n);

int main () {
    FILE *file = fopen("in1.txt", "r");

    Graph graph;
    int n, k;
    fscanf(file, "%d", &n);

    initGraph(&graph, n);

    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            fscanf(file, "%d", &k);

            if (k == 1)
                addEdge(&graph, i, j);
        }
    }
    fclose(file);

    printGraph(&graph, n);
}

void initGraph(Graph *graph, int n) {
    for (int i = 1; i <= n; i++) {
        graph->head[i] = NULL;
    }
}

nodePointer createNode(int k) {
    nodePointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->key = k;
    newNode->link = NULL;
    return newNode;
}

void addEdge(Graph *graph, int i, int j) {
    nodePointer newNode = createNode(j);
    if (graph->head[i] == NULL) {
        graph->head[i] = newNode;
    } else {
        nodePointer current = graph->head[i];
        while (current->link != NULL)
            current = current->link;
        current->link = newNode;
    }
    
    newNode = createNode(i);
    if (graph->head[j] == NULL) {
        graph->head[j] = newNode;
    } else {
        nodePointer current = graph->head[j];
        while (current->link != NULL)
            current = current->link;
        current->link = newNode;
    }
}

void printGraph(Graph *graph, int n) {
    nodePointer current;
    for (int i = 1; i <= n; i++) {
        printf("vertex %d : ", i);
        current = graph->head[i];
        while (current != NULL) {
            printf("%d ", current->key);
            current = current->link;
        }
        printf("\n");
    }
}
#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAD 10
#define MALLOC(p, s) \
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory"); \
        exit(EXIT_FAILURE); \
    }

typedef struct node {
    int vertex1;
    int vertex2;
    struct node* link1;
    struct node* link2;
} node, *nodePointer;

typedef struct Graph {
    nodePointer head[MAX_HEAD];
} Graph;

void initGraph(Graph* graph, int n);
nodePointer createNode(int v1, int v2);
void addEdge(Graph* graph, int v1, int v2);
void printGraph(Graph* graph, int n);

int main() {
    int n = 6; // Number of vertices
    Graph graph;
    initGraph(&graph, n);

    // Define edges
    addEdge(&graph, 1, 0);
    addEdge(&graph, 1, 3);
    addEdge(&graph, 2, 1);
    addEdge(&graph, 2, 5);
    addEdge(&graph, 3, 2);
    addEdge(&graph, 3, 5);
    addEdge(&graph, 3, 4);
    addEdge(&graph, 4, 0);
    addEdge(&graph, 5, 1);
    addEdge(&graph, 5, 0);
    addEdge(&graph, 5, 4);

    // Print adjacency multilist
    printGraph(&graph, n);

    return 0;
}

void initGraph(Graph* graph, int n) {
    for (int i = 0; i < n; i++) {
        graph->head[i] = NULL;
    }
}

nodePointer createNode(int v1, int v2) {
    nodePointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->vertex1 = v1;
    newNode->vertex2 = v2;
    newNode->link1 = NULL;
    newNode->link2 = NULL;
    return newNode;
}

void addEdge(Graph* graph, int v1, int v2) {
    nodePointer newNode = createNode(v1, v2);
    newNode->link1 = graph->head[v1];
    graph->head[v1] = newNode;
}

void printGraph(Graph* graph, int n) {
    for (int i = 0; i < n; i++) {
        printf("Vertex %d: ", i);
        nodePointer current = graph->head[i];
        while (current) {
            printf("-> (%d, %d) ", current->vertex1, current->vertex2);
            current = current->link1;
        }
        printf("\n");
    }
}

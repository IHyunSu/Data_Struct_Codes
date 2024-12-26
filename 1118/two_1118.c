#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10
#define MALLOC(p,s) \
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory"); \
        exit(EXIT_FAILURE); \
    }
#define FALSE 0
#define TRUE 1

typedef struct Node {
    int data;
    struct Node* link;
} Node, *NodePointer;

typedef struct {
    NodePointer head[MAX_VERTEX];
} Graph;

short int visited[MAX_VERTEX];

NodePointer createNode (int src);
void initGraph (Graph *graph, int n);
void addEdge (Graph *graph, int src, int dest);
void dfs (int v, Graph *graph);

int main () {
    FILE *file = fopen("in1.txt", "r");

    int n, tmp;
    fscanf(file, "%d", &n);
    Graph graph;

    initGraph(&graph, n);

    for (int i = 1; i <= n; i++) {
        visited[i] = FALSE;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            fscanf(file, "%d", &tmp);
            if (tmp) {
                addEdge(&graph, i, j);
            }
        }
    }
    fclose(file);

    scanf("%d", &tmp);
    dfs(tmp, &graph);
}

NodePointer createNode (int src) {
    NodePointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->data = src;
    newNode->link = NULL;
    return newNode;
}

void initGraph (Graph *graph, int n) {
    for (int i = 1; i <= n; i++) {
        graph->head[i] = NULL;
    }
}

void addEdge (Graph *graph, int src, int dest) {
    NodePointer newNode = createNode(dest);
    newNode->link = graph->head[src];
    graph->head[src] = newNode;

    newNode = createNode(src);
    newNode->link = graph->head[dest];
    graph->head[dest] = newNode;
}

void dfs (int v, Graph *graph) {
    NodePointer w;
    visited[v] = TRUE;
    printf("%d ", v);
    for (w = graph->head[v]; w; w = w->link) {
        if (!visited[w->data]) dfs(w->data, graph);
    }
}
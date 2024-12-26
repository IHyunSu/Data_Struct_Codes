#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAD 10
#define TRUE 1
#define FALSE 0
#define MALLOC(p,s) \
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory"); \
        exit(EXIT_FAILURE); \
    }

typedef struct node {
    int data;
    struct node* link;
} node, *nodePointer;

typedef struct {
    nodePointer head[MAX_HEAD];
} Graph;

int queue[MAX_HEAD];
int rear = -1, front = 0;

short int visited[MAX_HEAD];

void initGraph(Graph *graph, int n);
nodePointer createNode(int key);
void insertNode(Graph *graph, int i, int j);
void printNode(Graph *graph, int n);
void dfs(int v, Graph *graph);
void addq(int v);
int deleteq();
void bfs(int v, Graph *graph);


int main () {
    FILE *file = fopen("in.txt", "r");
    Graph graph;
    int n, temp;
    fscanf(file, "%d", &n);

    initGraph(&graph, n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            fscanf(file, "%d", &temp);
            if (temp != 0) {
                insertNode(&graph, i, j);
            }
        }
    }
    fclose(file);

    printNode(&graph, n);

    for (int i = 0; i < n; i++) {
        visited[i] = FALSE;
    }

    scanf("%d", &temp);
    printf("DFS(%d) : ", temp);
    dfs(temp, &graph);

    for (int i = 0; i < n; i++) {
        visited[i] = FALSE;
    }

    printf("\n");

    printf("BFS(%d) : ", temp);
    bfs(temp, &graph);

}

void initGraph(Graph *graph, int n) {
    for (int i = 0; i < n; i++) {
        graph->head[i] = NULL;
    }
}

nodePointer createNode(int key) {
    nodePointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->data = key;
    newNode->link = NULL;
    return newNode;
}

void insertNode(Graph *graph, int i, int j) {
    nodePointer newNode = createNode(j);
    if (graph->head[i] == NULL) {
        graph->head[i] = newNode;
    } else {
        nodePointer current = graph->head[i];
        while (current->link != NULL) {
            current = current->link;
        }
        current->link = newNode;
    }

    newNode = createNode(i);
    if (graph->head[j] == NULL) {
        graph->head[j] = newNode;
    } else {
        nodePointer current = graph->head[j];
        while (current->link != NULL) {
            current = current->link;
        }
        current->link = newNode;
    }
}

void printNode(Graph *graph, int n) {
    for (int i = 0; i < n; i++) {
        printf("Vertex %d : ", i);
        nodePointer current = graph->head[i];
        while(current) {
            printf("%d ", current->data);
            current = current->link;
        }
        printf("\n");
    }
}

void dfs(int v, Graph *graph) {
    nodePointer w;
    visited[v] = TRUE;
    printf("%d ", v);
    for (w = graph->head[v]; w != NULL; w = w->link) {
        if (!visited[w->data]) {
            dfs(w->data, graph);
        }
    }
}

void addq(int v) {
    if (front == MAX_HEAD -1) {
        printf("queue Full");
        exit(1);
    }
    queue[++rear] = v;
}

int deleteq() {
    if (front > rear) {
        printf("stack empty");
        return 0;
    }
    return queue[front++];
}

void bfs(int v, Graph *graph) {
    nodePointer w;
    printf("%d ", v);
    visited[v] = TRUE;
    addq(v);
    while (front <= rear) {
        v = deleteq();
        for (w = graph->head[v]; w; w = w->link) {
            if (!visited[w->data]) {
                addq(w->data);
                printf("%d ", w->data);
                visited[w->data] = TRUE;
            }
        }
    }

}
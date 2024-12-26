#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p,s) \
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory"); \
        exit(EXIT_FAILURE); \
    }

#define MAX_VERTEX_SIZE 20
#define TRUE 1
#define FALSE 0

short int visited[MAX_VERTEX_SIZE];
typedef struct node {
    int data;
    struct node* link;
}node, *nodePointer;

typedef struct {
    nodePointer head[MAX_VERTEX_SIZE];
}Graph;

void initVisited(int n);
void initGraph(Graph *graph, int n);
nodePointer createEdge(int d);
void addEdge(Graph *graph, int i, int j);
void dfs(int v, Graph *graph);
void add(int v);
int delete();
void bfs(int v, Graph *graph);
void printGraph(Graph* graph, int n);

int queue[MAX_VERTEX_SIZE];
int rear = -1, front = 0;

int main () {
    FILE *file = fopen("in4.txt", "r");
    int n, temp;
    Graph graph;

    fscanf(file, "%d", &n);

    initGraph(&graph, n);
    initVisited(n);
    for (int i = 0; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            fscanf(file, "%d", &temp);

            if (temp)
                addEdge(&graph, i, j);
        }
    }
    fclose(file);

    printGraph(&graph, n);

    scanf("%d", &temp);
    printf("DFS( %d ) : ", temp);
    dfs(temp, &graph);

    initVisited(n);
    printf("\nBFS( %d ) : ", temp);
    bfs(temp, &graph);

}

void initVisited(int n) {
    for (int i = 0; i <= n; i++) {
        visited[i] = FALSE;
    }
}

void initGraph(Graph *graph, int n) {
    for (int i = 0; i <= n; i++) {
        graph->head[i] = NULL;
    }
}

nodePointer createEdge(int d) {
    nodePointer temp;
    MALLOC(temp, sizeof(*temp));
    temp->data = d;
    temp->link = NULL;
    return temp;
}

void addEdge(Graph *graph, int i, int j) {
    nodePointer newNode = createEdge(j);
    if (graph->head[i] == NULL) {
        graph->head[i] = newNode;
    } else {
        nodePointer current = graph->head[i];
        while (current->link != NULL)
            current = current->link;
        current->link = newNode;
    }

    newNode = createEdge(i);
    if (graph->head[j] == NULL) {
        graph->head[j] = newNode;
    } else {
        nodePointer current = graph->head[j];
        while (current->link != NULL)
            current = current->link;
        current->link = newNode;
    }
}

void dfs(int v, Graph *graph) {
    nodePointer w;
    visited[v] = TRUE;
    printf("%d ", v);

    for (w = graph->head[v]; w; w = w->link) {
        if (!visited[w->data])
            dfs(w->data, graph);
    }
}

void add(int v) {
    if (rear == MAX_VERTEX_SIZE-1) {
        printf("queue Full");
        return;
    }
    queue[++rear] = v;
}

int delete() {
    if (front > rear) {
        printf("queue Empty");
        exit(1);
    }
    return queue[front++];
}

void bfs(int v, Graph *graph) {
    nodePointer w;
    visited[v] = TRUE;
    printf("%d ", v);
    add(v);
    while (front <= rear) {
        v = delete();
        for (w = graph->head[v]; w; w = w->link) {
            if (!visited[w->data]) {
                printf("%d ", w->data);
                add(w->data);
                visited[w->data] = TRUE;
            }
        }
    }
}

void printGraph(Graph* graph, int n) {
    for (int i = 0; i < n; i++) {
        printf("Vertex %d: ", i);
        nodePointer temp = graph->head[i];
        while (temp) {
            printf("%d ", temp->data);
            temp = temp->link;
        }
        printf("\n");
    }
}

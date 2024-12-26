#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAD 10
#define MALLOC(p,s) \
	if ((p = malloc(s)) == NULL) { \
		fprintf(stderr, "Insufficient Memory"); \
		exit(EXIT_FAILURE); \
	}
#define TRUE 1
#define FALSE 0


typedef struct node {
    int data;
    struct node* link;
} node, *nodePointer;

nodePointer nend = NULL;

typedef struct Graph {
    nodePointer head[MAX_HEAD];
} Graph;

int front = 0;
int rear = -1;
int queue[MAX_HEAD];

short int visited[MAX_HEAD];

void initGraph(Graph* graph, int n);
nodePointer createNode(int d);
void insert(Graph* graph, int i, int j);
void dfs(int v, Graph *graph);
void bfs(int v, Graph* graph);
void addq(int v);
int deleteq();
void printGraph(Graph* graph, int n);

int main() {
    FILE* file;
    if ((file = fopen("in.txt", "r")) == NULL) {
        printf("Can not open file");
        exit(1);
    }

    int n, temp;

    fscanf(file, "%d", &n);

    Graph graph;

    initGraph(&graph, n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            fscanf(file, "%d", &temp);
            if (temp) {
                insert(&graph, i, j);
            }
        }
    }
    fclose(file);

    for (int i = 0; i < n; i++) {
        visited[i] = FALSE;
    }

    printGraph(&graph, n);

    scanf("%d", &temp);

    printf("DFS(%d) : ", temp);
    dfs(temp, &graph);

    // 방문 배열 초기화
    for (int i = 0; i < n; i++) {
        visited[i] = FALSE;
    }

    printf("\nBFS(%d) : ", temp);
    bfs(temp, &graph);

}

void initGraph(Graph* graph, int n) {
    for (int i = 0; i < n; i++) {
        graph->head[i] = NULL;
    }
}

nodePointer createNode(int d) {
    nodePointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->data = d;
    newNode->link = NULL;
    return newNode;
}

void insert(Graph* graph, int i, int j) {
    nodePointer newNode = createNode(j);
    newNode->link = graph->head[i];
    graph->head[i] = newNode;

    newNode = createNode(i);
    newNode->link = graph->head[j];
    graph->head[j] = newNode;
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
    if (rear == MAX_HEAD - 1) {
        printf("queue full\n");
        exit(1);
    }
    queue[++rear] = v;
}

int deleteq() {
    if (front > rear) {
        printf("queue empty!\n");
        exit(1);
    }
    return queue[front++];
}

void bfs(int v, Graph* graph) {
    nodePointer w;
    printf("%d ", v);
    visited[v] = TRUE;
    addq(v);

    while (front <= rear) {
        v = deleteq();
        for (w = graph->head[v]; w != NULL; w = w->link) {
            if (!visited[w->data]) {
                printf("%d ", w->data);
                addq(w->data);
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

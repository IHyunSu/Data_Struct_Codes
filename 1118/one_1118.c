#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10
#define MALLOC(p,s) \
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory"); \
        exit(EXIT_FAILURE); \
    }

// 연결 리스트 노드 구조체 정의
typedef struct Node {
    int vertex;
    struct Node* next;
} Node, *NodePointer;

// 인접 리스트 구조체 정의
typedef struct Graph {
    NodePointer head[MAX_NODES];
} Graph;

Node* createNode(int vertex);
void initGraph(Graph* graph, int n);
void addEdge(Graph* graph, int src, int dest);
void printGraph(Graph* graph, int n);

// 메인 함수
int main() {
    FILE* file = fopen("in1.txt", "r");
    if (!file) {
        printf("File could not be opened.\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    Graph graph;
    initGraph(&graph, n);

    // 5 1 1 0 1 1 0 1 0 0 1
    // 인접 행렬의 upper diagonal 부분 읽기
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int edge;
            fscanf(file, "%d", &edge);
            if (edge == 1) {
                addEdge(&graph, i, j);
            }
        }
    }

    fclose(file);

    // 그래프 출력
    printGraph(&graph, n);

    return 0;
}

// 노드 생성 함수
NodePointer createNode(int vertex) {
    NodePointer newNode;
    MALLOC(newNode, sizeof(*newNode))
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// 그래프 초기화 함수
void initGraph(Graph* graph, int n) {
    for (int i = 1; i <= n; i++) {
        graph->head[i] = NULL;
    }
}

// 엣지 추가 함수
void addEdge(Graph* graph, int src, int dest) {
    NodePointer newNode = createNode(dest);
    newNode->next = graph->head[src];
    graph->head[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->head[dest];
    graph->head[dest] = newNode;
}

// 그래프 출력 함수
void printGraph(Graph* graph, int n) {
    for (int i = 1; i <= n; i++) {
        printf("Vertex %d: ", i);
        NodePointer temp = graph->head[i];
        while (temp) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

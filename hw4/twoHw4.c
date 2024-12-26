#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define MALLOC(p, s) \
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory\n"); \
        exit(EXIT_FAILURE); \
    }

// Edge 노드 구조체
typedef struct node {
    int vertex1;            // 현재 노드의 정점
    int vertex2;            // 가리키는 정점
    struct node* link1;     // vertex1에서의 다음 연결
    struct node* link2;     // vertex2에서의 다음 연결
} node, *nodePointer;

// 그래프 구조체
typedef struct Graph {
    nodePointer head[MAX_VERTICES]; // 인접 멀티리스트의 헤드 배열
    int vertexCount;               // 정점의 개수
} Graph;

// 함수 선언
void initGraph(Graph* graph, int n);
nodePointer createNode(int v1, int v2);
void addEdge(Graph* graph, int v1, int v2);
void buildGraphFromFile(Graph* graph, const char* filename);
void printAdjacentList(Graph* graph, int vertex);

int main() {
    Graph graph;
    buildGraphFromFile(&graph, "in.txt");

    int vertex;
    while (1) {
        printf("Enter a vertex (-1 to exit): ");
        scanf("%d", &vertex);

        if (vertex == -1) break;

        printAdjacentList(&graph, vertex);
    }

    return 0;
}

// 그래프 초기화
void initGraph(Graph* graph, int n) {
    graph->vertexCount = n;
    for (int i = 0; i < n; i++) {
        graph->head[i] = NULL;
    }
}

// 간선 노드 생성
nodePointer createNode(int v1, int v2) {
    nodePointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->vertex1 = v1;
    newNode->vertex2 = v2;
    newNode->link1 = NULL;
    newNode->link2 = NULL;
    return newNode;
}

// 간선 추가
void addEdge(Graph* graph, int v1, int v2) {
    nodePointer newNode = createNode(v1, v2);

    // vertex1의 인접 리스트에 추가
    newNode->link1 = graph->head[v1];
    graph->head[v1] = newNode;

    // vertex2의 인접 리스트에 추가
    newNode->link2 = graph->head[v2];
    graph->head[v2] = newNode;
}

// 파일로부터 그래프 구성
void buildGraphFromFile(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Unable to open file.\n");
        exit(EXIT_FAILURE);
    }

    int n;
    fscanf(file, "%d", &n); // 정점 개수 읽기
    initGraph(graph, n);

    int temp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &temp);
            if (temp && i < j) { // i < j로 중복 간선 방지 (무방향 그래프)
                addEdge(graph, i, j);
            }
        }
    }
    fclose(file);
}

// 인접 리스트 출력
void printAdjacentList(Graph* graph, int vertex) {
    if (vertex >= graph->vertexCount) {
        printf("Vertex %d does not exist.\n", vertex);
        return;
    }

    printf("Adjacent vertices of %d:", vertex);
    nodePointer current = graph->head[vertex];
    while (current) {
        if (current->vertex1 == vertex) {
            printf(" %d", current->vertex2);
            current = current->link1;
        } else {
            printf(" %d", current->vertex1);
            current = current->link2;
        }
    }
    printf("\n");
}

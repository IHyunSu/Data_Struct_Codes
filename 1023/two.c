#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p,s) \
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory"); \
        exit(EXIT_FAILURE); \
    }

typedef struct node {
    int data;
    struct node* next;
    struct node* prev;
} *nodePointer;

nodePointer createNode(int value);
void dinsert(nodePointer header, nodePointer newNode);
void printList(nodePointer header);
void printReverseList(nodePointer header);

int main() {
    nodePointer header;
    MALLOC(header, sizeof(*header));
    header->next = NULL;
    header->prev = NULL;
    FILE *file = fopen("in.txt", "r");
    int value;

    if (file == NULL) {
        fprintf(stderr, "파일을 열 수 없습니다.\n");
        return EXIT_FAILURE;
    }

    while (fscanf(file, "%d", &value) == 1) {
        nodePointer newNode = createNode(value);
        dinsert(header, newNode);
    }

    fclose(file);

    // 리스트 출력
    printList(header);
    printReverseList(header);

    nodePointer current = header->next;
    while (current != NULL) {
        nodePointer temp = current;
        current = current->next;
        free(temp);
    }
    free(header);

    return 0;
}

nodePointer createNode(int value) {
    nodePointer newNode = (nodePointer)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// 정렬된 순서로 노드 삽입
void dinsert(nodePointer header, nodePointer newNode) {
    nodePointer current = header->next;

    // 빈 리스트인 경우
    if (current == NULL) {
        header->next = newNode;
        newNode->prev = header;
        return;
    }

    // 리스트를 순회하여 올바른 위치를 찾는다.
    while (current != NULL && current->data < newNode->data) {
        current = current->next;
    }

    // 새 노드를 삽입
    if (current != NULL) {
        newNode->next = current; // 새 노드가 현재 노드를 가리킴
        newNode->prev = current->prev; // 새 노드의 이전 노드 설정
        current->prev->next = newNode; // 현재 노드의 이전 노드가 새 노드를 가리킴
        current->prev = newNode; // 현재 노드의 이전 노드를 새 노드로 설정
    } else {
        // 리스트의 끝에 노드 추가
        nodePointer last = header;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newNode;
        newNode->prev = last;
    }
}

// 리스트를 오름차순으로 출력
void printList(nodePointer header) {
    nodePointer current = header->next; // 헤더 노드 다음부터 시작
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 리스트를 내림차순으로 출력
void printReverseList(nodePointer header) {
    nodePointer current = header;
    // 리스트의 끝으로 이동
    while (current->next != NULL) {
        current = current->next;
    }
    while (current != header) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}

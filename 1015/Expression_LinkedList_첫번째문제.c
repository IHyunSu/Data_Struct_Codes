#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p,s) \
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory\n"); \
        exit(EXIT_FAILURE); \
    }

typedef struct listNode *listPointer;
typedef struct listNode {
    int data;
    listPointer link;
} listNode;

listPointer first = NULL;

void insert(listPointer *first, int data);
void printList(listPointer first); 

int main () {
    FILE *file;
    if ((file = fopen("in1.txt", "r")) == NULL) {
        printf("Cannot open file\n");
        exit(1);
    }

    int data;
    while (fscanf(file, "%d", &data) == 1) {
        insert(&first, data);
    }
    fclose(file);

    printList(first);
    return 0;
}

void insert(listPointer *head, int data) {
    listPointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->data = data;
    newNode->link = NULL;

    // 내림차순으로 삽입
    if (*head == NULL || (*head)->data <= data) {
        newNode->link = *head;
        *head = newNode; 
    } else {
        listPointer current = *head;
        while (current->link != NULL && current->link->data > data) {
            current = current->link;
        }
        newNode->link = current->link;
        current->link = newNode;
    }
}

void printList(listPointer head) {
    listPointer current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->link;
    }
    printf("\n");
}

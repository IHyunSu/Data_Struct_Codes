#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p,s) \
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory"); \
        exit(EXIT_FAILURE); \
    }

typedef struct listNode *listPointer;
typedef struct listNode {
    int data;
    listPointer link;
} listNode;

listPointer first = NULL;

void insert(listPointer *first, int data);
int delete(listPointer *first, int data);
void printList(listPointer first);

int main () {
    FILE *file;
    if ((file = fopen("in1.txt", "r")) == NULL) {
        printf("Cannot open file");
        exit(1);
    }
    int data;
    while ((fscanf(file, "%d", &data)) == 1) {
        insert(&first, data);
    }
    printList(first);
    fclose(file);
    while (1) {
        scanf("%d", &data);
        if (data == -1) {
            exit(1);
        }
        else {
            if (delete(&first, data)) {
                printList(first);
                continue;
            }
            insert(&first, data);
            printList(first);
        }
    }
    return 0;
}

void insert(listPointer *first, int data) {
    listPointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->data = data;
    newNode->link = NULL;


    if (*first == NULL || (*first)->data >= data) {
        newNode->link = *first;
        *first = newNode;
    } else {
        listPointer current = *first;
        while (current->link != NULL && current->link->data < data) {
            current = current->link;
        }
        newNode->link = current->link;
        current->link = newNode;
    }
}

int delete (listPointer *first, int data) {
    listPointer current = *first;
    listPointer front = NULL;
    while (current != NULL && current->data != data) {
        front = current;
        current = current->link;
    }

    if (current != NULL) {
        if (front == NULL) {
            *first = current->link;
        }
        else {
            front->link = current->link;
        }
        free(current);
        return 1;
    }
    return 0;
}

void printList(listPointer first) {
    listPointer newNode = first;
    while (newNode != NULL) {
        printf("%d ", newNode->data);
        newNode = newNode->link;
    }
    printf("\n");
}
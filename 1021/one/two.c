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
    listPointer next;
} listNode;

listPointer head = NULL;
listPointer last = NULL;

void insert (listPointer *head, int data);
int delete (listPointer *head, int data);
void printList (listPointer head);

int main () {
    while(1) {
        int data;
        scanf("%d", &data);
        // if (delete(&first, data)) {
        //     printList(head);
        //     continue;
        // }
        insert(&head, data);
        printList(head);
    }
    return 0;
}

void insert(listPointer *head, int data) {
    listPointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL || (*head)->data >= data) {
        newNode->next = *head;
        *head = newNode;
    }
    else {
        listPointer current = *head;
        while(current->next != NULL && current->next->data < data) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = (*head)->next;
    }
}

void printList(listPointer head) {
    listPointer current = head;
    while (current != head->next) {
        printf("%d ", current->data);
        current = current->next;
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 15
#define MALLOC(p,s) \
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory"); \
        exit(EXIT_FAILURE); \
    }

#define REALLOC(p,s) \
    if ((p = realloc(p,s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory"); \
        exit(EXIT_FAILURE); \
    }

typedef struct {
    int key;
} element;

element *queue;
int rear = 0;
int front = 0;
int capacity = 1;

void addQ(element item);
void queueFull();
void delQ();
int queueEmpty();
void printList();
void menu();

int main () {
    MALLOC(queue, sizeof(*queue) * capacity);
    menu();
    free(queue);
    return 0;
}

void menu() {
    char select[2];
    int num;
    while (1)
    {
        scanf(" %c", select);
        if (strcmp(select, "I") == 0) {
            scanf("%d", &num);
            element item = {num};
            addQ(item);
        }
        else if (strcmp(select, "D") == 0) {
            delQ();
        }
        else if (strcmp(select, "F") == 0) {
            printList();
            return;
        }
    }
}

void queueFull() {
    capacity++;
    if (capacity >= MAX_QUEUE_SIZE) {
        capacity = MAX_QUEUE_SIZE;
    }
    REALLOC(queue, sizeof(*queue) * capacity);
}

void addQ(element item) {
    if (((rear + 1) % MAX_QUEUE_SIZE) >= front) {
        if (capacity < MAX_QUEUE_SIZE) {
            queueFull();
        }
        else {
            printf("queue가 가득 찼습니다!\n");
            return;
        }
    }
    queue[rear] = item;
    rear = (rear + 1) % MAX_QUEUE_SIZE;
}

int queueEmpty () {
    if (front == rear) {
        return 1;
    }
    return 0;
}

void delQ () {
    if (queueEmpty()) {
        printf("-1\n");
        return;
    }
    printf("%d\n", queue[front].key);
    front = (front + 1) % MAX_QUEUE_SIZE;
}

void printList() {
    if (queueEmpty()) {
        printf("queue가 비었습니다\n");
        return;
    }

    int i = front % MAX_QUEUE_SIZE;
    while(i != rear) {
        printf("%d ", queue[i].key);
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
}
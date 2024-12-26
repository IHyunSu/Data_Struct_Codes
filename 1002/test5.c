#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 5

typedef struct {
    int key;
} element;

element queue[MAX_QUEUE_SIZE];
int front = 0;
int rear = 0;

void addQ(element item);
void queueFull();
void delQ();
int queueEmpty();
void printQueue();
void menu();

int main () {
    menu();
    return 0;
}

void menu () {
    char select[2];
    int num;

    while(1) {
        scanf(" %c", select);
        if (strcmp(select,"I") == 0) {
            scanf("%d", &num);
            element item = {num};
            addQ(item);
        }
        else if (strcmp(select,"D") == 0) {
            delQ();
        }
        else if (strcmp(select,"F") == 0) {
            printQueue();
            return;
        }
    }
}

void queueFull() {
    printf("queue Full!");
    return;
}

void addQ(element item) {
    if (((rear + 1) % MAX_QUEUE_SIZE) == front) {
        queueFull();
        return;
    }
    queue[rear] = item;
    rear = (rear + 1) % MAX_QUEUE_SIZE; 
}

int queueEmpty() {
    if (rear == front) {
        return 1;
    }
    return 0;
}

void delQ() {
    if (queueEmpty()) {
        printf("-1\n");
        return;
    }
    printf("%d\n", queue[front].key);
    front = (front + 1) % MAX_QUEUE_SIZE;
}

void printQueue() {
    if (queueEmpty()) {
        printf("queue가 비었습니다.\n");
        return;
    }
    
    int i = front % MAX_QUEUE_SIZE;

    while (i != rear) {
        printf("%d ", queue[i].key);
        i = (i + 1) % MAX_QUEUE_SIZE;
    }

    return;

}
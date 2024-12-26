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
void queueEmpty();
void printQueue();
void menu();

int main () {
    menu();
    return 0;
}

void menu () {
    char target[2];
    int num;
    while (1) {
        scanf(" %c", target);
        if (strcmp(target, "I") == 0) {
            scanf("%d", &num);
            element item = {num};
            addQ(item);
        }
        else if (strcmp(target, "D") == 0) {
            delQ();
        }
        else if (strcmp(target, "F") == 0) {
            printQueue();
            break;
        }
        else {
            printf("다시 입력해 주세요\n");
        }
    }
}

void queueFull() {
    printf("queue가 가득 찼습니다.\n");
}

void addQ(element item) {
    if ((rear + 1) % MAX_QUEUE_SIZE == front) {
        queueFull();
        return;
    }
    queue[rear] = item;
    rear = (rear + 1) % MAX_QUEUE_SIZE;
}

void queueEmpty () {
    printf("-1\n");
}

void delQ() {
    element item = {0};
    if (front == rear) {
        queueEmpty();
        return;
    }
    printf("%d\n", queue[front].key);
    front = (front + 1) % MAX_QUEUE_SIZE;
}

void printQueue () {
    if (front == rear) {
        printf("queue가 비어있습니다.\n");
        return;
    }
    int i = front % MAX_QUEUE_SIZE;

    while (i != rear) {
        printf("%d ", queue[i].key);
        i = (i + 1) % MAX_QUEUE_SIZE;
    }    
    return;
}
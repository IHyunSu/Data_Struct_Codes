#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#define MAX_STACK_SIZE 10

typedef struct {
    int key;
} element;

element *stack;
int capacity = 1;
int top = -1;

void push(element item);
void stackFull();
void pop();
int stackEmpty();
void printStack();
void menu();

int main () {
    MALLOC(stack, sizeof(*stack));
    menu();
    free(stack);
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
            push(item);
        }
        else if(strcmp(target, "D") == 0) {
            pop();
        }
        else if(strcmp(target, "F") == 0) {
            printStack();
            return;
        }
    }
}

void stackFull() {
    capacity *= 2;
    if (capacity >= MAX_STACK_SIZE) {
        capacity = MAX_STACK_SIZE;
        return;
    }
    REALLOC(stack, sizeof(*stack) * capacity);
}

void push(element item) {
    if (top >= capacity - 1) {
        if (capacity >= MAX_STACK_SIZE) {
            printf("스택이 가득 찼습니다.\n");
            return;
        }
        stackFull();
    }

    stack[++top] = item;
}

int stackEmpty() {
    if (top < 0) {
        printf("스택이 비었습니다.\n");
        return 1;
    }
    return 0;
}

void pop() {
    if (stackEmpty()) {
        return;
    }
    top--;
}

void printStack () {
    if (stackEmpty()) {
        return;
    }

    for (int i = 0; i <= top; i++) {
        printf("%d ", stack[i].key);
    }
}
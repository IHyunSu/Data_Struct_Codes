#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;

#define MAX_STACK_SIZE 10
#define MALLOC(p,s)\
    if ((p = malloc(s)) == NULL) {\
        fprintf(stderr, "Insufficient Memory");\
        exit(EXIT_FAILURE);\
    }

#define REALLOC(d,t) \
    if ((d = realloc(d, t)) == NULL) { \
        fprintf(stderr, "Insufficient Memory"); \
        exit(EXIT_FAILURE); \
    }

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
    MALLOC(stack, capacity * sizeof(*stack));
    menu();
    free(stack);
    return 0;
}

void menu () {
    while (1) {
        char select[2];
        int num;
        scanf(" %c", select);
        if (strcmp(select, "I") == 0) {
            scanf("%d", &num);
            element item = {num};
            push(item);
        }
        else if (strcmp(select, "D") == 0) {
            pop();
        }
        else if (strcmp(select, "F") == 0) {
            printStack();
            break;
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
            printf("stack 크기가 초과되었습니다. D나 F 둘중에 하나를 하여주십시오.\n");
            return;
        }
        stackFull();
    }
    stack[++top] = item;
}

int stackEmpty() {
    if (top < 0) {
        return 1; 
    }
    return 0;
}

void pop() {
    if (stackEmpty()) {
        printf("stack empty\n");
        return;
    }
    top--;
}

void printStack() {
    if (stackEmpty()) {
        printf("stack empty\n");
        return;
    }
    for (int i = 0; i <= top; i++) {
        printf("%d ", stack[i].key);
    }
}
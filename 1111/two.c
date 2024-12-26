#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
    int key;
} element;

element heap[MAX_ELEMENTS];

void push(element item, int *n);
element pop(int *n);

int main () {
    FILE *file = fopen("in.txt", "r");
    int n, cnt = 0, temp;
    element item;
    fscanf(file, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &temp);
        item.key = temp;
        push(item, &cnt);
    }
    for (int i = 1; i <= cnt; i++) {
        printf("%d ", heap[i].key);
    }
    printf("\n");
    fscanf(file, "%d", &temp);
    for (int i = 0; i < temp; i++) {
        pop(&cnt);
    }
    fclose(file);

    for (int i = 1; i <= cnt; i++) {
        printf("%d ", heap[i].key);
    }
}

void push(element item, int *n) {
    int i;
    if (HEAP_FULL(*n)) {
        fprintf(stderr, "The heap is full. \n");
        exit(EXIT_FAILURE);
    }
    i = ++(*n);
    while ((i != 1) && (item.key > heap[i/2].key)) {
        heap[i] = heap[i/2];
        i /= 2;
    }
    heap[i] = item;
}

element pop(int *n) {
    int parent, child;
    element item, temp;
    if (HEAP_EMPTY(*n)) {
        fprintf(stderr, "The heap is empty\n");
        exit(EXIT_FAILURE);
    }
    item = heap[1];
    temp = heap[(*n)--];
    parent = 1;
    child = 2;
    while (child <= *n) {
        if ((child < *n) && (heap[child].key < heap[child+1].key))
            child++;
        if (temp.key >= heap[child].key) break;
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
    return item;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWAP(a, b, temp) { \
    temp = a; \
    a = b; \
    b = temp; \
}

#define MAX_SIZE 20

typedef struct {
    int key;
} element;

void adjust(element a[], int root, int n);
void heapSort(element a[], int n);

int main () {
    FILE* file = fopen("in.txt", "r");
    element heap[MAX_SIZE];
    int n = 0, temp;
    while ((fscanf(file, "%d", &temp)) == 1) {
        n++;
        heap[n].key = temp;
    }
    fclose(file);

    
    heapSort(heap, n);

    for (int i = 1; i <= n; i++) {
        printf("%d ", heap[i].key);
    }
}

void adjust(element a[], int root, int n) {
    int rootkey, child;
    element temp;
    temp = a[root];
    rootkey = a[root].key;
    child = root * 2;

    while (child <= n) {
        if ((child < n) && (a[child].key < a[child+1].key))
            child++;
        if (rootkey >= a[child].key) {
            break;
        } else {
            a[child/2] = a[child];
            child *= 2;
        }
    }
    a[child/2] = temp;
}

void heapSort(element a[], int n) {
    int i, j;
    element temp;

    for (i = n/2; i > 0; i--)
        adjust(a, i, n);
    for (j = n-1; j > 0; j--) {
        SWAP(a[1], a[j+1], temp);
        adjust(a, 1, j);
    }
}
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
    char c;
} element;

void adjust(element a[], int root, int n);
void heapSort(element a[], int n);

int main () {
    FILE *file = fopen("in2.txt", "r");

    element heap[MAX_SIZE];

    int n = 0, temp;
    char temp2;
    while ((fscanf(file, "%d %c", &temp, &temp2)) == 2) {
        n++;
        heap[n].key = temp;
        heap[n].c = temp2;
    }
    fclose(file);

    heapSort(heap, n);

    for (int i = 1; i <= n; i++) {
        printf("%d %c\n", heap[i].key, heap[i].c);
    }
}

void adjust(element a[], int root, int n) {
    int rootkey, child;
    element temp;
    temp = a[root];
    rootkey = a[root].key;
    child = root * 2;

    while (child <= n) {
        if ((child < n) && (a[child].key <= a[child+1].key))
            child++;
        if (rootkey > a[child].key) {
            break;
        } else {
            a[child/2] = a[child];
            child *= 2;
        }
    }
    a[child/2] = temp;
}

void heapSort(element a[], int n) {
    int i;
    element temp;
    for (i = n/2; i > 0; i--)
        adjust(a, i, n);
    for (i = n-1; i > 0; i--) {
        SWAP(a[1], a[i+1], temp);
        adjust(a, 1, i);
    }
}
#include <stdio.h>
#include <stdlib.h>

#define SWAP(a, b) do { \
    element temp = a; \
    a = b; \
    b = temp; \
} while(0)

#define MAX_NODE 30

typedef struct {
    int key;
} element;

void heapSort(element* a, int n);
void adjust(element* a, int root, int n);
void display(element a[], int n);

int main() {
    FILE* file = fopen("in.txt", "r");
    if (!file) {
        fprintf(stderr, "Error opening file.\n");
        return EXIT_FAILURE;
    }
    
    element a[MAX_NODE];
    int i = 0, n, tmp;

    while (fscanf(file, "%d", &tmp) == 1 && i < MAX_NODE) {
        a[i].key = tmp;
        i++;
    }
    fclose(file);
    n = i;

    heapSort(a, n);
    display(a, n);

    return 0;
}

void heapSort(element* a, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        adjust(a, i, n);
    }
    for (int i = n - 1; i > 0; i--) {
        SWAP(a[0], a[i]);
        adjust(a, 0, i);
    }
}

void adjust(element* a, int root, int n) {
    int child;
    element temp = a[root];
    while ((child = 2 * root + 1) < n) { 
        if (child + 1 < n && a[child].key < a[child + 1].key) {
            child++; 
        }
        if (temp.key >= a[child].key) break; 
        a[root] = a[child];
        root = child;
    }
    a[root] = temp; 
}

void display(element a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i].key);
    }
    printf("\n");
}

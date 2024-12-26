#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

#define SWAP(a, b) do { \
    element temp = a; \
    a = b; \
    b = temp; \
} while(0)

#define MAX_NODE 30

typedef struct {
    int key;         // 정수 값
    char value;      // 문자 값
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
    int i = 0, n;

    while (fscanf(file, "%d %c", &a[i].key, &a[i].value) == 2 && i < MAX_NODE) {
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
    while (2 * root + 1 < n) { // left child index
        child = 2 * root + 1; // left child
        if (child + 1 < n && a[child].key < a[child + 1].key) {
            child++; // right child
        }
        if (temp.key >= a[child].key) break;
        a[root] = a[child];
        root = child;
    }
    a[root] = temp;
}

void display(element a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d %c\n", a[i].key, a[i].value);
    }
}

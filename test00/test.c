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
    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

    element heap[MAX_SIZE];
    int n = 0, temp;
    while ((fscanf(file, "%d", &temp)) == 1) {
        n++;
        heap[n].key = temp; // Read into the heap array
    }
    fclose(file);

    // Perform heap sort
    heapSort(heap, n);

    // Print sorted elements
    for (int i = n; i > 0; i--) {
        printf("%d ", heap[i].key);
    }
    return 0;
}

// Maintain the max heap property
void adjust(element a[], int root, int n) {
    int rootkey = a[root].key;
    element temp = a[root];
    int child = root * 2;

    while (child <= n) {
        // Select the larger child
        if (child < n && a[child].key < a[child + 1].key) {
            child++;
        }

        // If the root is larger than the largest child, stop
        if (rootkey >= a[child].key) {
            break;
        } else {
            // Move the larger child up
            a[child / 2] = a[child];
            child *= 2;
        }
    }
    a[child / 2] = temp;
}

// Perform heap sort
void heapSort(element a[], int n) {
    int i, j;
    element temp;

    // Build the initial max heap
    for (i = n / 2; i > 0; i--) {
        adjust(a, i, n);
    }

    // Sort the heap
    for (j = n - 1; j > 0; j--) {
        SWAP(a[1], a[j + 1], temp); // Move the max element to the end
        adjust(a, 1, j);           // Adjust the remaining heap
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STR_LEN 10  // Maximum string length
#define MAX_ELEMENTS 10 // Maximum number of elements
#define RADIX 27        // Alphabet size (26 letters + 1 for padding)

typedef struct {
    char value[MAX_STR_LEN + 1]; // +1 for null terminator
} element;

int digit(char c, int pos);
int radixSort(element a[], int link[], int d, int r, int n);
void printArrays(element a[], int link[], int n);

int main() {
    FILE *file = fopen("in.txt", "r");
    if (file == NULL) {
        perror("Unable to open file");
        return EXIT_FAILURE;
    }

    element a[MAX_ELEMENTS];
    int link[MAX_ELEMENTS];
    int i = 0;

    while ((fscanf(file, "%s", a[i].value) == 1) && (i < MAX_ELEMENTS)) {
        i++;
    }
    fclose(file);

    for (int j = 0; j < i; j++) {
        int len = strlen(a[j].value);
        for (int k = len; k < MAX_STR_LEN; k++) {
            a[j].value[k] = 'a' - 1;
        }
        a[j].value[MAX_STR_LEN] = '\0';
    }

    int first = radixSort(a, link, MAX_STR_LEN, RADIX, i);

    // Print sorted arrays
    for (int current = first; current != -1; current = link[current]) {
        printf("%s ", a[current].value);
    }

    return 0;
}

// Extract the value of the character at the given position
int digit(char c, int pos) {
    return c - ('a' - 1); // Map 'a'-1 to 0, 'a' to 1, ..., 'z' to 26
}

// Perform radix sort using a linked list
int radixSort(element a[], int link[], int d, int r, int n) {
    int front[r], rear[r];
    int first, last, current, bin;

    // Initialize the link array
    for (int i = 0; i < n - 1; i++) link[i] = i + 1;
    link[n - 1] = -1; // End of list
    first = 0;

    // Iterate over each position from least significant to most significant
    for (int pos = d - 1; pos >= 0; pos--) {
        for (bin = 0; bin < r; bin++) {
            front[bin] = -1;
            rear[bin] = -1;
        }

        // Distribute elements into bins based on the current digit
        for (current = first; current != -1; current = link[current]) {
            bin = digit(a[current].value[pos], pos);
            if (front[bin] == -1) {
                front[bin] = current; // First element in the bin
            } else {
                link[rear[bin]] = current; // Link to the current
            }
            rear[bin] = current; // Update the rear
        }

        // Rebuild the linked list
        first = -1;
        for (bin = 0; bin < r; bin++) {
            if (front[bin] != -1) {
                if (first == -1) {
                    first = front[bin]; // Set the first element
                } else {
                    link[last] = front[bin]; // Link the last of the previous to the current
                }
                last = rear[bin];
            }
        }
        link[last] = -1; // Terminate the list
    }

    return first; // Return the head of the sorted list
}

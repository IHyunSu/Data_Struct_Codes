#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NUMBERS 100
#define DIGITS 2
#define RADIX 10

typedef struct {
    int value;
} element;

int digit(int number, int d, int r);
int radixSort(element a[], int link[], int d, int r, int n);
void printArrays(element a[], int link[], int n);

int main() {
    FILE* file = fopen("in.txt", "r");
    if (!file) {
        fprintf(stderr, "Error opening file.\n");
        return EXIT_FAILURE;
    }

    element a[MAX_NUMBERS];
    int link[MAX_NUMBERS + 1];
    int n = 0;

    while (fscanf(file, "%d", &a[n].value) == 1 && n < MAX_NUMBERS) {
        n++;
    }
    fclose(file);

    radixSort(a, link, DIGITS, RADIX, n);


    printf("a 배열: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i].value);
    }
    printf("\n");

    return 0;
}

int digit(int number, int d, int r) {
    return (number / (int)pow(10, d)) % r;
}

int radixSort(element a[], int link[], int d, int r, int n) {
    int front[r], rear[r];
    int i, bin, current, first, last;
    first = 1;

    for (i = 1; i < n; i++) link[i] = i + 1;
    link[n] = 0;

    for (i = d - 1; i >= 0; i--) {
        for (bin = 0; bin < r; bin++) {
            front[bin] = 0;
            rear[bin] = 0;
        }

        for (current = first; current; current = link[current]) {
            bin = digit(a[current].value, i, r);
            if (front[bin] == 0) {
                front[bin] = current;
            } else {
                link[rear[bin]] = current;
            }
            rear[bin] = current;
        }

        for (bin = 0; !front[bin]; bin++);
        first = front[bin];
        last = rear[bin];

        for (bin++; bin < r; bin++) {
            if (front[bin]) {
                link[last] = front[bin];
                last = rear[bin];
            }
        }
        link[last] = 0;
        
        if (i == 0) { // 1의 자리 정렬 후 배열 출력
            printArrays(a, link, n);
        }
    }
    return first;
}

void printArrays(element a[], int link[], int n) {
    printf("정렬된 배열: ");
    for (int i = 1; i <= n; i++) {
        printf("%d ", a[i].value);
    }
    printf("\nLink: ");
    for (int i = 1; i <= n; i++) {
        printf("%d ", link[i]);
    }
    printf("\n\n");
}

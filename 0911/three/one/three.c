#include <stdio.h>
#include <stdlib.h>

int *mallocArray (int n);
void inputArray (int *arr, int n);
void selectionArray (int *arr, int n);
void printArray (int *arr, int n);
void freeArray (int *arr);

int main () {
    int *arr;
    int n;
    FILE *file;
    if ((file = fopen("f3.txt", "r")) == NULL) {
        printf("can not open error");
        exit(1);
    }
    fscanf(file, "%d", &n);
    fclose(file);

    arr = mallocArray (n);
    if (arr == NULL) {
        fprintf(stderr, "string error!");
        exit(1);
    }
    inputArray (arr, n);
    selectionArray (arr, n);
    printArray (arr, n);
    freeArray (arr);
}

int *mallocArray (int n) {
    return (int*)malloc(sizeof(int) * n);
}

void inputArray (int *arr, int n) {
    FILE *file;
    if ((file = fopen("f3.txt", "r")) == NULL) {
        printf("can not open file");
        exit(1);
    }
    fscanf(file, "%*d");
    for (int i = 0; i < n; i++) {
        if ((fscanf(file, "%d", &arr[i])) != 1) {
            fprintf(stderr, "string error!");
            exit(1);
        }
    }
    fclose(file);
}

void selectionArray (int *arr, int n) {
    int min, tmp;
    for (int i = 0; i < n - 1; i++) {
        min = i;
        for (int j = i; j < n; j++) {
            if (arr[j] < arr[min]) min = j;
        }
        if (i != min) {
            tmp = arr[i];
            arr[i] = arr[min];
            arr[min] = tmp;
        }
    }
}

void printArray (int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}

void freeArray (int *arr) {
    free(arr);
}
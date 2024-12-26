#include <stdio.h>
#include <stdlib.h>

int *arrayMalloc(int n);
void inputArray(int *arr, int n);
void selectSort(int *arr, int n);
void printArray(int *arr, int n);
void freeArray(int *arr, int n);

int main () {
    int n;
    int *arr;
    FILE *file;
    if ((file = fopen("f3.txt", "r")) == NULL) {
        printf("can not open file");
        exit(1);
    }
    fscanf(file, "%d", &n);
    fclose(file);
    arr = arrayMalloc(n);
    inputArray(arr, n);
    selectSort(arr, n);
    printArray(arr, n);
    freeArray(arr, n);
}

int *arrayMalloc(int n) {
    return (int *)malloc(sizeof(int) * n);
}

void inputArray(int *arr, int n) {
    FILE *file;
    if ((file = fopen("f3.txt", "r")) == NULL) {
        printf("can not open file");
        exit(1);
    }
    fscanf(file,"%*d");
    for (int i = 0; i < n; i++) {
        if ((fscanf(file, "%d", &arr[i])) != 1) {
            printf("string input error");
            exit(1);
        }
    }
    fclose(file);
}

void selectSort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

void printArray(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}

void freeArray(int *arr, int n) {
    free(arr);
}
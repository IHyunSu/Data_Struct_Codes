#include <stdio.h>
#include <stdlib.h>

int *mallocArray (int n);
void inputArray (int *arr, int n, char *filename);
void selectionArray (int *arr, int n);
int binarySearch(int *arr, int searchnum, int left, int right);
void freeArray (int *arr);

int main () {
    int *arr;
    int n;
    char filename[20];
    scanf("%s", filename);
    FILE *file;
    if ((file = fopen(filename, "r")) == NULL) {
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
    inputArray (arr, n, filename);
    selectionArray (arr, n);
    int searchnum, left = 0, right = n - 1, findIndex;
    scanf("%d", &searchnum);
    findIndex = binarySearch(arr, searchnum, left, right);
    printf("S(%d)", findIndex);
    freeArray (arr);
}

int *mallocArray (int n) {
    return (int*)malloc(sizeof(int) * n);
}

void inputArray (int *arr, int n, char *filename) {
    FILE *file;
    if ((file = fopen(filename, "r")) == NULL) {
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

int binarySearch(int *arr, int searchnum, int left, int right) {
    while (left <= right) {
        int mid = (left + (right - left)) / 2;

        if (arr[mid] > searchnum)
            right = mid - 1;
        else if (arr[mid] < searchnum)
            left = mid + 1;
        else
            return mid;
    }
    return -1;
}

void freeArray (int *arr) {
    free(arr);
}
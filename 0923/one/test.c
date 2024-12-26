#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sequentialSearch(char arr[][4], int n, char target[]);
int iterativeBinarySearch(char arr[][4], int n, char target[]);
int recursiveBinarySearch(char arr[][4], int left, int right, char target[]);

int main() {
    char arr[100][4];
    FILE *file;
    int n = 0;

    if ((file = fopen("f1.txt", "r")) == NULL) {
        printf("can not open file");
        exit(1);
    }

    while (fscanf(file, "%3s", arr[n]) == 1) {
        n++;
    }
    fclose(file);

    char target[10];
    scanf("%s", target);

    int res1 = sequentialSearch(arr, n, target);
    printf("Sequential search result: %s\n", res1 == 1 ? "S" : "F");

    qsort(arr, n, sizeof(arr[0]), (int (*)(const void*, const void*)) strcmp);

    int res2 = iterativeBinarySearch(arr, n, target);
    printf("Iterative binary search result: %s\n", res2 == 1 ? "S" : "F");

    int res3 = recursiveBinarySearch(arr, 0, n - 1, target);
    printf("Recursive binary search result: %s\n", res3 == 1 ? "S" : "F");

    return 0;
}

int sequentialSearch(char arr[][4], int n, char target[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i], target) == 0) {
            return 1;
        }
    }
    return 0;
}

int iterativeBinarySearch(char arr[][4], int n, char target[]) {
    int low = 0;
    int high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (strcmp(arr[mid], target) == 0) return 1;
        else if (strcmp(arr[mid], target) < 0) low = mid + 1;
        else high = mid - 1;
    }
    return 0;
}

int recursiveBinarySearch(char arr[][4], int left, int right, char target[]) {
    if (left > right) {
        return 0;
    }
    int mid = (left + right) / 2;
    if (strcmp(arr[mid], target) == 0) return 1;
    else if (strcmp(arr[mid], target) > 0) return recursiveBinarySearch(arr, left, mid - 1, target);
    else return recursiveBinarySearch(arr, mid + 1, right, target);
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int sequentialSearch(char arr[][4], int n, char target[]);
int iterativeBinarySearch(char arr[][4], int n, char target[]);
int recursiveBinarySearch(char arr[][4], int left, int right, char target[]);

int main () {
    char arr[100][4];
    char target[10];
    scanf("%s", target);

    int n = 0;
    FILE *file;
    if ((file = fopen("f1.txt", "r")) == NULL) {
        printf("can not open file");
        exit(1);
    }

    while ((fscanf(file, "%s", target[n])) == 1) {
        n++;
    }
    fclose(file);

    int res1 = sequentialSearch(arr, n, target);
    printf("Sequential search result: %s", res1 == 1 ? "S" : "F");

    qsort(arr, n, arr[0], ((int(*)(const void*, const void*)) strcmp));

    int res2 = iterativeBinarySearch(arr, n, target);
    printf("Iterative binary search result: %s", res2 == 1 ? "S" : "F");
    
    int left = 0;
    int right = n - 1;
    int res3 = recursiveBinarySearch(arr, left, right, target);
    printf("Recursive binary search result: S  %s", res3 == 1 ? "S" : "F");

}

int sequentialSearch(char arr[][4], int n, char target[]) {

}

int iterativeBinarySearch(char arr[][4], int n, char target[]) {

}

int recursiveBinarySearch(char arr[][4], int left, int right, char target[]) {

}
#include <stdio.h>
#include <stdlib.h>

int *listMalloc(int n);
void inputList(int *list, int n, char *fileName);
void selectSort(int *list, int n);
int binarySearch(int *list, int n, int target);
void printList(int *list, int n);
void freeList(int *list, int n);

int main () {
    int *list;
    int n;
    char fileName[10];
    scanf("%s", fileName);
    FILE *file;
    if ((file = fopen(fileName, "r")) == NULL) {
        printf("can not open file");
        exit(1);
    }
    fscanf(file, "%d", &n);
    fclose(file);
    list = listMalloc(n);
    if (list == NULL) {
        fprintf(stderr, "String malloc error!");
        exit(1);
    }
    inputList(list, n, fileName);
    selectSort(list, n);
    int target;
    scanf("%d", &target);
    int index = binarySearch(list, n, target);
    if (index != -1) {
        printf("S (%d)", index);
    }
    else {
        printf("F (%d)", index);
    }
    printf("\n정렬된 배열 : \n");
    printList(list, n);
    freeList(list, n);
    return 0;
}

int *listMalloc(int n) {
    return (int *)malloc(sizeof(int) * n);
}

void inputList(int *list, int n, char *fileName) {
    FILE *file;
    if ((file = fopen(fileName, "r")) == NULL) {
        printf("can not open file");
        exit(1);
    }
    fscanf(file, "%*d");
    for (int i = 0; i < n; i++) {
        if ((fscanf(file, "%d", &list[i])) != 1) {
            fprintf(stderr, "string error!");
            exit(1);
        }
    }
    fclose(file);
}

void selectSort(int *list, int n) {
    int min, tmp;
    for (int i = 0; i < n - 1; i++) {
        min = i;
        for (int j = i + 1; j < n; j++) {
            if (list[j] < list[min]) {
                min = j;
            }
        }
        if (i != min) {
            tmp = list[i];
            list[i] = list[min];
            list[min] = tmp;
        }
    }
}

int binarySearch(int *list, int n, int target) {
    int left = 0;
    int right = n - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (list[mid] < target)
            left = mid + 1;
        else if (list[mid] > target)
            right = mid - 1;
        else
            return mid;
    }
    return -1;
}

void printList(int *list, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
}

void freeList(int *list, int n) {
    free(list);
}

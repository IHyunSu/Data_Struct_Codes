#include <stdio.h>
#include <stdlib.h>

int *listMalloc(int n);
void inputList (int *list, int n, char *filename);
void selectSort(int *list, int n);
int binsearch(int *list, int searchnum, int left, int right);
void freeList (int *list);

int main () {
    int n;
    int *list;
    char filename[10];
    scanf("%s", filename);
    int searchnum, left, right;
    FILE *file;
    if ((file = fopen(filename, "r")) == NULL) {
        printf("can not open file");
        exit(1);
    }

    fscanf(file, "%d", &n);
    fclose(file);

    list = listMalloc(n);
    if (list == NULL) {
        printf("string error");
        exit(1);
    }

    inputList(list, n, filename);

    selectSort(list, n);
    scanf("%d", &searchnum);
    left = 0;
    right = n - 1;
    int index = binsearch(list, searchnum, left, right);
    if (index != -1) {
        printf("S (%d)", index);
    }
    else {
        printf("F (%d)", index);
    }
    freeList(list);
    return 0;
}

int *listMalloc(int n) {
    return (int *) malloc (sizeof(int) * n);
}

void inputList(int *list, int n, char *filename) {
    FILE *file;
    if ((file = fopen(filename, "r")) == NULL) {
        printf("can not open file");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        if ((fscanf(file, "%d", &list[i])) != 1) {
            printf("string error");
            exit(1);
        }
    }
    fclose(file);
}

void selectSort(int *list, int n) {
    int minIndex, tmp;
    for (int i = 0; i < n - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (list[j] < list[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            tmp = list[i];
            list[i] = list[minIndex];
            list[minIndex] = tmp;
        }
    }
}

int binsearch(int *list, int searchnum, int left, int right) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (list[mid] == searchnum) {
            return mid;
        }
        if (list[mid] < searchnum) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void freeList (int *list) {
    free(list);
}
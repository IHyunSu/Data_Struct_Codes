#include <stdio.h>
#include <stdlib.h>

int *listMalloc (int n);
void inputlist (int *list, int n, char *fileName);
void selectionSort (int *list, int n);
void printList (int *list, int n);
void freelist (int *list);

int main () {
    int *list;
    int n;
    char fileName[10];
    scanf("%s", fileName);
    FILE * file;
    if ((file = fopen(fileName, "r")) == NULL) {
        printf("can not open file");
        exit(1);
    }
    fscanf(file, "%d", &n);
    fclose(file);

    list = listMalloc(n);
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    inputlist (list, n, fileName);
    selectionSort(list, n);
    printList(list, n);
    freelist(list);

    return 0;
}

int *listMalloc (int n) {
    return (int *)malloc(sizeof(int) * n);
}

void inputlist (int *list, int n, char *fileName) {
    FILE *file;
    if ((file = fopen(fileName, "r")) == NULL) {
        printf("can not open file");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        if ((fscanf(file, "%d", &list[i])) != 1) {
            fprintf(stderr, "string error!");
            exit(1);
        } 
    }
    fclose(file);
}

void selectionSort (int *list, int n) {
    int smallIndex, tmp;
    for (int i = 0; i < n - 1; i++) {
        smallIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (list[j] < list[smallIndex]) {
                smallIndex = j;
            }
        }
        if (smallIndex != i) {
            tmp = list[i];
            list[i] = list[smallIndex];
            list[smallIndex] = tmp;
        }
    }
}

void printList (int *list, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
}

void freelist (int *list) {
    free(list);
}
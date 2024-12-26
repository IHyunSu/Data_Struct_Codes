#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC(p,s) \
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory"); \
        exit(EXIT_FAILURE); \
    }

void insertTree (char *tree, int n, char fileName[]);
void childCount (char *tree, int *n1, int *n2, int *n0, int n);

int main () {
    char *tree1, *tree2;
    int n1 = 0, n2 = 0, n0 = 0;
    FILE *file1;
    if ((file1 = fopen("f1.txt", "r")) == NULL) {
        printf("can not open file1");
        exit(1);
    }
    char c, n = 0;
    while (fscanf(file1, "%c ", &c) == 1) {
        n++;
    }
    fclose(file1);
    MALLOC(tree1, n);
    insertTree(tree1, n, "f1.txt");
    printf("f1.txt:\n");
    for (int i = 0; i < n; i++) {
        printf("%c", tree1[i]);
    }
    printf("\n");
    childCount(tree1, &n1, &n2, &n0, n);
    printf("n1 = %d\nn2 = %d\nn0 = %d\n", n1, n2, n0);

    FILE *file2;
    if ((file2 = fopen("f2.txt", "r")) == NULL) {
        printf("can not open file2");
        exit(1);
    }
    n = 0;
    while (fscanf(file2, "%c ", &c) == 1) {
        n++;
    }
    fclose(file2);
    MALLOC(tree2, n);
    insertTree(tree2, n, "f2.txt");
    printf("f2.txt:\n");
    for (int i = 0; i < n; i++) {
        printf("%c", tree2[i]);
    }
    printf("\n");
    n1 = 0, n2 = 0, n0 = 0;
    childCount(tree2, &n1, &n2, &n0, n);
    printf("n1 = %d\nn2 = %d\nn0 = %d", n1, n2, n0);
}

void insertTree (char *tree, int n, char fileName[]) {
    FILE *file1;
    if ((file1 = fopen(fileName, "r")) == NULL) {
        printf("can not open file");
        exit(1);
    }
    char c;
    for (int i = 0; i < n; i++) {
        fscanf(file1, "%c ", &c);
        tree[i] = c;
    }
    fclose(file1);
}

void childCount (char *tree, int *n1, int *n2, int *n0, int n) {
    int left, right, childCount = 0;
    for (int i = 0; i < n; i++) {
        if (tree[i] != '\0') {
            left = 2*i+1;
            right = 2*i+2;
            childCount = 0;

            if (left <= n && tree[left] != '\0') childCount++;
            if (right <= n && tree[right] != '\0') childCount++;
            
            if (childCount == 0) (*n0)++;
            else if (childCount == 1) (*n1)++;
            else if (childCount == 2) (*n2)++;
        }
    }
}
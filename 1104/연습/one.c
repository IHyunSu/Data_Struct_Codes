#include <stdio.h>

#define MAX_SIZE 20

void childCount(char tree[], int *n1, int *n2, int *n0);

int main () {
    char tree1[MAX_SIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    char tree2[MAX_SIZE] = {'A', 'B', '\0', 'C', '\0', '\0', '\0', 'D', '\0', '\0', '\0', 
    '\0', '\0', '\0', '\0', 'E'};

    int n1 = 0, n2 = 0, n0 = 0;
    childCount(tree1, &n1, &n2, &n0);
    printf("n1 = %d\nn2 = %d\nn0 = %d\n", n1, n2, n0);

    n1 = 0, n2 = 0, n0 = 0;
    childCount(tree2, &n1, &n2, &n0);
    printf("n1 = %d\nn2 = %d\nn0 = %d", n1, n2, n0);
}

void childCount(char tree[], int *n1, int *n2, int *n0) {
    int left, right, childCount;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (tree[i] != '\0') {
            left = 2*i+1;
            right = 2*i+2;
            childCount = 0;
            if (left <= MAX_SIZE && tree[left] != '\0') childCount++;
            if (right <= MAX_SIZE && tree[right] != '\0') childCount++;

            if (childCount == 0) (*n0)++;
            else if (childCount == 1) (*n1)++;
            else if (childCount == 2) (*n2)++;
        }
    }
}
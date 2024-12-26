#include <stdio.h>
#include <string.h>

#define MAX_SIZE 20

void countNodes(char tree[], int* n0, int* n1, int* n2) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (tree[i] != '\0') {
            int left = 2 * i + 1;   
            int right = 2 * i + 2;
            int childCount = 0;

            if (left < MAX_SIZE && tree[left] != '\0') {
                childCount++;
            }
            if (right < MAX_SIZE && tree[right] != '\0') {
                childCount++;
            }

            if (childCount == 0) {
                (*n0)++;
            } else if (childCount == 1) {
                (*n1)++;
            } else if (childCount == 2) {
                (*n2)++;
            }
        }
    }
}

int main() {
    char tree1[MAX_SIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};

    int n0 = 0, n1 = 0, n2 = 0;

    countNodes(tree1, &n0, &n1, &n2);

    printf("Tree 1:\nN1 = %d\nN2 = %d\nN0 = %d\n", n1, n2, n0);

    n0 = 0; n1 = 0; n2 = 0;
    char tree2[MAX_SIZE] = {'A', 'B', '\0', 'C', '\0', '\0', '\0', 'D', '\0', '\0', '\0', '\0', '\0', '\0', '\0', 'E'};
    countNodes(tree2, &n0, &n1, &n2);
    printf("Tree 2:\nN1 = %d\nN2 = %d\nN0 = %d\n", n1, n2, n0);

    return 0;
}

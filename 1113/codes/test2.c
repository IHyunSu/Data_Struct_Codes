#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;

typedef struct tree{
    element data;
    struct tree* leftChild;
    struct tree* rightChild;
} tree, *treePointer;

treePointer modifield(treePointer ptr, int k);
treePointer insert(treePointer ptr, int k);
treePointer delete(treePointer ptr, int k);
treePointer maxValueSerach(treePointer ptr);

int main () {
    FILE *file = fopen("in.txt", "r");

    treePointer root = NULL, item;

    int n, temp;
    fscanf(file, "%d", &n);

    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &temp);
        insert(&root, temp);
    }
    fclose(file);


}

treePointer modifield(treePointer ptr, int k) {
    while (ptr != NULL) {
        if (ptr->data.key == k) return ptr;
        if (ptr->data.key > k) ptr = ptr->leftChild;
        else ptr = ptr->rightChild;
    }
    return NULL; // 값을 못 찾을 시 NULL (비어있다는 것을 반환)
}

treePointer insert(treePointer ptr, int k) {

}

treePointer delete(treePointer ptr, int k) {

}

treePointer maxValueSerach(treePointer ptr) {

}
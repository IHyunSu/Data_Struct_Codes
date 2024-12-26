#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p, s)                              \
    if ((p = malloc(s)) == NULL)                  \
    {                                             \
        fprintf(stderr, "Insufficient Memory\n"); \
        exit(EXIT_FAILURE);                       \
    }

typedef struct
{
    int key;
} element;

typedef struct tree
{
    element data;
    struct tree *leftChild;
    struct tree *rightChild;
} tree, *treePointer;

treePointer modifiedSearch(treePointer node, int k);
void insert(treePointer *node, int k);
void inorderTraversal(treePointer node);
treePointer deleteNode(treePointer root, int key);
treePointer findMin(treePointer root);

int main()
{
    FILE *file = fopen("in.txt", "r");
    treePointer root = NULL;

    int n, k;
    fscanf(file, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        fscanf(file, "%d", &k);
        insert(&root, k);
    }

    fscanf(file, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &k);
        root = deleteNode(root, k);
    }
    fclose(file);

    inorderTraversal(root);

    return 0;
}

treePointer modifiedSearch(treePointer node, int k)
{
    while (node != NULL)
    {
        if (k == node->data.key)
        {
            return node;
        }
        if (k < node->data.key)
        {
            node = node->leftChild;
        }
        else
        {
            node = node->rightChild;
        }
    }
    return NULL;
}

void insert(treePointer *node, int k)
{
    treePointer ptr, temp = modifiedSearch(*node, k);

    if (temp == NULL)
    {
        MALLOC(ptr, sizeof(*ptr));
        ptr->data.key = k;
        ptr->leftChild = ptr->rightChild = NULL;

        if (*node == NULL) // Tree가 비어있다면 새로운 노드는 root가 된다.
        {
            *node = ptr;
        }
        else // Tree가 비어있지 않다면, 맞는 위치에 insert한다.
        {
            treePointer current = *node;
            treePointer parent = NULL;

            // 삽입을 위해 조상 노드를 찾는다.
            while (current != NULL)
            {
                parent = current;
                if (k < current->data.key)
                {
                    current = current->leftChild;
                }
                else
                {
                    current = current->rightChild;
                }
            }

            // 새 노드를 부모 노드의 왼쪽 또는 오른쪽 자식으로 삽입한다.
            if (k < parent->data.key)
            {
                parent->leftChild = ptr;
            }
            else
            {
                parent->rightChild = ptr;
            }
        }
    }
}

/* 
7 5 4 1 6 3 9 8
3 9 2 6
*/
/*
10 2 4 6 8 10 12 14 16 18 20 
5 1 2 3 4 5
*/

treePointer findMin(treePointer root) {
    while (root->leftChild != NULL) {
        root = root->leftChild;
    }
    return root;
}

treePointer deleteNode(treePointer root, int key)
{
    if (root == NULL)
    {
        printf("E "); // 노드를 찾지 못한 경우
        return root; 
    }

    // 키가 작으면 왼쪽 서브트리로 이동
    if (key < root->data.key)
    {
        root->leftChild = deleteNode(root->leftChild, key);
    }
    // 키가 크면 오른쪽 서브트리로 이동
    else if (key > root->data.key)
    {
        root->rightChild = deleteNode(root->rightChild, key);
    }
    // 키가 같으면 삭제
    else
    { 
        printf("S "); // 노드를 성공적으로 삭제할 경우
        if (root->leftChild != NULL && root->rightChild != NULL) {
            treePointer temp = findMin(root->rightChild);
            root->data.key = temp->data.key;
            root->rightChild = deleteNode(root->rightChild, temp->data.key);
        }
        else {
            treePointer temp = (root->leftChild != NULL) ? root->leftChild : root->rightChild;
            free(root);
            return temp;
        }
    }
    return root;
}


void inorderTraversal(treePointer node)
{
    if (node)
    {
        inorderTraversal(node->leftChild);  // 왼쪽 자식 순회
        printf("%d ", node->data.key);      // key
        inorderTraversal(node->rightChild); // 오른쪽 자식 순회
    }
}

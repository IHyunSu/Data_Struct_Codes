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
void findMax(treePointer root);

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
    fclose(file);

    inorderTraversal(root);
    printf("\n");
    findMax(root);

    return 0;
}

// node가 있는지 없는지 찾는 함수. 예제코드 5.16
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

            // 삼입을 위해 조상 노드를 찾는다.
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

// 중위 순회 (트리 내용 출력)
void inorderTraversal(treePointer node)
{
    if (node != NULL)
    {
        inorderTraversal(node->leftChild);  // 왼쪽 자식 순회
        printf("%d ", node->data.key);      // key
        inorderTraversal(node->rightChild); // 오른쪽 자식 순회
    }
}

// max값 찾기
void findMax(treePointer root)
{
    int max = root->data.key;
    while (1)
    {
        if (root->rightChild == NULL)
        {
            max = root->data.key;
            break;
        }
        root = root->rightChild;
    }
    printf("%d", max);
}
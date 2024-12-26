#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int countNodes(Node* root) {
    if (root == NULL) {
        return 0; // 노드가 없으면 0 반환
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main() {
    Node* root = createNode('A');
    root->left = createNode('B');
    root->right = createNode('C'); 
    root->left->left = createNode('D');
    root->left->right = createNode('E');
    root->right->left = createNode('F');
    root->right->right = createNode('G');
    root->left->left->left = createNode('H');
    root->left->left->right = createNode('I');

    // 노드 개수 계산
    int totalNodes = countNodes(root);
    
    printf("nodes = %d\n", totalNodes);

    return 0;
}

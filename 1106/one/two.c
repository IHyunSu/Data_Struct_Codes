#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} node;

node* newNode(int data);
void countLeafNode(node* ptr);
int n0Count = 0;

int main () {
    node* root = newNode(4);
    root->left = newNode(3);
    root->right = newNode(6);
    root->left->left = newNode(2);
    root->left->right = newNode(5);
    root->right->right = newNode(8);

    countLeafNode(root);
    printf("%d", n0Count);
}

node* newNode(int data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void countLeafNode(node* ptr) {
    if (ptr) {
        countLeafNode(ptr->left);
        countLeafNode(ptr->right);
        if (ptr->right == NULL && ptr->left == NULL) n0Count++;
    }
}

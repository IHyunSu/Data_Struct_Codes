#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} node;

void inorder(node* ptr);
node* newNode(int data);
node* copy(node* original);
int equal(node* first, node* second);

int main () {
    node* root = newNode(4);
    root->left = newNode(3);
    root->right = newNode(6);
    root->left->left = newNode(2);
    root->left->right = newNode(5);
    root->right->right = newNode(8);

    printf("original inorder : ");
    inorder(root);

    node* root2 = copy(root);
    if (root2 == NULL) printf("copy error");
    else printf("\ncopy finished!\n");

    int success = equal(root, root2);
    if (success == 1) printf("equal test success!\n"); 
    else printf("equal test error");

    printf("copied inorder: ");
    inorder(root2);
}

node* newNode(int data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void inorder(node* ptr) {
    if (ptr) {
        inorder(ptr->left);
        printf("%d ", ptr->data);
        inorder(ptr->right);
    }
}

node* copy(node* original) {
    node* temp;
    if (original) {
        temp = (node*)malloc(sizeof(node));
        temp->left = copy(original->left);
        temp->right = copy(original->right);
        temp->data = original->data;
        return temp;
    }
    return NULL;
}

int equal(node* first, node* second) {
    return ((!first && !second) || 
    (first && second &&
    (first->data == second->data) &&
    equal(first->left, second->left) &&
    equal(first->right, second->right)
    ));
}
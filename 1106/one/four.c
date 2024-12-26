#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 20

typedef struct node {
    char data;
    struct node* left;
    struct node* right;
} node;

node* stack[MAX_STACK_SIZE];
int top = -1;

node* createNode(char data);
void push(node* node);
node* pop();
void iterInorder(node* node);

int main () {
    node* root = createNode('+');
    root->left = createNode('*');
    root->right = createNode('E');
    root->left->left = createNode('*');
    root->left->right = createNode('D');
    root->left->left->left = createNode('/');
    root->left->left->right = createNode('C');
    root->left->left->left->left = createNode('A');
    root->left->left->left->right = createNode('B');

    printf("LVR : ");
    iterInorder(root);
}

node* createNode(char data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void push(node* node) {
    if (node == NULL) {
        return;
    }
    if (top < MAX_STACK_SIZE -1) {
        stack[++top] = node;
    } else {
        printf("stack full!");
    }
}

node* pop() {
    if (top == -1) {
        return NULL;
    }
    return stack[top--];
}

void iterInorder(node* node) {
    for (;;) {
        for (; node; node = node->left)
            push(node);
        node = pop();
        if (!node) break;
        printf("%c ", node->data);
        node = node->right;
    }
}
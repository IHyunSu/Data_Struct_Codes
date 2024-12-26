#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 20

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} node;

int front = 0, rear = -1;
node* queue[MAX_QUEUE_SIZE];

node* newNode(int data);
void addq(node* ptr);
node* deleteq();
void levelOrder(node* ptr);

int main () {
    node* root = newNode(4);
    root->left = newNode(3);
    root->right = newNode(6);
    root->left->left = newNode(2);
    root->left->right = newNode(5);
    root->right->right = newNode(8);

    levelOrder(root);
    return 0;
}

node* newNode(int data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void addq(node* ptr) {
    if (ptr == NULL) {
        return;
    }
    if (rear < MAX_QUEUE_SIZE - 1) { 
        queue[++rear] = ptr;
    } else {
        printf("Queue is full\n");
    }
}

node* deleteq() {
    if (front > rear) {
        return NULL;
    }
    return queue[front++];
}

void levelOrder(node* ptr) {
    if (!ptr) return;
    addq(ptr);
    while (1) {
        ptr = deleteq();
        if (ptr) {
            printf("%d ", ptr->data);
            if (ptr->left) addq(ptr->left);
            if (ptr->right) addq(ptr->right);
        } else {
            break;
        }
    }
    printf("\n");
}

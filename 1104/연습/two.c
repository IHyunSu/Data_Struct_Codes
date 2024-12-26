#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p,s) \
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory"); \
        exit(EXIT_FAILURE); \
    }

typedef struct node {
    char data;
    struct node* leftChilde;
    struct node* rightChilde;
} node;

node* createNode(char c);
int nodeCount(node *root);

int main () {
    node* root = createNode('A');
    root->leftChilde = createNode('B');
    root->rightChilde = createNode('C');
    root->leftChilde->leftChilde = createNode('D');
    root->leftChilde->rightChilde = createNode('E');
    root->rightChilde->leftChilde = createNode('F');
    root->rightChilde->rightChilde = createNode('G');
    root->leftChilde->leftChilde->leftChilde = createNode('H');
    root->leftChilde->leftChilde->rightChilde = createNode('I');

    int result = nodeCount(root);
    printf("nodes = %d", result);
}

node* createNode(char c) {
    node* temp;
    MALLOC(temp, sizeof(node));
    temp->data = c;
    temp->leftChilde = NULL;
    temp->rightChilde = NULL;
    return temp;
}

int nodeCount(node *root) {
    if (root == NULL) {
        return 0;
    }

    
}
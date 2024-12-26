#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p,s)\
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory"); \
        exit(EXIT_FAILURE); \
    }

typedef struct polyList *polyPointer;
typedef struct polyList {
    int coefficient;
    int exponent;
    polyPointer link;
} polyList;

polyPointer first = NULL;
polyPointer a = NULL;
polyPointer b = NULL;
polyPointer c = NULL;

void insert(polyPointer *f, int dataA, int dataB);
polyPointer padd(polyPointer a, polyPointer b);
void attach(float coefficient, int exponent, polyPointer *ptr);
void printPoly(polyPointer c);

int main () {
    FILE *file21;
    if ((file21 = fopen("in21.txt", "r")) == NULL) {
        printf("can not open file21");
        exit(1);
    }
    FILE *file22;
    if ((file22 = fopen("in22.txt", "r")) == NULL) {
        printf("can not open file22");
    }

    int dataA, dataB, dataC, dataD;
    while(fscanf(file21, "%d %d", &dataA, &dataB) == 2) {
        insert(&a, dataA, dataB);
    }
    while(fscanf(file22, "%d %d", &dataC, &dataD) == 2) {
        insert(&b, dataC, dataD);
    }

    fclose(file21);
    fclose(file22);

    c = padd(a, b);

    printPoly(c);

    return 0;
}

void insert (polyPointer *f, int data1, int data2) {
    polyPointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->coefficient = data1;
    newNode->exponent = data2;

    if (first == NULL) {
        newNode->link = NULL;
        (*f) = newNode;
    } else {
        polyPointer current = *f;
        while (current->link != NULL) {
            current = current->link;
        }
        newNode->link = current->link;
        current->link = newNode;
    }
}

polyPointer padd(polyPointer a, polyPointer b) {
    polyPointer temp;
    MALLOC(temp, sizeof(*temp));
    if (first == NULL) {
        temp->link = NULL;
        first = temp;
    } else {
        while (a->link != NULL || b->link != NULL) {
            if (a->coefficient == b->coefficient) {
                temp->exponent = a->exponent + b->exponent;
                temp->coefficient = a->coefficient;
                temp = temp->link;
                a = a->link;
                b = b->link;
            }
            a = a->link;
        }
    }
    return temp;
}

void attach(float coefficient, int exponent, polyPointer *ptr) {
    
}

void printPoly(polyPointer c) {
    c = first;
    while (c->link!=NULL) {
        printf("%d %d ", c->exponent, c->coefficient);
        c = c->link;
    }
}



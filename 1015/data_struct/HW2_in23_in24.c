#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p,s) \
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory\n"); \
        exit(EXIT_FAILURE); \
    }

typedef struct polyList *polyPointer;
typedef struct polyList {
    int coefficient;
    int exponent;
    polyPointer link;
} polyList;

polyPointer a = NULL;
polyPointer b = NULL;
polyPointer c = NULL;

void insert(polyPointer *f, int coefficient, int exponent);
polyPointer padd(polyPointer a, polyPointer b);
void attach(int coefficient, int exponent, polyPointer *ptr);
void printPoly(polyPointer c);

int main() {
    FILE *file21;
    if ((file21 = fopen("in23.txt", "r")) == NULL) {
        printf("Cannot open file21\n");
        exit(1);
    }

    FILE *file22;
    if ((file22 = fopen("in24.txt", "r")) == NULL) {
        printf("Cannot open file22\n");
        exit(1);
    }

    int coefficient, exponent;
    while (fscanf(file21, "%d %d", &coefficient, &exponent) == 2) {
        insert(&a, coefficient, exponent);
    }
    while (fscanf(file22, "%d %d", &coefficient, &exponent) == 2) {
        insert(&b, coefficient, exponent);
    }

    fclose(file21);
    fclose(file22);

    c = padd(a, b);

    printPoly(c);

    return 0;
}

void insert(polyPointer *f, int coefficient, int exponent) {
    polyPointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->link = NULL;

    if (*f == NULL) {
        *f = newNode;
    } else {
        polyPointer current = *f;
        while (current->link != NULL) {
            current = current->link;
        }
        current->link = newNode;
    }
}

polyPointer padd(polyPointer a, polyPointer b) {
    polyPointer result = NULL;

    while (a != NULL && b != NULL) {
        if (a->exponent > b->exponent) {
            attach(a->coefficient, a->exponent, &result);
            a = a->link;
        } else if (a->exponent < b->exponent) {
            attach(b->coefficient, b->exponent, &result);
            b = b->link;
        } else {
            int sumCoeff = a->coefficient + b->coefficient;
            if (sumCoeff != 0) {
                attach(sumCoeff, a->exponent, &result);
            }
            a = a->link;
            b = b->link;
        }
    }

    while (a != NULL) {
        attach(a->coefficient, a->exponent, &result);
        a = a->link;
    }

    while (b != NULL) {
        attach(b->coefficient, b->exponent, &result);
        b = b->link;
    }

    return result;
}

void attach(int coefficient, int exponent, polyPointer *ptr) {
    polyPointer newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->link = NULL;

    if (*ptr == NULL) {
        *ptr = newNode;
    } else {
        polyPointer current = *ptr;
        while (current->link != NULL) {
            current = current->link;
        }
        current->link = newNode;
    }
}

void printPoly(polyPointer c) {
    if (c == NULL) {
        printf("0\n");
        return;
    }
    while (c != NULL) {
        printf("%d %d ", c->coefficient, c->exponent);
        c = c->link;
    }
    printf("\n");
}

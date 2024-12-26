#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC(p,s) \
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory"); \
        exit(EXIT_FAILURE); \
    }

#define IS_EMPTY(first)(!first);

typedef struct listNode *listPointer;
typedef struct listNode {
    int data;
    listPointer link;
};

int list[100];
listPointer first = NULL;

void insert(listPointer *first, int data);
void printList(listPointer first); 

int main () {
    FILE *file;
    if ((file = fopen("in1.txt", "r")) == NULL) {
        printf("can not open file");
        exit(1);
    }
    int i = 0;
    while ((fscanf(file, "%d", &list[i])) == 1) {
        i++;
    }
    void insert(listPointer *first, int data);

}

void insert(listPointer *head, int data) {
    listPointer temp;
    int len = strlen(list);
    MALLOC(temp, sizeof(*temp));
    
    for (int i = 0; i < len; i++) {
        temp[i].data = list[i];
        temp[i].link = temp[i].data;
    }

    int tmp;

    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (temp[i].data > temp[j].data) {
                tmp = temp[i].link;
                temp[i].link = temp[j].link;
                temp[j].link = tmp;
            }
        }
    }
}
#include <stdlib.h>

#define MAX_SIZE 50
#define MALLOC(p,s) \
    if ((p = malloc(s)) == NULL) { \
        fprintf(stderr, "Insufficient Memory\n"); \
        exit(EXIT_FAILURE); \
    }

typedef enum {head, entry} tagfield;

typedef struct matrixNode *matrixPointer;
typedef struct {
    int row;
    int col;
    int value;
} entryNode;

typedef struct matrixNode {
    matrixPointer down;
    matrixPointer right;
    tagfield tag;
    union {
        matrixPointer next;
        entryNode entry;
    } u;
} matrixNode;

matrixPointer hdnode[MAX_SIZE];

matrixPointer mread(void);
matrixPointer newNode();
void mwrite(matrixPointer node);
void merase(matrixPointer *node); 

int main () {
    matrixPointer *node;
    MALLOC(node, MAX_SIZE * sizeof(matrixPointer));
    while(1) {
        int data;
        printf("matrix 작업 선택 (1. 입력 2. 출력 3. 삭제 4. 종료): ");
        scanf("%d", &data);
        if (data == 1)
            node[0] = mread(); // 첫 번째 요소에 저장
        else if (data == 2) 
            mwrite(node[0]);
        else if (data == 3)
            merase(&node[0]);
        else if (data == 4)
            exit(0);
    }
}

matrixPointer newNode() {
    matrixPointer tem;
    MALLOC(tem, sizeof(*tem));
    return tem;
}

matrixPointer mread(void) {
    int numRows, numCols, numTerms, numHeads, i;
    int row, col, value, currentRow;
    matrixPointer temp, last, node;

    printf("행과 열의 크기 및 nonzero 항의 개수 입력: \n");
    scanf("%d%d%d", &numRows, &numCols, &numTerms);
    numHeads = (numCols > numRows) ? numCols : numRows;
    node = newNode(); 
    node->tag = entry;
    node->u.entry.row = numRows;
    node->u.entry.col = numCols;

    if (!numHeads) 
        node->right = node;
    else {
        for (i = 0; i < numHeads; i++) {
            temp = newNode();
            hdnode[i] = temp; 
            hdnode[i]->tag = head;
            hdnode[i]->right = temp; 
            hdnode[i]->u.next = temp;
        }
        currentRow = 0;
        last = hdnode[0];

        printf("행, 열, 값 입력: \n");
        for (i = 0; i < numTerms; i++) {
            scanf("%d%d%d", &row, &col, &value);
            if (row > currentRow) {
                last->right = hdnode[currentRow];
                currentRow = row; 
                last = hdnode[row];
            }
            MALLOC(temp, sizeof(*temp));
            temp->tag = entry; 
            temp->u.entry.row = row;
            temp->u.entry.col = col;
            temp->u.entry.value = value;
            last->right = temp;

            last = temp;

            hdnode[col]->u.next->down = temp; 
            hdnode[col]->u.next = temp;
        }
        last->right = hdnode[currentRow];

        for (i = 0; i < numCols; i++)
            hdnode[i]->u.next->down = hdnode[i];

        for (i = 0; i < numHeads - 1; i++)
            hdnode[i]->u.next = hdnode[i + 1];
        hdnode[numHeads - 1]->u.next = node;
        node->right = hdnode[0];
    }
    return node;
}

void mwrite (matrixPointer node) {
    int i;
    if (node == NULL) {
        printf("node가 비었습니다\n");
        return;
    }
    matrixPointer temp, head = node->right;
    printf("\n numRows = %d, numCols = %d \n", node->u.entry.row, node->u.entry.col);
    printf(" The matrix by row, column, and value: \n\n");
    for (i = 0; i < node->u.entry.row; i++) {
        for (temp = head->right; temp != head; temp = temp->right)
            printf("%5d%5d%5d \n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
        head = head->u.next;
    }
}

void merase (matrixPointer *node) {
    matrixPointer x, y, head = (*node)->right;
    int i;

    for (i = 0; i < (*node)->u.entry.row; i++) {
        y = head->right;
        while(y != head) {
            x = y; 
            y = y->right; 
            free(x);
        }
        x = head; 
        head = head->u.next; 
        free(x);
    }

    y = head;
    while (y != *node) {
        x = y; 
        y = y->u.next; 
        free(x);
    }
    free(*node); 
    *node = NULL;
}

#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101
#define MAX_COL 100

typedef struct {
    int row;
    int col;
    int val;
} term;

void readMatrix(const char *filename, term matrix[]);
void transpose(term a[], term b[]);
void writeMatrix(const char *filename, term matrix[]);
void printMatrix2D(term matrix[]);

int main() {
    term a[MAX_TERMS];
    term b[MAX_TERMS];

    readMatrix("a.txt", a);

    transpose(a, b);

    printf("Original Matrix (A):\n");
    printMatrix2D(a);
    printf("\nTransposed Matrix (B):\n");
    printMatrix2D(b);

    writeMatrix("b.txt", b);

    return 0;
}

void readMatrix(const char *filename, term matrix[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot open file %s\n", filename);
        exit(1);
    }

    int row, col, val; /*변수로 선언해서 값을 받음*/

    fscanf(file, "%d %d %d", &matrix[0].row, &matrix[0].col, &matrix[0].val); /* 첫번째만 따로 받는 이유? */
    /* row = 6행, col = 6열, value 개수 = 8개 */

    int num = matrix[0].val;
    for (int i = 1; i <= num; i++) {
        fscanf(file, "%d %d %d", &row, &col, &val);
        matrix[i].row = row;
        matrix[i].col = col;
        matrix[i].val = val;
    }

    fclose(file);
}

void transpose(term a[], term b[]) {
    int rowTerms[MAX_COL] = {0}, startingPos[MAX_COL] = {0};

    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].val = a[0].val;

    int numTerms = a[0].val;
    int numCols = a[0].col;

    if (numTerms > 0) {
        for (int i = 1; i <= numTerms; i++) {
            rowTerms[a[i].col]++;
        }

        startingPos[0] = 1;
        for (int i = 1; i < numCols; i++) {
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
        }

        for (int i = 1; i <= numTerms; i++) {
            int j = startingPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].val = a[i].val;
        }
    }
}

void writeMatrix(const char *filename, term matrix[]) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Cannot open file %s\n", filename);
        exit(1);
    }

    for (int i = 0; i <= matrix[0].val; i++) {
        fprintf(file, "%d %d %d\n", matrix[i].row, matrix[i].col, matrix[i].val);
    }

    fclose(file);
}

void printMatrix2D(term matrix[]) {
    int rows = matrix[0].row;
    int cols = matrix[0].col;
    int data[MAX_COL][MAX_COL] = {0};

    for (int i = 1; i <= matrix[0].val; i++) {
        data[matrix[i].row][matrix[i].col] = matrix[i].val;
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            printf("%3d ", data[r][c]);
        }
        printf("\n");
    }
}

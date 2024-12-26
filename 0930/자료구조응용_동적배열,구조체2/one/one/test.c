#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101

typedef struct {
    int row;
    int col;
    int value;
} term;

term a[MAX_TERMS];

int readMatrix(int *rows, int *cols, int *nonZeroCount, int arra[100][100]);
void printMatrix(int nonZeroCount);
void search(int find_value, int nonZeroCount);

int main() {
    int rows, cols, nonZeroCount = 0;
    int arra[100][100];

    readMatrix(&rows, &cols, &nonZeroCount, arra);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arra[i][j] != 0) {
                a[nonZeroCount].row = i;
                a[nonZeroCount].col = j;
                a[nonZeroCount].value = arra[i][j];
                nonZeroCount++;
            }
        }
    }

    printf("%d %d %d\n", rows, cols, nonZeroCount);
    printMatrix(nonZeroCount);

	int find_value;
	scanf("%d", &find_value);
	search(find_value, nonZeroCount);

    return 0;
}

int readMatrix(int *rows, int *cols, int *nonZeroCount, int arra[100][100]) {
    FILE *file;

    if ((file = fopen("f2.txt", "r")) == NULL) {
        printf("can not open file\n");
        exit(1);
    }

    fscanf(file, "%d %d", rows, cols);

    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            fscanf(file, "%d", &arra[i][j]);
        }
    }
    fclose(file);
    return 0;
}

void printMatrix(int nonZeroCount) {
    for (int i = 0; i < nonZeroCount; i++) {
        printf("%d %d %d\n", a[i].row, a[i].col, a[i].value);
    }
}

void search(int find_value, int nonZeroCount) {
	for (int i = 0; i < nonZeroCount; i++) {
		if (a[i].value == find_value) {
			printf("row: %d\ncolumn: %d", a[i].row, a[i].col);
		}
	}
}

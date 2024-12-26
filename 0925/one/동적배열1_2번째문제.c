#include <stdio.h>
#include <stdlib.h>

int** make2dArray(int rows, int cols);
void init2dArray(int** array, int rows, int cols);
int** add2dArray(int** A, int** B, int rows, int cols);
void display2dArray(int** array, int rows, int cols);
void free2dArray(int** array, int rows);

int main () {
    int rows, cols;
    int **A, **B;

    printf("Enter row, column size: ");
    scanf("%d %d", &rows, &cols);

    A = make2dArray(rows, cols);
    B = make2dArray(rows, cols);

    printf("Input A matrix:\n");
    init2dArray(A, rows, cols);
    printf("Input B matrix:\n");
    init2dArray(B, rows, cols);

    int **sum = add2dArray(A, B, rows, cols);
    printf("Sum of matrices:\n");
    display2dArray(sum, rows, cols);

    free2dArray(A, rows);
    free2dArray(B, rows);
    free2dArray(sum, rows);

    return 0;
}

int** make2dArray(int rows, int cols) {
    int **arr = (int **) malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; i++) {
        arr[i] = (int *) malloc(sizeof(int) * cols);
    }
    return arr;
}

void init2dArray(int** array, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &array[i][j]);
        }
    }
}

int** add2dArray(int** A, int** B, int rows, int cols) {
    int **sum = make2dArray(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum[i][j] = A[i][j] + B[i][j];
        }
    }
    return sum;
}

void display2dArray(int** array, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}

void free2dArray(int** array, int rows) {
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}

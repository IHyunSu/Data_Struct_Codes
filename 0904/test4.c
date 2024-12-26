#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int **build2DArray (int rows, int cols);
void arrStoredInput (int **arr, int rows, int cols);
double standardDeviation (int **arr, int rows, int cols);

int main () {
    int rows, cols;
    int **arr;
    scanf("%d %d", &rows, &cols);
    arr = build2DArray (rows, cols);
    arrStoredInput (arr, rows, cols);
    double result = standardDeviation (arr, rows, cols);
    for (int i = 0; i < rows; i ++) {
        free(arr[i]);
    }
    free(arr);
    printf("표준편차 = %.2f", result);

}

int **build2DArray (int rows, int cols) {
    int ** arr = (int **) malloc (sizeof(int *) * rows);
    for (int i = 0; i < rows; i++) {
        arr[i] = (int *) malloc (sizeof(int) * cols);
    }
    return arr;
}

void arrStoredInput (int **arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
}

double standardDeviation (int **arr, int rows, int cols) {
    int n = rows * cols;
    double sum = 0.0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum += arr[i][j];
        }
    }
    double mean = sum / n;

    double variance = 0.0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            variance += pow(arr[i][j] - mean, 2);
        }
    }
    variance /= n;
    double stddev = sqrt(variance);
    return stddev;
}
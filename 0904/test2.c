#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int ** build2DArray(int rows, int cols);
void input (int** arr, int rows, int cols);
double calculateStandardDeviation(int **arr, int rows, int cols);

int main () {
    int **arr;
    int rows, cols;

    scanf("%d %d", &rows, &cols);

    FILE * file;
    if ((file = (fopen("f3.txt", "a"))) == NULL) {
        printf("파일을 열 수 없습니다.");
        exit(1);
    }

    fprintf(file, "%d %d\n", rows, cols);
    fclose(file);

    arr = build2DArray(rows, cols);
    input (arr, rows, cols);

    double result = calculateStandardDeviation(arr, rows, cols);
    printf("표준편차 = %.2f", result);
}

int ** build2DArray(int rows, int cols) {
    int ** arr = (int **) malloc (sizeof(int *) * rows);
    for (int i = 0; i < rows; i++) {
        arr[i] = (int *) malloc (sizeof(int) * cols);
    }
    return arr;
}

void input (int** arr, int rows, int cols) {
    FILE *file;
    if ((file = (fopen("f3.txt", "w"))) == NULL) {
        printf("파일을 열 수 없습니다.");
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &arr[i][j]);
            fprintf(file, "%d ", arr[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

double calculateStandardDeviation(int **arr, int rows, int cols) {
    double sum = 0.0, mean, variance = 0.0, stddev;
    int totalElements = rows * cols;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum += arr[i][j];
        }
    }

    mean = sum / totalElements;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            variance += pow(arr[i][j] - mean, 2);
        }
    }
    variance /= totalElements;

    stddev = sqrt(variance);

    return stddev;
}

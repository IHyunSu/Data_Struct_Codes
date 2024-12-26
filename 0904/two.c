#include <stdio.h>
#include <stdlib.h>

double* input(int n);
int search(double* arr, int n, double data);
void output(double* arr, int n);

int main() {
    double* arr;
    int n;

    scanf("%d", &n);
    
    arr = input(n);

    double data;
    printf("(scanf)\n");
    scanf("%lf", &data);

    int result = search(arr, n, data);
    output(arr, n);

    printf("index = %d\n", result);
    free(arr);
}

double* input(int n) {
    double* arr = (double*)malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &arr[i]);
    }
    return arr;
}

int search(double* arr, int n, double data) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == data) {
            return i;
        }
    }
    return -1;
}

void output(double* arr, int n) {
    printf("Array elements: ");
    for (int i = 0; i < n; i++) {
        printf("%.2lf ", arr[i]);
    }
    printf("\n");
}
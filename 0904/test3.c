#include <stdio.h>
#include <stdlib.h>

void fileInput ();
double* iuput(double* arr, int n);
int search(double* arr, int n, double data);
void output(double* arr, int n);

int main () {
    fileInput();
    double *arr;
    int n, data;
    FILE *file;
    if ((file = fopen("f2.txt", "r")) == NULL) {
        printf("파일을 읽을 수 없습니다.");
        exit(1);
    }
    fscanf(file, "%d", &n);

    arr = iuput(arr, n);

    fscanf(file, "%*d");
    for (int i = 0; i < n; i++) {
        fscanf(file, "%*f");
    }
    for (int i = 0; i < 7; i++) {
        fscanf(file, "%*s");
    }
    fscanf(file, "%d", &data);
    fclose(file);
    search(arr, n, data);
}

void fileInput () {
    FILE *file;
    if ((file = fopen("f2.txt", "w")) == NULL) {
        printf("파일이 열리지 않습니다.");
        exit(1);
    }
    int n;
    scanf("%d", &n);
    fprintf(file, "%d\n", n);
    double a;
    for (int i = 0; i < n; i++) {
        scanf("%lf", &a);
        fprintf(file, "%.2f ", a);
    }
    fprintf(file, "\n");
    fprintf(file, "(scanf)\n");
    int data;
    scanf("%d", &data);
    fprintf(file, "%d", data);
    fclose(file);
}

double* iuput(double* arr, int n) {
    arr = (double *) malloc (sizeof(double) * n);
    FILE *file;
    if ((file = fopen("f2.txt", "w")) == NULL) {
        printf("파일을 읽을 수 없습니다.");
        exit(1);
    }
    fscanf(file, "%*d");
    for (int i = 0; i < n; i++) {
        fscanf(file, "%lf", &arr[i]);
    }
    fclose(file);
    return arr;
}

int search(double* arr, int n, double data) {
    FILE *file;
    if ((file = fopen("f2.txt", "w")) == NULL) {
        printf("파일을 열 수 없습니다.");
        exit(0);
    }
    for (int i = 0; i < n; i++) {
        if (data == arr[i])
            return i;
    }
    return -1;
}


#include <stdio.h>
#include <stdlib.h>

void findMin (int n);

int main () {
    int n;
    FILE *file;
    if ((file = fopen("f2.txt", "r")) == NULL) {
        printf("cannot open file");
        exit(1);
    }
    fscanf(file, "%d", &n);
    fclose(file);
    findMin(n);
    return 0;
}

void findMin (int n) {
    int a, min;
    FILE *file;
    if ((file = fopen("f2.txt", "r")) == NULL) {
        printf("can not open file");
        exit(1);
    }
    fscanf(file, "%*d");
    fscanf(file, "%d", &a);
    min = a;
    for (int i = 1; i < n; i++) {
        fscanf(file, "%d", &a);
        if (a <= min) {
            min = a;
        }
    }
    fclose(file);
    printf("%d", min);
}
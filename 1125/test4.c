#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 20
#define SWAP(a, b, temp) { \
    temp = a; \
    a = b; \
    b = temp; \
}

typedef struct {
    char name[MAX_SIZE];
    int key;
    float grade;
} Student;

void quickSort(Student a[], int left, int right);

int main () {
    FILE *file = fopen("in.txt", "r");
    int n;
    fscanf(file, "%d", &n);

    Student a[MAX_SIZE];

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d %f", a[i].name, &a[i].key, &a[i].grade);
    }
    fclose(file);

    int left = 0, right = n-1;
    quickSort(a, left, right);

    for (int i = 0; i < n; i++) {
        printf("%s %d %.1f\n", a[i].name, a[i].key, a[i].grade);
    }
}

void quickSort(Student a[], int left, int right) {
    int i, j;
    char pivot[20];
    Student temp;

    if (left < right) {
        i = left, j = right+1;
        strcpy(pivot, a[left].name);
        do {
            do i++; while(strcmp(pivot, a[i].name) > 0);
            do j--; while(strcmp(pivot, a[j].name) < 0);
            if (i < j) SWAP(a[i], a[j], temp);
        } while (i < j);
        SWAP(a[left], a[j], temp);
        quickSort(a, left, j-1);
        quickSort(a, j+1, right);
    }
}
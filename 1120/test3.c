#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    char name[20];
    int grade;
} Student;

void insertSort(Student arr[], int n);
void insert(Student e, Student arr[], int i);
void printArray(Student arr[], int n);

int main () {
    FILE *file = fopen("in.txt", "r");

    Student arr[20];

    int n;
    fscanf(file, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d %s %d", &arr[i].key, arr[i].name, &arr[i].grade);
    }
    fclose(file);

    insertSort(arr, n);
    printArray(arr, n);
}

void insertSort(Student arr[], int n) {
    for (int j = 1; j < n; j++) {
        Student temp = arr[j];
        insert(temp, arr, j-1);
    }
}

void insert(Student e, Student arr[], int i) {
    while (arr[i].key > e.key) {
        arr[i+1] = arr[i];
        i--;
    }
    arr[i+1] = e;
}

void printArray(Student arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d %s %d\n", arr[i].key, arr[i].name, arr[i].grade);
    }
}
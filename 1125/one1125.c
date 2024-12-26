#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 20
#define SWAP(a, b, temp) { \
    temp = a;  \
    a = b;     \
    b = temp;  \
} 

typedef struct {
    char name[10];
    int number;
    float grade;
} Student;

void printStudents(Student arr[], int n);
void quickSort(Student arr[], int left, int right);

int main () {
    FILE *file = fopen("in.txt", "r");

    Student arr[MAX_STUDENTS];

    int n;
    fscanf(file, "%d", &n);
    for (int i = 1; i <= n; i++) {
        fscanf(file, "%s %d %f", arr[i].name, &arr[i].number, &arr[i].grade);
    }
    fclose(file);

    int left = 1, right = n;
    quickSort(arr, left, right);

    printStudents(arr, n);
}

void printStudents(Student arr[], int n) {
    printf("첫번째 문제 : \n");
    for (int i = 1; i <= n; i++) {
        printf("이름: %s, 학번: %d, 평균성적: %.2f\n", arr[i].name, arr[i].number, arr[i].grade);
    }
}

void quickSort(Student a[], int left, int right)
{
    char pivot[10];
    int i, j; Student temp;
    if (left < right) {
        i = left; j = right + 1;
        strcpy(pivot, a[left].name);
        do {
            do i++; while (strcmp(a[i].name, pivot) < 0);
            do j--; while (strcmp(a[j].name, pivot) > 0);
            if (i < j) SWAP(a[i], a[j], temp);
        } while (i < j);
        SWAP(a[left], a[j],temp);
        quickSort(a, left, j-1);
        quickSort(a, j+1, right);
    }
} 


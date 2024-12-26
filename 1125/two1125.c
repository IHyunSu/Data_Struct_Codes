#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 20

typedef struct {
    char name[10];
    int number;
    float grade;
} Student;

void printStudents(Student arr[], int n);
int compare(const void *a, const void *b);

int main() {
    FILE *file = fopen("in.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "파일을 열 수 없습니다.\n");
        return 1;
    }

    Student arr[MAX_STUDENTS];
    int n;
    fscanf(file, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d %f", arr[i].name, &arr[i].number, &arr[i].grade);
    }
    fclose(file);

    qsort(arr, n, sizeof(Student), compare);

    printStudents(arr, n);
    return 0;
}

void printStudents(Student arr[], int n) {
    printf("두번째 문제: \n");
    for (int i = 0; i < n; i++) {
        printf("이름: %s, 학번: %d, 평균성적: %.2f\n", arr[i].name, arr[i].number, arr[i].grade);
    }
}

int compare(const void *a, const void *b) {
    Student *studentA = (Student *)a;
    Student *studentB = (Student *)b;
    return strcmp(studentA->name, studentB->name);
}

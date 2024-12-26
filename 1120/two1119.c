#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    char name[10];
    int grade;
} student;

void insertion_sort(student arr[], int n);
void insert(student e, student arr[], int i);

int main() {
    student arr[10];
    FILE *file = fopen("in.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "파일을 열 수 없습니다.\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    int i = 0;
    while (i < n && (fscanf(file, "%d %s %d", &arr[i].key, arr[i].name, &arr[i].grade) == 3)) {
        i++;
    }
    fclose(file);

    printf("정렬 전:\n");
    for (int j = 0; j < i; j++) {
        printf("%d %s %d\n", arr[j].key, arr[j].name, arr[j].grade);
    }

    printf("\n");

    insertion_sort(arr, i);

    printf("정렬 후:\n");
    for (int j = 0; j < i; j++) {
        printf("%d %s %d\n", arr[j].key, arr[j].name, arr[j].grade);
    }

    return 0;
}

void insertion_sort(student arr[], int n) {
    for (int j = 1; j < n; j++) {
        student temp = arr[j];
        insert(temp, arr, j - 1);
    }
}

void insert(student e, student arr[], int i) {
    while (arr[i].key > e.key) {
        arr[i + 1] = arr[i];
        i--;
    }
    arr[i + 1] = e;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int num;
    char name[20];
    double grade1;
    double grade2;
    double qize;
} Student;

Student *creatStudents (int n);
void inputStudents(Student* students, int n);
void printStudents(Student* students, int n);
void searchStudent(Student* students, int n, char *searchName);
void freeStudent(Student* students, int n);

int main () {
    Student *students;
    int n;
    FILE *file;
    if ((file = fopen("f2.txt", "r")) == NULL) {
        printf("cannot open file");
        exit(1);
    }
    fscanf(file, "%d", &n);
    fclose(file);
    students = creatStudents(n);
    inputStudents(students, n);
    printStudents(students, n);
    char *searchName[20];
    printf("(scanf)\n");
    scanf("%99s", &searchName);
    searchStudent(students, n, searchName);
    freeStudent(students, n);
}

Student *creatStudents (int n) {
    return (Student*)malloc(sizeof(Student) * n);
}

void inputStudents(Student* students, int n) {
    FILE *file;
    if ((file = fopen("f2.txt", "r")) == NULL) {
        printf("cannot open file");
        exit(1);
    }
    fscanf(file, "%*d");
    for (int i = 0; i < n; i++) {
        fscanf(file, "%99s %lf %lf %lf", students[i].name, students[i].grade1,
        students[i].grade2, students[i].qize);
    }
    for (int i = 0; i < n; i++) {
        students[i].num = i + 1;
    }
    fclose(file);
}

void printStudents(Student* students, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d %99s %.1f %.1f %.1f %.1f\n", students[i].num, students[i].name, students[i].grade1, students[i].grade2, 
        students[i].qize, (students[i].grade1 + students[i].grade2 + students[i].qize));
    }
}

void searchStudent(Student* students, int n, char *searchName) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        if ((strcmp(searchName, students[i].name)) == 0) {
            printf("%d %99s %.1f %.1f %.1f %.1f\n", students[i].num, students[i].name, students[i].grade1, students[i].grade2, 
        students[i].qize, (students[i].grade1 + students[i].grade2 + students[i].qize));
        }
    }
}

void freeStudent(Student* students, int n) {
    free(students);
}

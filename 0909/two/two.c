#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int num;
    char name[10];
    double grade1;
    double grade2;
    double quiz;
} Student;

Student *createStudents(int n);
void inputStudents(Student *students, int n);
void printStudents(Student *students, int n);
void findStudents(Student *students, int n);
void freeStudents(Student *students);

int main () {
    Student *students;
    int n;

    FILE *file;
    if ((file = fopen("f2.txt", "r")) == NULL) {
        printf("Cannot open file");
        exit(1);
    }

    fscanf(file, "%d", &n);
    fclose(file);

    students = createStudents(n);
    if (students == NULL) {
        printf("Allocation failed\n");
        return -1;
    }
    inputStudents(students, n);
    printStudents(students, n);
    findStudents(students, n);
    freeStudents(students);

    return 0;
    
}

Student *createStudents(int n) {
    return (Student*)malloc(sizeof(Student) * n);
}

void inputStudents(Student *students, int n) {
    FILE *file;
    if ((file = fopen("f2.txt", "r")) == NULL) {
        printf("Cannot open file");
        exit(1);
    }
    fscanf(file, "%*d");
    for (int i =0; i < n; i++) {
        fscanf(file, "%5s %lf %lf %lf", students[i].name, &students[i].grade1, &students[i].grade2, 
        &students[i].quiz);
    }
    fclose(file);
}

void printStudents(Student *students, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d %s %.1f %.1f %.1f %.1f\n", i + 1, students[i].name, students[i].grade1, 
        students[i].grade2, students[i].quiz, (students[i].grade1 + students[i].grade2 + students[i].quiz));
    }
}

void findStudents(Student *students, int n) {
    printf("(scanf)\n");
    char findName[10];
    scanf("%s", findName);
    for (int i = 0; i < n; i++) {
        if (strcmp(students[i].name,findName) == 0) {
            printf("%d %s %.1f %.1f %.1f %.1f\n", i + 1, students[i].name, students[i].grade1, 
            students[i].grade2, students[i].quiz, (students[i].grade1 + students[i].grade2 + students[i].quiz));
        }
    }
}

void freeStudents(Student *students) {
    free(students);
}
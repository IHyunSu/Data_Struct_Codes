#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int sid;
    char name[10];
} Student;

Student* create(int size);
Student* resize(Student* array, int* size);
Student* add(Student* array, int* count, int* size, int id, char* name);
void removeById(Student* array, int* count, int id);
void print(Student* array, int count);
void freeArray(Student* array);

int main() {
    FILE *file;
    if ((file = fopen("f3.txt", "r")) == NULL) {
        printf("Cannot open file\n");
        exit(1);
    }

    int capacity = 10, size = 0;
    Student *array = create(capacity);
    
    int id;
    char name[10];

    while (fscanf(file, "%d %s", &id, name) == 2) {
        array = add(array, &size, &capacity, id, name);
    }
    fclose(file);

    // 학생 정보 출력
    print(array, size);

    // 메모리 해제
    freeArray(array);
    return 0;
}

Student* create(int size) {
    return (Student*) malloc(sizeof(Student) * size);
}

Student* resize(Student* array, int* size) {
    *size *= 2;
    return (Student*) realloc(array, sizeof(Student) * (*size));
}

Student* add(Student* array, int* count, int* size, int id, char* name) {
    if (*count >= *size) {
        array = resize(array, size);
        if (array == NULL) {
            fprintf(stderr, "Memory allocation error!\n");
            exit(1);
        }
    }
    array[*count].sid = id;
    strncpy(array[*count].name, name, sizeof(array[*count].name) - 1);
    array[*count].name[sizeof(array[*count].name) - 1] = '\0'; // null terminate
    (*count)++;
    return array;
}

void removeById(Student* array, int* count, int id) {
    for (int i = 0; i < *count; i++) {
        if (array[i].sid == id) {
            for (int j = i; j < (*count) - 1; j++) {
                array[j] = array[j + 1]; // Shift elements left
            }
            (*count)--; // Reduce count
            break;
        }
    }
}

void print(Student* array, int count) {
    for (int i = 0; i < count; i++) {
        printf("ID: %d, Name: %s\n", array[i].sid, array[i].name);
    }
}

void freeArray(Student* array) {
    free(array);
}

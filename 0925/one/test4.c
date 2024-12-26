#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int sid;
    char name[10];
} Student;

Student* create(int size);
Student* resize(Student* array, int* size);
Student* add(Student* array, int* count, int* size, int id, char* name) ;
void removeById(Student* array, int* count, int id);
void print(Student* array, int count);
void freeArray(Student* array);

int main () {
    FILE *file;
    if ((file = fopen("f3.txt", "r")) == NULL) {
        printf("can not open file");
        exit(1);
    }

    int size = 10, count = 0;

    Student* arr = create(size);

    int id;
    char name[10];

    while((fscanf(file, "%d %s", &id, name)) == 2) {
        arr = add(arr, &count, &size, id, name);
    }

    while (1) {
        int num;
        printf("1.추가 2.삭제 3.출력 4.종료\n");
        scanf("%d", &num);

        if (num == 1) {
            printf("학번 이름 입력 : ");
            scanf("%d %s", &id, name);
            arr = add(arr, &count, &size, id, name);
            printf("%d 데이터가 추가되었습니다.\n", id);
            printf("배열 데이터 개수 %d\n", count);
        }

        else if (num == 2) {
            printf("학번 입력 : ");
            scanf("%d", &id);
            remove(arr);
            // if (arr != NULL) {
            //     printf("학번 %d 데이터가 삭제 되었습니다.\n", id);
            //     printf("배열 데이터 개수 %d\n", count);
            // }
            // else {
            //     printf("학번 %d 데이터는 존재하지 않습니다.\n", id);
            //     printf("배열 데이터 개수 %d\n", count);
            // }
        }

        else if (num == 3) {

        }

        else if (num == 4) {
            break;
        }
    }
}

Student* create(int size) {
    return (Student*)malloc(sizeof(Student) * 10);
}

Student* resize(Student* array, int* size) {
    *size *= 2;
    return (Student*) realloc (array, sizeof(Student) * (*size));
}

Student* add(Student* array, int* count, int* size, int id, char* name) {
    while (*count >= *size) {
        array = resize(array, &size);
        if (array == NULL) {
            fprintf(stderr, "memory allocation error!");
            exit(1);
        }
    }
    array[*count].sid = id;
    strncpy(array[*count].name, name, sizeof(array[*count].name - 1));
    array[*count].name[sizeof(array[*count].name) - 1] = '\0';
    (*count)++;
    return array;
}

void removeById(Student* array, int* count, int id) {
    int left = 0;
    int right = *count - 1;
    while (left >= right) {
        int mid = (left + right) / 2;
        if (array[mid].sid == id) 
    }
}

void print(Student* array, int count) {

}

void freeArray(Student* array) {

}
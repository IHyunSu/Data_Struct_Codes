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
        printf("파일을 열 수 없습니다.\n");
        exit(1);
    }

    int size = 10, count = 0;

    Student* arr = create(size);

    int id;
    char name[10];

    while ((fscanf(file, "%d %s", &id, name)) == 2) {
        arr = add(arr, &count, &size, id, name);
    }

    fclose(file);

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
        } else if (num == 2) {
            printf("학번 입력 : ");
            scanf("%d", &id);
            removeById(arr, &count, id);
            printf("배열 데이터 개수 %d\n", count);
        } else if (num == 3) {
            print(arr, count);
        } else if (num == 4) {
            break;
        }
    }

    freeArray(arr); // 메모리 해제
    return 0;
}

Student* create(int size) {
    return (Student*)malloc(sizeof(Student) * size);
}

Student* resize(Student* array, int* size) {
    *size *= 2;
    return (Student*) realloc(array, sizeof(Student) * (*size));
}

Student* add(Student* array, int* count, int* size, int id, char* name) {
    while (*count >= *size) {
        array = resize(array, size);
        if (array == NULL) {
            fprintf(stderr, "메모리 할당 오류!\n");
            exit(1);
        }
    }
    array[*count].sid = id;
    strncpy(array[*count].name, name, sizeof(array[*count].name) - 1);
    array[*count].name[sizeof(array[*count].name) - 1] = '\0';
    (*count)++;
    return array;
}

void removeById(Student* array, int* count, int id) {
    for (int i = 0; i < *count; i++) {
        if (array[i].sid == id) {
            for (int j = i; j < *count - 1; j++) {
                array[j] = array[j + 1]; // 삭제된 자리 앞으로 당기기
            }
            (*count)--; // 카운트 감소
            printf("학번 %d 데이터가 삭제 되었습니다.\n", id);
            return;
        }
    }
    printf("학번 %d 데이터는 존재하지 않습니다.\n", id);
}

void print(Student* array, int count) {
    if (count == 0) {
        printf("데이터가 없습니다.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        printf("학번: %d, 이름: %s\n", array[i].sid, array[i].name);
    }
}

void freeArray(Student* array) {
    free(array);
}

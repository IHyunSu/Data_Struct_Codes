#include <stdio.h>
#include <stdlib.h>

int *listMalloc(int n);
void inputList(int *list, int n, char *str);
void selectSort(int *list, int n);
int binsearch(int *list, int searchnum, int left, int right);
void freeList(int *list);

int main() {
    int n;
    int *list;
    int searchnum, left, right;
    char str[10];
    scanf("%s", str);
    FILE *file;

    if ((file = fopen(str, "r")) == NULL) {
        printf("파일을 열 수 없습니다.\n");
        exit(1);
    }

    fscanf(file, "%d", &n);
    fclose(file);

    list = listMalloc(n);
    if (list == NULL) {
        printf("메모리 할당 오류\n");
        exit(1);
    }

    inputList(list, n, str);

    selectSort(list, n);

    printf("검색할 숫자를 입력하세요: ");
    scanf("%d", &searchnum);

    left = 0;
    right = n - 1;
    int index = binsearch(list, searchnum, left, right);

    if (index != -1) {
        printf("숫자 %d는 인덱스 %d에 있습니다.\n", searchnum, index);
    } else {
        printf("숫자 %d는 리스트에 없습니다.\n", searchnum);
    }

    freeList(list);
    return 0;
}

int *listMalloc(int n) {
    return (int *)malloc(sizeof(int) * n);
}

void inputList(int *list, int n, char *str) {
    FILE *file;
    if ((file = fopen(str, "r")) == NULL) {
        printf("파일을 열 수 없습니다.\n");
        exit(1);
    }
    fscanf(file, "%*d");
    for (int i = 0; i < n; i++) {
        if ((fscanf(file, "%d", &list[i])) != 1) {
            printf("입력 오류\n");
            exit(1);
        }
    }
    fclose(file);
}

void selectSort(int *list, int n) {
    int minIndex, tmp;
    for (int i = 0; i < n - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (list[j] < list[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            tmp = list[i];
            list[i] = list[minIndex];
            list[minIndex] = tmp;
        }
    }
}

int binsearch(int *list, int searchnum, int left, int right) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (list[mid] == searchnum) {
            return mid;
        }
        if (list[mid] < searchnum) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void freeList(int *list) {
    free(list);
}

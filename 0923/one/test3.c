#include <stdio.h>
#include <stdlib.h>

void printIntersect(int* arr1, int size1, int* arr2, int size2);

int main() {
    int* arr1 = (int*)malloc(sizeof(int) * 10);
    int* arr2 = (int*)malloc(sizeof(int) * 10);
    int size1 = 0, size2 = 0;
    int capacity1 = 10, capacity2 = 10;

    FILE* file1;
    if ((file1 = fopen("f3_1.txt", "r")) == NULL) {
        printf("can not open file f3_1.txt\n");
        exit(1);
    }

    FILE* file2;
    if ((file2 = fopen("f3_2.txt", "r")) == NULL) {
        printf("can not open file f3_2.txt\n");
        fclose(file1);
        exit(1);
    }

    while (1) {
        if (size1 >= capacity1) {
            capacity1 += 10;
            arr1 = (int*)realloc(arr1, sizeof(int) * capacity1);
            if (arr1 == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                exit(1);
            }
        }
        if (fscanf(file1, "%d", &arr1[size1]) != 1) break;
        size1++;
    }
    fclose(file1);

    // 두 번째 파일에서 숫자 읽기
    while (1) {
        if (size2 >= capacity2) {
            capacity2 += 10;
            arr2 = (int*)realloc(arr2, sizeof(int) * capacity2);
            if (arr2 == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                exit(1);
            }
        }
        if (fscanf(file2, "%d", &arr2[size2]) != 1) break;
        size2++;
    }
    fclose(file2);

    printIntersect(arr1, size1, arr2, size2);

    free(arr1);
    free(arr2);

    return 0;
}

void printIntersect(int* arr1, int size1, int* arr2, int size2) {
    // int* arr3 = (int*)malloc(sizeof(int) * (size1 < size2 ? size1 : size2));
    // int k = 0;

    // for (int i = 0; i < size1; i++) {
    //     for (int j = 0; j < size2; j++) {
    //         if (arr1[i] == arr2[j]) {
    //             int found = 0;
    //             for (int m = 0; m < k; m++) {
    //                 if (arr3[m] == arr1[i]) {
    //                     found = 1;
    //                     break;
    //                 }
    //             }
    //             if (!found) {
    //                 arr3[k] = arr1[i];
    //                 k++;
    //             }
    //         }
    //     }
    // }

    // for (int i = 0; i < k; i++) {
    //     printf("%d ", arr3[i]);
    // }
    // printf("\n");

    // free(arr3);

    int i = 0, j = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            i++;
        }
        else if (arr1[i] > arr2[j]) {
            j++;
        }
        else {
            printf("%d ", arr1[i]);
            i++;
            j++;
        }
    }
    printf("\n");

}

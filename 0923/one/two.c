#include <stdio.h>
#include <stdlib.h>

void printIntersect(int* arr1, int size1, int* arr2, int size2);

int main () {
    int* arr1;
    int* arr2;
    int size1 = 0;
    int size2 = 0;

    FILE* file1;
    if ((file1 = fopen("f2_1.txt", "r")) == NULL) {
        printf("can not open file f2_1.txt\n");
        exit(1);
    }

    FILE* file2;
    if ((file2 = fopen("f2_2.txt", "r")) == NULL) {
        printf("can not open file f2_2.txt\n");
        fclose(file1);
        exit(1);
    }

    while (!feof(file1)) {
        int temp;
        if (fscanf(file1, "%d", &temp) == 1) {
            size1++;
        }
    }
    rewind(file1);

    while (!feof(file2)) {
        int temp;
        if (fscanf(file2, "%d", &temp) == 1) {
            size2++;
        }
    }
    rewind(file2);

    arr1 = (int *) malloc (sizeof(int) * size1);
    arr2 = (int *) malloc (sizeof(int) * size2);

    for (int i = 0; i < size1; i++) {
        if (fscanf(file1, "%d", &arr1[i]) != 1) {
            fprintf(stderr, "Error reading from f2_1.txt\n");
            exit(1);
        }
    }

    for (int i = 0; i < size2; i++) {
        if (fscanf(file2, "%d", &arr2[i]) != 1) {
            fprintf(stderr, "Error reading from f2_2.txt\n");
            exit(1);
        }
    }

    fclose(file1);
    fclose(file2);

    printIntersect(arr1, size1, arr2, size2);

    free(arr1);
    free(arr2);

    return 0;
}

void printIntersect(int* arr1, int size1, int* arr2, int size2) {
    // int *arr3 = (int *) malloc (sizeof(int *) * size1 < size2 ? size1 : size2);
    // int k = 0;
    // for (int i = 0; i < size1; i++) {
    //     for (int j = 0; j < size2; j++) {
    //         if (arr1[i] == arr2[j]) {
    //             arr3[k] = arr1[i];
    //             k++;
    //         }
    //     }
    // }

    // for (int i = 0; i < k; i++) {
    //     printf("%d ", arr3[i]);
    // }

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
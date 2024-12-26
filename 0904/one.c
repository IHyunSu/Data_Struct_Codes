#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void readStoredArr (int [], int );
int maxValue (int [], int );
int minValue (int [], int );

int main () {
    FILE *file;
    int arr[10000] = {0};
    int i, num;
    const int millionNum = 10000;

    if ((file = (fopen("f1.txt", "w"))) == NULL) {
        printf("파일을 읽을 수 없습니다.");
        exit(1);
    }

    srand(time(NULL));

    for (i = 0; i < millionNum; i++) {
        fprintf(file, "%d\n", rand() % 10000);
    }

    fclose(file);

    readStoredArr (arr, millionNum);
    int max = maxValue (arr, millionNum);
    int min = minValue (arr, millionNum);

    printf("최댓값 : %d\n", max);
    printf("최소값 : %d", min);

}

void readStoredArr (int arr[], int millionNum) {
    FILE * file;
    if ((file = (fopen("f1.txt", "r"))) == NULL) {
        printf("파일을 읽을 수 없습니다.");
        exit(1);
    }

    for (int i = 0; i < millionNum; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);
}

int maxValue (int arr[], int millionNum) {
    int max = arr[0];

    for (int i = 1; i < millionNum; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    return max;
}

int minValue (int arr[], int millionNum) {
    int min = arr[0];

    for (int i = 1; i < millionNum; i++) {
        if (arr[i] < min)
            min = arr[i];
    }
    
    return min;
}

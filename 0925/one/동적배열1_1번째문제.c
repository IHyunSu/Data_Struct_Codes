#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linearSearch(int* arr, int n, int target);

int main () {
    int *arr;
    int N;
    scanf("%d", &N);

    arr = (int *) malloc (sizeof(int) * N); 

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % N;
    }

    int target;
    scanf("%d", &target);

    double duration;

    clock_t start = clock();
    int index = linearSearch(arr, N, target);
    clock_t end = clock();

    if (index != -1) printf("Index : %d\n", index);
    else printf("Not found\n");

    duration = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%.6f", duration);

    free(arr);

    return 0;

}

int linearSearch(int* arr, int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}
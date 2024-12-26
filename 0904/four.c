#include <stdio.h>
#include <stdlib.h>

int sumAry1D(int *ary, int size);

int main() {
    int **ary;
    int rowNum, size, totalSum = 0;

    scanf("%d", &rowNum);
    ary = (int **)calloc(rowNum, sizeof(int *));
    
    for (int i = 0; i < rowNum; i++) {
        scanf("%d", &size);
        ary[i] = (int *)calloc(size, sizeof(int));
        
        for (int j = 0; j < size; j++) {
            scanf("%d", &ary[i][j]);
        }
        
        totalSum += sumAry1D(ary[i], size);
    }

    for (int i = 0; i < rowNum; i++) {
        free(ary[i]);
    }
    free(ary);

    printf("배열 합 = %d\n", totalSum);
    return 0;
}

int sumAry1D(int *ary, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += ary[i];
    }
    return sum;
}

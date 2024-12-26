#include <stdio.h>
#include <stdlib.h>

int N, K;

int selection_sort(int A[]);

int selection_sort(int A[]) {
    int count = 0;

    for (int i = N - 1; i > 0; i--) {
        int big = 0;

        for (int j = 0; j <= i; j++)
            if (A[j] > A[big]) big = j;

        if (big != i) {
            int tmp = A[i];
            A[i] = A[big];
            A[big] = tmp;

            count++;
        }

        if (count == K) {
            for (int j = 0; j < N; j++)
                printf("%d ", A[j]);
            printf("\n");
            return 0;
        }
    }

    return -1;
}

int main() {
    scanf("%d %d", &N, &K);

    int *A = (int *)malloc(N * sizeof(int));
    if (A == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1; // 메모리 할당 실패 시 오류 반환
    }

    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    
    if (selection_sort(A) == -1)
        printf("-1\n");

    free(A); // 동적 메모리 해제
    return 0;
}

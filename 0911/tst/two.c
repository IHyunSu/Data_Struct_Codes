#include <stdio.h>

int selectSort (int *A, int N, int K);

int main () {
    int N, K;
    scanf("%d %d", &N, &K);
    int *A = (int *)malloc(sizeof(int) * N);
    
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    
    if (selectSort(A, N, K) == -1)
        printf("-1\n");

    free(A);
}

int selectSort (int *A, int N, int K) {
    int last, tmp, Cnt = 0;
    for (int i = N - 1; i > 0; i--) {
        last = i;
        for (int j = 0; j < i; j++) {
            if (A[j] > A[last]) last = j;
        }
        if (i != last) {
            tmp = A[i];
            A[i] = A[last];
            A[last] = tmp;

            Cnt++;
        }

        if (Cnt == K) {
            for (int j = 0; j < N; j++)
                printf("%d ", A[j]);
            printf("\n");
            return 0;
        }
    }
    return -1;
}
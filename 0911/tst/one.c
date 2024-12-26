#include <stdio.h>
#include <stdlib.h>

void selectSort(int *list, int n, int target);
int ch_n(int *list, int n);

int main() {
    int list[10001];
    int n, target;
    scanf("%d %d", &n, &target);
    for (int i = 0; i < n; i++) {
        scanf("%d", &list[i]);
    }
    selectSort(list, n, target);
    return 0;
}

void selectSort(int *list, int n, int target) {
    int largest, tmp, swapCnt = 0;

    for (int i = n - 1; i >= n - 1 - target && i > 0; i--) {
        largest = 0;
        for (int j = 1; j <= i; j++) {
            if (list[j] > list[largest]) {
                largest = j;
            }
        }
        if (i != largest) {
            tmp = list[i];
            list[i] = list[largest];
            list[largest] = tmp;
        }
        if ((ch_n(list, n)) == 1) {
            printf("-1");
            return; 
        }
    }


    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int ch_n(int *list, int n){
    int cnt = 0;
    for (int i = 0; i < n - 1; i++) {
        if (list[i] == i + 1) {
            cnt++;
        }
    }
    if (cnt == n - 1) {
        return 1;
    }
    else {
        return 0;
    }
}
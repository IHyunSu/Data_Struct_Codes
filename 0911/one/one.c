#include <stdio.h>

void findMin (int n);

int main () {
    int n;
    scanf("%d", &n);
    findMin(n);
    return 0;
}

void findMin (int n) {
    int a, min;
    scanf("%d", &a);
    min = a;
    for (int i = 1; i < n; i++) {
        scanf("%d", &a);
        if (a <= min) {
            min = a;
        }
    }
    printf("%d", min);
}
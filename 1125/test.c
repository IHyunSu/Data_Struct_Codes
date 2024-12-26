#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} element;

element a[20];
int link[20];

void readA(element a[], int* n);
void initLink(int link[], int n);
int rmergeSort(element a[], int link[], int left, int right);
int listMerge(element a[], int link[], int start1, int start2);

int main() {
    int n;

    readA(a, &n);
    initLink(link, n);

    if (n > 0) {
        int left = 0, right = n - 1;
        rmergeSort(a, link, left, right);
        
        printf("%d\n", n);
        for (int i = 0; i < n; i++) {
            printf("%d ", a[i].key);
        }
        printf("\n");

        // 링크 배열을 사용하여 정렬된 결과 출력
        for (int i = 0; i < n; i++) {
            printf("%d ", a[link[i]].key);
        }
        printf("\n");
    } else {
        printf("No data to sort.\n");
    }

    return 0;
}

void initLink(int link[], int n) {
    for (int i = 0; i < n; i++) {
        link[i] = -1; // 초기화 시 -1로 설정
    }
}

void readA(element a[], int* n) {
    (*n) = 0;
    FILE *file = fopen("in2.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file.\n");
        exit(1);
    }
    
    while ((fscanf(file, "%d", &a[*n].key)) == 1) {
        (*n)++;
    }
    fclose(file);
}

int rmergeSort(element a[], int link[], int left, int right) {
    if (left >= right) return left;
    int mid = (left + right) / 2;
    return listMerge(a, link, rmergeSort(a, link, left, mid), 
                            rmergeSort(a, link, mid + 1, right));
}

int listMerge(element a[], int link[], int start1, int start2) {
    int resultStart = -1; // 결과 리스트의 시작 인덱스
    int lastResult = -1; // 마지막 결과 인덱스

    while (start1 != -1 && start2 != -1) {
        if (a[start1].key <= a[start2].key) {
            if (resultStart == -1) {
                resultStart = start1; // 첫 번째 요소 설정
            } else {
                link[lastResult] = start1; // 이전 결과의 다음 요소 설정
            }
            lastResult = start1; // 마지막 결과 업데이트
            start1 = link[start1]; // 다음 요소로 이동
        } else {
            if (resultStart == -1) {
                resultStart = start2; // 첫 번째 요소 설정
            } else {
                link[lastResult] = start2; // 이전 결과의 다음 요소 설정
            }
            lastResult = start2; // 마지막 결과 업데이트
            start2 = link[start2]; // 다음 요소로 이동
        }
    }

    // 남아 있는 요소 추가
    if (start1 != -1) {
        if (resultStart == -1) {
            resultStart = start1; // 첫 번째 요소 설정
        } else {
            link[lastResult] = start1; // 이전 결과의 다음 요소 설정
        }
    } else if (start2 != -1) {
        if (resultStart == -1) {
            resultStart = start2; // 첫 번째 요소 설정
        } else {
            link[lastResult] = start2; // 이전 결과의 다음 요소 설정
        }
    }

    if (lastResult != -1) {
        link[lastResult] = -1; // 마지막 요소의 다음은 -1로 설정
    }

    return resultStart; // 결과의 시작 인덱스 반환
}

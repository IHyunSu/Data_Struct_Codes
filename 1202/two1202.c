#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STR_LEN 10  
#define MAX_ELEMENTS 10 
#define RADIX 27 

typedef struct {
    char value[MAX_STR_LEN + 1]; 
} element;

int digit(char c, int pos);
int radixSort(element a[], int link[], int d, int r, int n);
void printArrays(element a[], int link[], int n);

int main() {
    FILE *file = fopen("in.txt", "r");
    if (file == NULL) {
        perror("Unable to open file");
        return EXIT_FAILURE;
    }

    element a[MAX_ELEMENTS];
    int link[MAX_ELEMENTS];
    int i = 0;

    while ((fscanf(file, "%s", a[i].value) == 1) && (i < MAX_ELEMENTS)) {
        i++;
    }
    fclose(file);

    for (int j = 0; j < i; j++) {
        int len = strlen(a[j].value);
        for (int k = len; k < MAX_STR_LEN; k++) {
            a[j].value[k] = 'a' - 1;
        }
        a[j].value[MAX_STR_LEN] = '\0';
    }

    int first = radixSort(a, link, MAX_STR_LEN, RADIX, i);

    for (int current = first; current != -1; current = link[current]) {
        int len = strlen(a[current].value);
        for (int k = 0; k < len; k++) { // 문자열 길이만큼 반복
            if (a[current].value[k] == '`') {
                break;
            }
            printf("%c", a[current].value[k]);
        }
        printf(" "); // 각 문자열 사이에 공백 추가
    }

    printf("\n");


    return 0;
}

int digit(char c, int pos) {
    return c - ('a' - 1);
}

int radixSort(element a[], int link[], int d, int r, int n) {
    int front[r], rear[r];
    int first, last, current, bin;

    for (int i = 0; i < n - 1; i++) link[i] = i + 1;
    link[n - 1] = -1;
    first = 0;

    for (int pos = d - 1; pos >= 0; pos--) {
        for (bin = 0; bin < r; bin++) {
            front[bin] = -1;
            rear[bin] = -1;
        }

        for (current = first; current != -1; current = link[current]) {
            bin = digit(a[current].value[pos], pos);
            if (front[bin] == -1) {
                front[bin] = current;
            } else {
                link[rear[bin]] = current;
            }
            rear[bin] = current;
        }

        first = -1;
        for (bin = 0; bin < r; bin++) {
            if (front[bin] != -1) {
                if (first == -1) {
                    first = front[bin];
                } else {
                    link[last] = front[bin];
                }
                last = rear[bin];
            }
        }
        link[last] = -1; 
    }

    return first;
}

void printArrays(element a[], int link[], int n) {
    printf("Linked List Order:\n");
    for (int i = 0; i < n; i++) {
        printf("%s ", a[link[i]].value);
    }
    printf("\n");
}

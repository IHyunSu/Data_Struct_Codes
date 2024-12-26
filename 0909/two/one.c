#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inputStrings(char* p[], int n);
void printStrings(char* p[], int n);
void freeMemory(char* p[], int n);

int main() {
    char* p[100];
    int n;
    FILE *file;

    if ((file = fopen("f1.txt", "r")) == NULL) {
        printf("Cannot open file\n");
        exit(1);
    }

    fscanf(file, "%d", &n);
    fclose(file);

    inputStrings(p, n);
    printStrings(p, n);
    freeMemory(p, n);

    return 0;
}

void inputStrings(char* p[], int n) {
    char buffer[100];
    FILE *file;

    if ((file = fopen("f1.txt", "r")) == NULL) {
        printf("Cannot open file\n");
        exit(1);
    }

    fscanf(file, "%*d");

    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%99s", buffer) != 1) {
            printf("Error reading string %d\n", i + 1);
            exit(1);
        }

        p[i] = (char*)malloc(strlen(buffer) + 1);
        if (p[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        strcpy(p[i], buffer);
    }
    fclose(file);
}

void printStrings(char* p[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s ", p[i]);
    }
}

void freeMemory(char* p[], int n) {
    for (int i = 0; i < n; i++) {
        free(p[i]);
    }
}

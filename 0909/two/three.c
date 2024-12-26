#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b);
void printStrings(char strings[][20], int n);

int main () {
    char strings[20][20];

    FILE *file;
    if ((file = fopen("f3.txt", "r")) == NULL) {
        printf("Cannot open file\n");
        exit(1);
    }
    
    int i = 0;
    while (i < 20 && fscanf(file, "%19s", strings[i]) != EOF) {
        i++;
    }
    fclose(file);

    int n = i;

    qsort(strings, n, sizeof(strings[0]), cmp);

    printStrings(strings, n);

    return 0;
}

int cmp(const void *a, const void *b) {
    const char *str1 = (const char *)a;
    const char *str2 = (const char *)b;

    return strcmp(str1, str2);
}

void printStrings(char strings[][20], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s ", strings[i]);
    }
}

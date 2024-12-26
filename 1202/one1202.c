#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_SIZE 20

typedef struct {
    char key[MAX_KEY_SIZE];
    int x;
    int hash;
}Ht;

Ht ht[MAX_KEY_SIZE];

unsigned int stringToInt(char *key);
int search(int k, int D);

int main () {
    FILE *file1 = fopen("in.txt", "r");

    int D, i = 0;
    printf("(scanf: D value)\n");
    scanf("%d", &D);

    char temp[MAX_KEY_SIZE][MAX_KEY_SIZE];
    while (fscanf(file1, "%s", &temp[i][0]) == 1) {
        i++;
    }
    fclose(file1);

    int hashTemp, intTemp;
    for (int j = 0; j < i; j++) {
        intTemp = stringToInt(&temp[j][0]);
        hashTemp = intTemp % D;
        if (ht[hashTemp].hash == 0) {
            strcpy(ht[hashTemp].key, &temp[j][0]);
            ht[hashTemp].hash = hashTemp;
        } 
        else {
            Ht *current = &ht[++hashTemp];
            while (current[hashTemp].hash != 0) {
                hashTemp++;
            }
            strcpy(ht[hashTemp].key, &temp[j][0]);
            current[hashTemp].hash = hashTemp;
        }
    }
    for (int i = 0; i < D; i++) {
        ht[i].x = stringToInt(ht[i].key);
    }

    FILE *file2 = fopen("search.txt", "r");
    i = 0;
    while ((fscanf(file2, "%s", &temp[i][0])) == 1) {
        i++;
    }
    fclose(file2);

    printf("\n");
    int result;
    for (int j = 0; j < i; j++) {
        result = search(stringToInt(&temp[j][0]), D);
        if (result != 0)
            printf("S\n");
        else
            printf("E\n");
    }
    printf("\n");

    for (int i = 0; i < D; i++) {
        printf("%d: ", i);
        if (ht[i].x != 0) {
            printf("%s (%d)", ht[i].key, ht[i].x);
        }
        printf("\n");
    }

}

unsigned int stringToInt(char *key) {
    int number = 0;
    while (*key)
        number += *key++;
    return number;
}

int search(int k, int D) {
    int homeBucket, currentBucket, i = 0;
    homeBucket = 0;
    for (currentBucket = homeBucket; i < D && ht[currentBucket].x != k;) {
        currentBucket = (currentBucket + 1) % D;
        if (currentBucket == homeBucket)
            return 0;
        i++;
    }
    if (ht[currentBucket].x == k)
        return ht[currentBucket].x;
    return 0;
}
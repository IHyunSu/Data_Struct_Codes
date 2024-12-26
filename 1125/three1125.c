#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20

typedef struct {
    int key;
} element;

element a[20];
int link[20];

void readA(element a[], int* n);
void initLink(int link[], int n);
int rmergeSort(element a[], int link[], int left, int right);
int listMerge(element a[], int link[], int start1, int start2);
void mergeSort(element a[], int n);
void mergePass(element initList[], element mergedList[], int n, int s);
void merge(element initList[], element mergeList[], int i, int m, int n);



int main () {
    int n;

    readA(a, &n);
    initLink(link, n);

    int left = 0, right = n-1;
    rmergeSort(a, link, left, right);
    printf("%d\n", n);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i].key);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%d ", link[i]);
    }

    mergeSort(a, n);

    printf("\n");
    for (int i = 1; i < n; i++) {
        printf("%d ", a[i].key);
    }

}

void initLink(int link[], int n) {
    for (int i = 0; i < n; i++) {
        link[i] = 0;
    }
}

void readA(element a[], int* n) {
    (*n) = 1;
    FILE *file = fopen("in2.txt", "r");
    while ((fscanf(file, "%d", &a[*n].key)) == 1) {
        (*n)++;
    }
    fclose(file);
}

int rmergeSort(element a[], int link[], int left, int right)
{
    if (left >= right) return left;
    int mid = (left + right) / 2;
    return listMerge(a, link, rmergeSort(a, link, left, mid), 
                            rmergeSort(a, link, mid+1, right));
}

int listMerge(element a[], int link[], int start1, int start2) {
    int last1, last2, lastResult = 0;
    for (last1 = start1, last2 = start2; last1 && last2; ) {
        if (a[last1].key <= a[last2].key) {
            link[lastResult] = last1;
            lastResult = last1; last1 = link[last1];
        }
        else {
            link[lastResult] = last2;
            lastResult = last2; last2 = link[last2];
        }
    }
    if (last1 == 0) link[lastResult] = last2;
    else link[lastResult] = last1;
    return link[0];
}

void mergeSort(element a[], int n) {
    int s = 1; /* current segment size */
    element extra[MAX_SIZE];
    while (s<n) {
        mergePass(a, extra, n, s);  
        s *= 2;
        mergePass(extra , a, n , s);
        s *= 2;
    }
}

void mergePass(element initList[], element mergedList[], int n, int s)
{/* n: the number of elements in the list,
s: the size of each sorted segment */
    int i, j;
    for(i = 1; i <= n-2*s+1; i+= 2*s)
        merge(initList, mergedList, i, i+s-1, i+2*s-1);
    if((i+s-1)<n) merge(initList, mergedList, i, i+s-1, n);
    else
        for(j=i; j <= n; j++)
            mergedList[j] = initList[j];
}

void merge(element initList[], element mergeList[], int i, int m, int n)
{
    int j, k, t;
    j = m+1;
    k = i;

    while( i <= m && j <= n) {
        if (initList[i].key <= initList[j].key)
            mergeList[k++] = initList[i++];
        else
            mergeList[k++] = initList[j++];
    }
    if (i > m) /* mergedList[k:n] = initList[j:n]*/
        for(t = j; t <= n; t++)
            mergeList[t] = initList[t];
    else /* mergedList[k:n] = initList[i:m] */
        for(t = i; t <= m; t++)
            mergeList[k+t-i] = initList[t];
}
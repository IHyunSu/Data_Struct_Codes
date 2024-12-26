#include <stdio.h>

typedef struct {
    int key;
    char name[10];
    int grade;
} student;

void insertion_sort (student arr[], int n);
void insert(student e, student arr[], int i);
int binary_search(student arr[], int n, int left, int right, int target);

int main () {
    FILE *file = fopen("in.txt", "r");
    student arr[10];

    int n;
    fscanf(file, "%d", &n);

    for (int i = 0; i < n; i++) {
        fscanf(file, "%d %s %d", &arr[i].key, arr[i].name, &arr[i].grade);
    }
    insertion_sort(arr, n);

    int left = 0, right = n;

    for (int i = 0; i < n; i++) {
        printf("%d %s %d\n", arr[i].key, arr[i].name, arr[i].grade);
    }

    int target;
    scanf("%d", &target);
    int result_index = binary_search(arr, n, left, right, target);
    
    if (result_index == -1) {
        printf("해당 key는 데이터에 없습니다. 다시 입력해 주세요");
    } else {
        printf("해당 데이터는 %d번째에 있습니다.\n", result_index+1);
        printf("key: %d\nname: %s\ngrade: %d\n", arr[result_index].key, arr[result_index].name, arr[result_index].grade);
    }

}

void insertion_sort(student arr[], int n) {
    for (int j = 1; j < n; j++) {
        student temp = arr[j];
        insert(temp, arr, j - 1);
    }
}

void insert(student e, student arr[], int i) {
    while (arr[i].key > e.key) {
        arr[i + 1] = arr[i];
        i--;
    }
    arr[i + 1] = e;
}


int binary_search(student arr[], int n, int left, int right, int target) {
    while (left <= right) {
        int middle = (left + right) / 2;
        if (arr[middle].key < target) {
            left = middle+1;
        }
        else if (arr[middle].key > target) {
            right = middle-1;
        }
        else {
            return middle;
        }
    }
    return -1;
}
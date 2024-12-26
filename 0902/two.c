#include <stdio.h>

void Print (const char *fruits[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", fruits[i]);
    }
}

int main() {
    const char *fruits[] = {"Apple", "Banana", "Cherry", "Date", "Elderberry"};

    int size = sizeof(fruits) / sizeof(fruits[0]);

    Print(fruits, size);

   

}
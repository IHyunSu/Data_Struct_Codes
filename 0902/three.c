#include <stdio.h>

void colorProgram (const char *color[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", color[i]);
    }
}

int main () {
    const char *color[] = {"Red", "Green", "Blue", "Yellow", "Purple"};

    int size = sizeof(color) / sizeof(color[0]);

    colorProgram(color, size);
}
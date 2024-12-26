#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

Point* createPoints(int n);
void inputPoints(Point* points, int n);
void printPoints(const Point* points, int n);
void freePoints(Point* points);

int main () {
    Point* points;
    int n;

    printf("Number of points : ");
    scanf("%d", &n);

    points = createPoints(n);
    if (points == NULL) {
        printf("Allocation failed\n");
        return -1;
    }
    inputPoints(points, n);
    printPoints(points, n);
    freePoints(points);

    return 0;
}

Point* createPoints(int n) {
    return (Point*)malloc(n * sizeof(Point));
}

void inputPoints(Point* points, int n) {
    for (int i = 0; i < n; i++) {
        printf("Point %d (x y): ", i + 1);
        scanf("%d %d", &points[i].x, &points[i].y);
    }
}

void printPoints(const Point* points, int n) {
    for (int i = 0; i < n; i++) {
        printf("(%d, %d)", points[i].x, points[i].y);
    }
}

void freePoints(Point* points) {
    free(points);
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TERMS 100

typedef struct {
    float coef;  // 계수 (coefficient)
    int expon;   // 차수 (exoponent)
} polynominal;

polynominal terms[MAX_TERMS];
int avail = 0;

void attach(float coefficient, int exponent);
void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd);
void readPoly(int *starta, int *finisha, int *startb, int *finishb);
void printPoly(int startt, int finisht);
float evalPoly(int startd, int finishd, float x);

int main() {
    int startd, finishd;
    int starta, finisha, startb, finishb;

    readPoly(&starta, &finisha, &startb, &finishb);
    padd(starta, finisha, startb, finishb, &startd, &finishd);
    
    printf("D(x) = ");
    printPoly(startd, finishd);
    
    double x;
    printf("x 값을 입력하세요: ");
    scanf("%lf", &x);
    
    double result = evalPoly(startd, finishd, x);
    printf("D(%.2f) = %.2f\n", x, result);

    return 0;
}

void readPoly(int *starta, int *finisha, int *startb, int *finishb) {
    FILE *file; if ((file = fopen("f1.txt", "r")) == NULL) { printf("파일을 열 수 없습니다.\n");
        exit(1);
    }

    int n;
    fscanf(file, "%d", &n);
    (*starta) = 0;
    (*finisha) = n - 1;
    for (int i = (*starta); i <= (*finisha); i++) {
        fscanf(file, "%f %d", &terms[i].coef, &terms[i].expon);
    }
    avail += n;
    printf("A(x) = ");
    printPoly(*starta, *finisha);

    fscanf(file, "%d", &n);
    (*startb) = avail;
    (*finishb) = avail + n - 1;
    for (int i = (*startb); i <= (*finishb); i++) {
        fscanf(file, "%f %d", &terms[i].coef, &terms[i].expon);
    }
    avail += n;
    printf("B(x) = ");
    printPoly(*startb, *finishb);

    fclose(file);
}

void attach(float coefficient, int exponent) {
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "다항식 항의 수가 너무 많습니다.\n");
        exit(1);
    }

    terms[avail].coef = coefficient;
    terms[avail].expon = exponent;
    avail++;
}

void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd) {
    *startd = avail; 

    while (starta <= finisha && startb <= finishb) {
        if (terms[starta].expon == terms[startb].expon) {
            float sum = terms[starta].coef + terms[startb].coef;
            if (sum != 0) {
                attach(sum, terms[starta].expon);
            }
            starta++;
            startb++;
        } else if (terms[starta].expon > terms[startb].expon) {
            attach(terms[starta].coef, terms[starta].expon);
            starta++;
        } else {
            attach(terms[startb].coef, terms[startb].expon);
            startb++;
        }
    }
    
    while (starta <= finisha) {
        attach(terms[starta].coef, terms[starta].expon);
        starta++;
    }
    
    while (startb <= finishb) {
        attach(terms[startb].coef, terms[startb].expon);
        startb++;
    }
    
    *finishd = avail - 1; 
}

void printPoly(int startt, int finisht) {
    for (int i = startt; i <= finisht; i++) {
        printf("%dx^%d", (int)terms[i].coef, terms[i].expon);
        if (i < finisht) {
            printf(" + ");
        }
    }
    printf("\n");
}

float evalPoly(int startd, int finishd, float x) {
    double result = 0.0;
    for (int i = startd; i <= finishd; i++) {
        result += terms[i].coef * pow(x, terms[i].expon);
    }
    return result;
}

#include <stdio.h>

void sumArray (double sum[]) {
    double a;
    
    for (int i = 0; i < 10; i++) {
        scanf("%lf", &a);
        sum[i] = a;
    }

    double hap = 0.0;
    for (int i = 0; i < 10; i++) {
        hap += sum[i];
    }
    printf("합 = %.2f ", hap);
}

void averageArray (double sum[]) {
    double average = 0.0;
    for (int i = 0; i < 10; i++) {
        average += sum[i];
    }
    average = average / 10.0;
    printf("평균 = %.2f", average);
}

int main () {

    double sum[10] = {};

    sumArray(sum);
    averageArray(sum);

}
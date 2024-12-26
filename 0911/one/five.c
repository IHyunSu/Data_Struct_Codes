#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n);

int main () {
	int n;
	scanf("%d", &n);
	printf("%d", fibonacci(n));
	return 0;
}

int fibonacci(int n) {
	if (n == 0)	return 0;
	else if (n <= 1) return 1;

	return fibonacci(n - 1) + fibonacci (n - 2);
}

//이 시스템에서 계산할 수 있는 최대값은 40~45정도 된다.
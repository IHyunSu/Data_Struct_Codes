#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

typedef enum { 
    lparen, rparen, plus, minus, times, divide, mod, eos, operand 
} precedence;

char stack[MAX]; // 연산자 스택
int top = -1; // 스택의 최상위 인덱스

void push(char symbol) {
    stack[++top] = symbol;
}

char pop() {
    return stack[top--];
}

int isEmpty() {
    return top == -1;
}

precedence getToken(char *symbol, int *n, const char *expr) {
    *symbol = expr[(*n)++];
    switch (*symbol) {
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '/': return divide;
        case '*': return times;
        case '%': return mod;
        case '\0': return eos;
        default: return operand;
    }
}

void infixToPostfix(const char *expr) {
    char symbol;
    int n = 0;
    precedence token;

    while ((token = getToken(&symbol, &n, expr)) != eos) {
        if (token == operand) {
            printf("%c ", symbol); // 피연산자 출력
        } else if (token == lparen) {
            push(symbol);
        } else if (token == rparen) {
            while (!isEmpty() && (symbol = pop()) != '(') {
                printf("%c ", symbol); // 연산자 출력
            }
        } else { // 연산자
            while (!isEmpty() && precedence(stack[top]) >= precedence(token)) {
                printf("%c ", pop());
            }
            push(symbol);
        }
    }

    while (!isEmpty()) {
        printf("%c ", pop());
    }
    printf("\n");
}

int precedence(char op) {
    switch(op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/':
        case '%': return 2;
        default: return 0;
    }
}

int calculatePostfix(const char *postfix) {
    int stack[MAX], top = -1;
    char symbol;
    int n = 0;
    precedence token;

    while ((token = getToken(&symbol, &n, postfix)) != eos) {
        if (token == operand) {
            stack[++top] = symbol - '0'; // 문자 숫자로 변환 후 스택에 저장
        } else {
            int op2 = stack[top--];
            int op1 = stack[top--];
            switch (token) {
                case plus: stack[++top] = op1 + op2; break;
                case minus: stack[++top] = op1 - op2; break;
                case times: stack[++top] = op1 * op2; break;
                case divide: stack[++top] = op1 / op2; break;
                case mod: stack[++top] = op1 % op2; break;
            }
        }
    }
    return stack[top];
}

int main() {
    const char *expr = "6 2 / 3 - 4 2 * +"; // 후위 표기법으로 변환된 문자열
    infixToPostfix("(6/2-3+4*2)");
    printf("Result: %d\n", calculatePostfix(expr));
    return 0;
}

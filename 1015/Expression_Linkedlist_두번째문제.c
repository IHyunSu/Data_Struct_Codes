#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

typedef enum { 
    lparen, rparen, plus, minus, times, divide, mod, eos, operand 
} precedence;

char stack[MAX];
int top = -1;

void push(char symbol) {
    if (top >= MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = symbol;
}

char pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        return '\0';
    }
    return stack[top--];
}

char peek() {
    if (top == -1) {
        return '\0';
    }
    return stack[top];
}

int precedenceValue(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/':
        case '%': return 2;
        default: return 0;
    }
}

void infixToPostfix(const char *infix, char *postfix) {
    int i = 0, j = 0;
    char symbol;

    while ((symbol = infix[i++]) != '\0') {
        if (isdigit(symbol)) {
            postfix[j++] = symbol;
            postfix[j++] = ' ';
        } else if (symbol == '(') {
            push(symbol);
        } else if (symbol == ')') {
            while (top != -1 && peek() != '(') {
                postfix[j++] = pop();
                postfix[j++] = ' ';
            }
            pop();
        } else {
            while (top != -1 && precedenceValue(peek()) >= precedenceValue(symbol)) {
                postfix[j++] = pop();
                postfix[j++] = ' ';
            }
            push(symbol);
        }
    }

    while (top != -1) {
        postfix[j++] = pop();
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}

int evalPostfix(const char *postfix) {
    int stack[MAX];
    int top = -1;
    char symbol;
    int op1, op2;

    for (int i = 0; postfix[i] != '\0'; i++) {
        symbol = postfix[i];
        if (isspace(symbol)) continue;

        if (isdigit(symbol)) {
            stack[++top] = symbol - '0';
        } else {
            op2 = stack[top--];
            op1 = stack[top--];
            switch (symbol) {
                case '+': stack[++top] = op1 + op2; break;
                case '-': stack[++top] = op1 - op2; break;
                case '*': stack[++top] = op1 * op2; break;
                case '/': stack[++top] = op1 / op2; break;
                case '%': stack[++top] = op1 % op2; break;
            }
        }
    }
    return stack[top];
}

int main() {
    char infix[100];
    char postfix[100];

    FILE *file = fopen("in21.txt", "r");
    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }
    fgets(infix, sizeof(infix), file);
    fclose(file);

    infixToPostfix(infix, postfix);
    printf("%s\n", postfix);
    
    int result = evalPostfix(postfix);
    printf("%d\n", result);

    return 0;
}

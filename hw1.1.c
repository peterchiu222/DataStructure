#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_SIZE 100

// Stack data structure
struct Stack {
    int top;
    char items[MAX_SIZE];
};

// Function to push an item to the stack
void push(struct Stack* stack, char item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack->items[++stack->top] = item;
}

// Function to pop an item from the stack
char pop(struct Stack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->items[stack->top--];
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Function to get the precedence of an operator
int getPrecedence(char ch) {
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    return 0;
}

// Function to convert infix expression to postfix
void infixToPostfix(char* infix) {
    struct Stack stack;
    stack.top = -1;
    char postfix[MAX_SIZE];
    int i, j = 0;

    for (i = 0; infix[i]; i++) {
        char token = infix[i];

        if (isalnum(token)) {
            postfix[j++] = token;
        } else if (isOperator(token)) {
            while (stack.top >= 0 && getPrecedence(stack.items[stack.top]) >= getPrecedence(token)) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, token);
        } else if (token == '(') {
            push(&stack, token);
        } else if (token == ')') {
            while (stack.top >= 0 && stack.items[stack.top] != '(') {
                postfix[j++] = pop(&stack);
            }
            if (stack.top >= 0 && stack.items[stack.top] == '(') {
                pop(&stack);
            } else {
                printf("Invalid expression\n");
                exit(1);
            }
        }
    }

    while (stack.top >= 0) {
        if (stack.items[stack.top] == '(') {
            printf("Invalid expression\n");
            exit(1);
        }
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';
    printf("%s\n", postfix);
}

int main() {
    char infix[MAX_SIZE];
    scanf("%s", infix);
    infixToPostfix(infix);
    return 0;
}
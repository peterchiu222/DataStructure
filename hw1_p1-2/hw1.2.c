#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct Stack {
    char data[MAX_SIZE][MAX_SIZE];
    int top;
} Stack;

void initialize(Stack *stack) {
    stack->top = -1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, char item[]) {
    if (stack->top < MAX_SIZE - 1) {
        strcpy(stack->data[++stack->top], item);
    } else {
        printf("Stack overflow\n");
    }
}

void pop(Stack *stack, char result[]) {
    if (!isEmpty(stack)) {
        strcpy(result, stack->data[stack->top]);
        stack->top--;
    } else {
        printf("Stack is empty\n");
    }
}

void postfixToPrefix(char postfix[]) {
    Stack stack;
    initialize(&stack);

    int length = strlen(postfix);

    for (int i = 0; i < length; i++) {
        char item[MAX_SIZE];
        item[0] = postfix[i];
        item[1] = '\0';

        if (isalnum(postfix[i])) {
            push(&stack, item);
        } else {
            char operand1[MAX_SIZE], operand2[MAX_SIZE];
            pop(&stack, operand1);
            pop(&stack, operand2);
            char prefixExpr[MAX_SIZE];
            strcpy(prefixExpr, item);
            strcat(prefixExpr, operand2);
            strcat(prefixExpr, operand1);
            push(&stack, prefixExpr);
        }
    }

    char prefix[MAX_SIZE];
    pop(&stack, prefix);

    printf("%s\n", prefix);
}

int main() {
    char postfix[MAX_SIZE];
    scanf("%s", postfix);
    postfixToPrefix(postfix);
    return 0;
}

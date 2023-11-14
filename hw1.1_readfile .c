#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPRESSION_LENGTH 100

// Define a stack structure to hold operators
struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

// Create and initialize a stack
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Push an element onto the stack
void push(struct Stack* stack, char item) {
    stack->array[++stack->top] = item;
}

// Pop an element from the stack
char pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '\0'; // Null character indicates an empty stack
}

// Get the top element of the stack without popping
char peek(struct Stack* stack) {
    return stack->array[stack->top];
}

// Check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Get precedence of an operator
int precedence(char ch) {
    if (ch == '^')
        return 3;
    else if (ch == '*' || ch == '/')
        return 2;
    else if (ch == '+' || ch == '-')
        return 1;
    return 0;
}

// Convert infix expression to postfix expression
void infixToPostfix(char* infix, char* postfix) {
    struct Stack* stack = createStack(strlen(infix));
    int i, j;
    i = j = 0;

    while (infix[i] != '\0') {
        char c = infix[i];

        if (isalnum(c)) {
            postfix[j++] = c;
            i++;
        } else if (c == '(') {
            push(stack, c);
            i++;
        } else if (c == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                postfix[j++] = pop(stack);
            }
            if (!isEmpty(stack) && peek(stack) != '(')
                return; // Invalid expression
            else
                pop(stack);
            i++;
        } else {
            while (!isEmpty(stack) && precedence(c) <= precedence(peek(stack))) {
                postfix[j++] = pop(stack);
            }
            push(stack, c);
            i++;
        }
    }

    while (!isEmpty(stack)) {
        postfix[j++] = pop(stack);
    }

    postfix[j] = '\0';
}

int main() {
    char infix[MAX_EXPRESSION_LENGTH];
    char postfix[MAX_EXPRESSION_LENGTH];

    FILE *file = fopen("input_01.txt", "r");  

    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    while (fscanf(file, "%s", infix) != EOF) {
        infixToPostfix(infix, postfix);
        printf("Infix expression: %s\n", infix);
        printf("Postfix expression: %s\n", postfix);
    }

    fclose(file);  

    return 0;
}

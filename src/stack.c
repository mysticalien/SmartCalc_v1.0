#include "stack.h"

// #define MAX_LEN 255

// #define MAX_LEN 100

CalcStack *createStack() {
  CalcStack *newStack = (CalcStack *)malloc(sizeof(CalcStack));
  if (newStack != NULL) {
    newStack->length = 0;
    newStack->tokens = (char **)malloc(MAX_LEN * sizeof(char *));
    if (newStack->tokens == NULL) {
      free(newStack);
      newStack = NULL;
    }
  }
  return newStack;
}

bool isEmpty(CalcStack *stack) { return stack == NULL || stack->length == 0; }

bool isFull(CalcStack *stack) {
  return stack != NULL && stack->length == MAX_LEN;
}

void push(CalcStack *stack, char *token) {
  if (stack != NULL && !isFull(stack) && token != NULL) {
    stack->tokens[stack->length] = token;
    stack->length++;
  }
}

char *peek(CalcStack *stack) {
  return (isEmpty(stack)) ? NULL : stack->tokens[stack->length - 1];
}

char *pop(CalcStack *stack) {
  if (isEmpty(stack)) {
    return NULL;
  }
  stack->length--;
  return stack->tokens[stack->length];
}

void freeStack(CalcStack *stack) {
  if (stack != NULL && stack->tokens != NULL) {
    free(stack->tokens);
    stack->tokens = NULL;
    stack->length = 0;
    free(stack);
  }
}

// int main() {
//     CalcStack* myStack = createStack();
//
//     push(myStack, "sin");
//     push(myStack, "(");
//     push(myStack, ")");
//
//     printf("Top of the stack: %s\n", peek(myStack));
//
//     while (!isEmpty(myStack)) {
//         printf("Popped: %s\n", pop(myStack));
//     }
//
//     freeStack(myStack);
//
//     return 0;
// }

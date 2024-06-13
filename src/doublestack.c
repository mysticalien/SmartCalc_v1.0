#include "stack.h"

#define MAX_LEN 255

DoubleStack *initDoubleStack() {
  DoubleStack *newStack = (DoubleStack *)malloc(sizeof(DoubleStack));
  if (newStack != NULL) {
    newStack->length = 0;
    newStack->values = (long double *)malloc(MAX_LEN * sizeof(long double));
    if (newStack->values == NULL) {
      free(newStack);
      newStack = NULL;
    }
  }
  return newStack;
}

bool isDoubleStackEmpty(DoubleStack *stack) {
  return stack == NULL || stack->length == 0;
}

bool isDoubleStackFull(DoubleStack *stack) {
  return stack != NULL && stack->length == MAX_LEN;
}

void pushIntoDoubleStack(DoubleStack *stack, long double value) {
  if (stack != NULL && !isDoubleStackFull(stack)) {
    stack->values[stack->length] = value;
    stack->length++;
  }
}

long double peekDoubleStack(DoubleStack *stack) {
  return (isDoubleStackEmpty(stack)) ? 0 : stack->values[stack->length - 1];
}

long double popDoubleStack(DoubleStack *stack) {
  return (isDoubleStackEmpty(stack)) ? 0 : stack->values[--stack->length];
}

void removeDoubleStack(DoubleStack *stack) {
  if (stack != NULL) {
    if (stack->values != NULL) {
      free(stack->values);
    }
    free(stack);
  }
}

// int main() {
//     DoubleStack* myDoubleStack = initDoubleStack();
//
//     pushIntoDoubleStack(myDoubleStack, 3);
//     pushIntoDoubleStack(myDoubleStack, 2.718);
//     pushIntoDoubleStack(myDoubleStack, 02);
//
//     printf("Top of the double stack: %.7Lf\n",
//     peekDoubleStack(myDoubleStack));
//
//     while (!isDoubleStackEmpty(myDoubleStack)) {
//         printf("Popped: %.7Lf\n", popDoubleStack(myDoubleStack));
//     }
//
//     removeDoubleStack(myDoubleStack);
//
//     return 0;
// }

#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 255

typedef struct {
  char **tokens;
  int length;
} CalcStack;

typedef struct {
  long double *values;
  int length;
} DoubleStack;

DoubleStack *initDoubleStack();
bool isDoubleStackEmpty(DoubleStack *stack);
bool isDoubleStackFull(DoubleStack *stack);
void pushIntoDoubleStack(DoubleStack *stack, long double value);
long double peekDoubleStack(DoubleStack *stack);
long double popDoubleStack(DoubleStack *stack);
void removeDoubleStack(DoubleStack *stack);

CalcStack *createStack();
bool isEmpty(CalcStack *stack);
bool isFull(CalcStack *stack);
void push(CalcStack *stack, char *token);
char *peek(CalcStack *stack);
char *pop(CalcStack *stack);
void freeStack(CalcStack *stack);

#endif /* STACK_H */

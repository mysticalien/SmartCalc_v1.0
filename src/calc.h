#ifndef C7_SMARTCALC_V1_0_1_CALC_H
#define C7_SMARTCALC_V1_0_1_CALC_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

#define MAX_LEN 255

// Adding x if needed
char *replaceX(const char *expression, const char *value_of_x);

// Input Validation
bool isValidExpression(const char *expression);
bool processFunction(const char *expression, int *i, int *balance,
                     bool *lastWasOperand, int *is_valid);
void checkOperatorValidity(char currentChar, char prevChar, bool lastWasOperand,
                           int *is_valid);

// Parse Expression into tokens
void parseNumber(const char **ptr, char *token);
void processOperator(const char **ptr, char *tokens, int *lastWasOperand);
void readAlphaToken(const char **ptr, char *token);
void generateTokens(const char *expression, char *tokens);

// Reverse Polish Notation
int check_priority(char token);
void handleClosingParenthesis(char *temp, CalcStack *operators, int *is_fun);
void handleOperator(char *token, char *temp, CalcStack *operators);
void RPN(char *tokens, char *temp);

// Calcutations
int processOperation(DoubleStack *stack, long double *result, int sign);
int processFunctions(DoubleStack *stack, long double *result, char *func);
int processToken(char *token, DoubleStack *stack, long double *result);
int calculate(char *expression, long double *result);
// long double RPNcalculator(char* expression);
int RPNcalculator(const char *expression, long double *result);

// Loan Calculator
double convertYearsToMonths(double years);
long double calculateOverpaymentOnCredit(long double loanAmount,
                                         long double totalPayment);
long double calculateMonthlyDifferentiatedPayment(long double totalPayment,
                                                  double loanTermInMonths);
long double calculateMonthlyAnnuityPayment(long double principal,
                                           double periods,
                                           long double annualInterestRate);
long double calculateTotalAnnuityPayment(long double monthlyAnnuityPayment,
                                         double loanTermInMonths);
long double calculateTotalDifferentiatedPayment(long double principal,
                                                double periods,
                                                long double annualInterestRate);

typedef struct {
  double depositAmount;
  int depositTerm;
  double interestRate;
  int termUnit;  // 0 for days, 1 for months
  int capitalization;
  int depositFrequency;    // 0 for none, 1 for monthly, 2 for once in 2 months,
                           // etc.
  int additionalDeposits;  // 0 for false, 1 for true
  double additionalDepositAmount;
  int currency;
} DepositInfo;

typedef struct {
  double totalAmount;
  double totalInterest;
  double tax;
} DepositResult;

DepositResult calculateDepositIncome(DepositInfo deposit);

#endif  // C7_SMARTCALC_V1_0_1_CALC_H

#include "calc.h"

int processOperation(DoubleStack *stack, long double *result, int sign) {
  long double value1 = popDoubleStack(stack);
  long double value2 = popDoubleStack(stack);

  if (sign == '+') {
    *result = value2 + value1;
  } else if (sign == '-') {
    *result = value2 - value1;
  } else if (sign == '*') {
    *result = value2 * value1;
  } else if (sign == '/') {
    *result = value2 / value1;
  } else if (sign == '^') {
    *result = powl(value2, value1);
  }

  return isnan(*result) == 0 ? 1 : 0;
}

int processFunctions(DoubleStack *stack, long double *result, char *func) {
  long double value = popDoubleStack(stack);

  if (strstr(func, "mod")) {
    *result = fabsl(value);
  } else if (strstr(func, "acos")) {
    *result = acosl(value);
  } else if (strstr(func, "asin")) {
    *result = asinl(value);
  } else if (strstr(func, "atan")) {
    *result = atanl(value);
  } else if (strstr(func, "cos")) {
    *result = cosl(value);
  } else if (strstr(func, "sin")) {
    *result = sinl(value);
  } else if (strstr(func, "tan")) {
    *result = tanl(value);
  } else if (strstr(func, "sqrt")) {
    *result = sqrtl(value);
  } else if (strstr(func, "ln")) {
    *result = logl(value);
  } else if (strstr(func, "log")) {
    *result = log10l(value);
  }

  return isnan(*result) == 0 ? 1 : 0;
}

int processToken(char *token, DoubleStack *stack, long double *result) {
  int flag = 1;
  if (token == NULL || stack == NULL || result == NULL) {
    flag = 0;
  }
  if (flag == 1) {
    if (strchr("0123456789.", (int)*token)) {
      pushIntoDoubleStack(stack, strtold(token, &token));
    } else if (strchr("*/+-^", (int)*token)) {
      //            long double res = 0;
      flag = processOperation(stack, result, (int)*token);
      if (flag == 1) {
        pushIntoDoubleStack(stack, *result);
      }
    } else if (*token == 'u' || *token == 'p') {
      int sign = (*token == 'u') ? -1 : 1;
      pushIntoDoubleStack(stack, sign * popDoubleStack(stack));
    } else {
      flag = processFunctions(stack, result, token);
      if (flag == 1) {
        pushIntoDoubleStack(stack, *result);
      }
    }
  }

  return flag;
}

int calculate(char *expression, long double *result) {
  char temp[MAX_LEN + 1] = {'\0'};
  strncpy(temp, expression, MAX_LEN);

  int flag = 1;

  DoubleStack *stack = initDoubleStack();
  if (stack != NULL) {
    char *token = strtok(temp, " ");
    while (token != NULL && flag == 1 && strcmp(token, "w") != 0) {
      if (!processToken(token, stack, result)) {
        flag = 0;
      }
      if (flag == 1) {
        token = strtok(NULL, " ");
      }
    }

    *result = popDoubleStack(stack);
    removeDoubleStack(stack);
  }

  return flag;
}

int RPNcalculator(const char *expression, long double *result) {
  if (expression == NULL) {
    return 1;
  }

  int has_error = 0;

  if (isValidExpression(expression)) {
    char tokens[MAX_LEN * 2 + 1] = {'\0'};
    generateTokens(expression, tokens);
    char *temp = (char *)calloc(MAX_LEN * 2 + 1, sizeof(char));
    RPN(tokens, temp);
    has_error = !calculate(temp, result);
    free(temp);

  } else {
    has_error = 1;  // Флаг ошибки - недопустимое выражение
  }

  return has_error;
}

// int main() {
//     char *str = "log(log(log(1)))";
//     long double result;
//     RPNcalculator(str, &result);
//     printf("%Lf", result);
//     return 1;
// }

// int main() {
//     char expression[] = "2 2 + 1 u - mod w";
//     int has_error;
//     long double result = 0;
//     if (isValidExpression(expression)) {
//         char tokens[MAX_LEN * 2 + 1] = {'\0'};
//         generateTokens(expression, tokens);
//         printf("Tokens: %s\n", tokens);
//         char* temp = (char*)calloc(MAX_LEN * 2 + 1, sizeof(char));
//         RPN(tokens, temp);
//         printf("Postfix Expression: %s\n", temp);
//         long double result = 0;
//         has_error = !calculate(temp, &result);
//
//         if (has_error == 1) {
//             printf("Error in expression evaluation.\n");
//         } else {
//             printf("%Lf\n", result);
//         }
//     } else {
//         printf("The expression is not valid.\n");
//         has_error = 0;
//     }
//     char* str = "4 6 * sin u 99 + 7 5 + mod +";
//     long double result = 0;
//     int has_error = !calculate(str, &result);
//
//     if (has_error == 1) {
//         printf("Error in expression evaluation.\n");
//     } else {
//         printf("Result: %Lf\n", result);
//     }
//
//     return has_error == 1 ? 1 : 0;
// }

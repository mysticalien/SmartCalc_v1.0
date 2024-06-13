#include "calc.h"
#include "stack.h"

int check_priority(char token) {
  int priority = 0;
  if (token == '(') {
    priority = 0;
  } else if (token == '+' || token == '-') {
    priority = 1;
  } else if (token == '*' || token == '/') {
    priority = 2;
  } else if (token == '^') {
    priority = 3;
  } else if (token == 'u' || token == 'p') {
    priority = 4;
  } else if (token == 'm' || token == 'c' || token == 's' || token == 't' ||
             token == 'a' || token == 'l') {
    priority = 0;
  }
  return priority;
}

void handleClosingParenthesis(char *temp, CalcStack *operators, int *is_fun) {
  int is_end = 0;
  int pair = 0;

  while (is_end == 0 && pair == 0) {
    if (!isEmpty(operators)) {
      if (strchr("mcstal", (int)*peek(operators))) {
        (*is_fun)--;
        strcat(temp, pop(operators));
        strcat(temp, " ");
        pair = 1;
      } else if (*peek(operators) == '(') {
        pop(operators);
        (*is_fun)--;
        pair = 1;
      } else if (*peek(operators) != '(' &&
                 !strchr("mcstal", (int)*peek(operators))) {
        strcat(temp, pop(operators));
        strcat(temp, " ");
      }
    } else if (isEmpty(operators) || *is_fun == 0) {
      is_end = 1;
    }
  }
}

void handleOperator(char *token, char *temp, CalcStack *operators) {
  if (peek(operators) != NULL) {
    char prevOperator;
    //        if (!strchr("mcstal", (int)*peek(operators))) {
    //            prevOperator = *peek(operators);
    //        }

    prevOperator = *peek(operators);

    char currOperator = *token;

    if (check_priority(currOperator) > check_priority(prevOperator) ||
        (check_priority(currOperator) == check_priority(prevOperator) &&
         check_priority(currOperator) == 3)) {
      push(operators, token);
    } else {
      while (peek(operators) != NULL &&
             !strchr("mcstal(", (int)*peek(operators))) {
        strcat(temp, pop(operators));
        strcat(temp, " ");
      }
      //            strcat(temp, pop(operators));
      //            strcat(temp, " ");
      push(operators, token);
    }
  } else {
    push(operators, token);
  }
}

void RPN(char *tokens, char *temp) {
  CalcStack *operators = createStack();
  memset(temp, '\0', MAX_LEN * 2 + 2);
  char *token = strtok(tokens, " ");
  int len = MAX_LEN * 2;
  int is_fun = 0;

  while (len - (int)strlen(token) > 0 && token != NULL && *token != 'w') {
    if (strchr("0123456789.x", (int)*token)) {
      strcat(temp, token);
      strcat(temp, " ");
    } else if (strchr("*/+-^", (int)*token)) {
      handleOperator(token, temp, operators);
    } else if (strchr("mcstalup(", (int)*token)) {
      push(operators, token);
      is_fun += 1;
    } else if (strchr(")", (int)*token)) {
      handleClosingParenthesis(temp, operators, &is_fun);
    }

    token = strtok(NULL, " ");
    if (token != NULL) {
      len -= (int)strlen(token) + 1;  // 1 -> size of space char
    }
  }

  while (!isEmpty(operators)) {
    strcat(temp, pop(operators));
    strcat(temp, " ");
  }

  strcat(temp, "w");
  strcat(temp, " ");

  freeStack(operators);

  strncpy(tokens, temp, sizeof(temp) - 1);
}

// int main() {
//     char tokens[] = "u sin ( 4 ^ 6 ) + 99 ) + mod u x + 5 ) w";
//
//     char* temp = (char*)calloc(MAX_LEN * 2 + 1, sizeof(char));
//     RPN(tokens, temp);
////    printf("Infix Expression: %s\n", tokens);
//
//    printf("Postfix Expression: %s\n", temp);
//    return 0;
//}

// int main() {
//     char tokens[] = "u sin ( 4 ^ 6 ) + 99 ) + mod u x + 5 ) w";
////    char tokens[] = "p 3.1466666666 + ( 2 * 5 ) - sqrt 9.0 + ( 4 * 6 ) ) +
/// mod u x + 5 ) q";
//    int error = 0;
//    if (tokens[0] == '\0') {
//        error = 1;
//    }
//
//    char* temp = (char*)calloc(MAX_LEN * 2 + 1, sizeof(char));
//    CalcStack* operators = createStack();
//    if (operators != NULL && error == 0 && temp != NULL) {
//        memset(temp, '\0', MAX_LEN * 2 + 2);
//        char* token = strtok(tokens, " ");
//        int len = MAX_LEN * 2;
//        int is_fun = 0;
//        while (len - (int)strlen(token) > 0 && token != NULL && *token != 'w')
//        {
////            printf("MARUSS   %s\n", temp);
////            printf("OL   %s\n", token);
////            printf("??? %s\n", peek(operators));
//            if (strchr("0123456789.x", (int)*token)) {
//                strcat(temp, token);
//                strcat(temp, " ");
//            } else if (strchr("*/+-^", (int)*token)) {
//                if (peek(operators) != NULL) {
//                    char prevOperator = '(';
//                    if (!strchr("mcstal", (int)*peek(operators))) {
//                        prevOperator = *peek(operators);
//                    }
//
////                    printf("PREV %c\n", prevOperator);
//                    char currOperator = *token;
//
//                    if (check_priority(currOperator) >
//                    check_priority(prevOperator) ||
//                    (check_priority(currOperator) ==
//                    check_priority(prevOperator) &&
//                    check_priority(currOperator) == 3)) {
//                        push(operators, token);
////                        printf("Post %s\n", peek(operators));
//                    } else {
//                        strcat(temp, pop(operators));
//                        strcat(temp, " ");
//                        push(operators, token);
//                    }
//                } else {
//                    push(operators, token);
//                }
//            } else if (strchr("mcstalup(", (int)*token)) {
//                push(operators, token);
//                is_fun += 1;
//            } else if (strchr(")", (int)*token)) {
//                int is_end = 0;
//                int pair = 0;
//                while (is_end == 0 && pair == 0) {
//                    if (!isEmpty(operators)) {
////                        printf("STAAACKK %s", peek(operators));
//                        if (strchr("mcstal", (int)*peek(operators))) {
//                            is_fun -= 1;
//                            strcat(temp, pop(operators));
//                            strcat(temp, " ");
//                            if (!isEmpty(operators)) {
//                                strcat(temp, pop(operators));
//                                strcat(temp, " ");
//                            }
//                            pair = 1;
//                        } else if (*peek(operators) == '(') {
//                            pop(operators);
//                            is_fun -= 1;
//                            pair = 1;
//                        } else if (is_fun >= 1) {
//                            strcat(temp, pop(operators));
//                            strcat(temp, " ");
//                        }
//                    } else if (isEmpty(operators) || is_fun == 0) {
//                        is_end = 1;
//                    }
//                }
//            }
//            token = strtok(NULL, " ");
//            if (token != NULL) {
//                len -= (int)strlen(token) + 1;  // 1 -> size of space char
//            }
//        }
//
//        while (!isEmpty(operators)) {
//            strcat(temp, pop(operators));
//            strcat(temp, " ");
//        }
//
//        strcat(temp, "w");
//        strcat(temp, " ");
//
//        freeStack(operators);
//
//        strncpy(tokens, temp, sizeof(temp) - 1);
//        printf("Infix Expression: %s\n", tokens);
//        printf("Postfix Expression: %s\n", temp);
//    } else {
//        error = 1;
//    }
//    return 0;
//}

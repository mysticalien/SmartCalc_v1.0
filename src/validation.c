#include "calc.h"

bool processFunction(const char *expression, int *i, int *balance,
                     bool *lastWasOperand, int *is_valid) {
  char functionName[16];
  int j = 0;

  if (*lastWasOperand) {
    *is_valid = 0;
  }

  int bracket_found = 0;

  while (((isalpha(expression[*i]) && j < 15) || (expression[*i] == '(')) &&
         bracket_found == 0 && expression[*i] != 'x') {
    functionName[j++] = expression[(*i)++];
    if (expression[*i] == '(') {
      bracket_found = 1;
      functionName[j++] = expression[(*i)++];
    }
  }

  functionName[j] = '\0';

  if (strcmp(functionName, "sin(") == 0 || strcmp(functionName, "cos(") == 0 ||
      strcmp(functionName, "mod(") == 0 || strcmp(functionName, "ln(") == 0 ||
      strcmp(functionName, "tan(") == 0 || strcmp(functionName, "log(") == 0 ||
      strcmp(functionName, "acos(") == 0 ||
      strcmp(functionName, "asin(") == 0 ||
      strcmp(functionName, "atan(") == 0 ||
      strcmp(functionName, "sqrt(") == 0) {
    *lastWasOperand = false;  // Сброс флага перед функцией
    *balance += 1;
  } else {
    *is_valid = 0;
  }

  (*i)--;  // Вернем i на последний символ, который не входит в имя функции

  return *is_valid;
}

void checkOperatorValidity(char currentChar, char prevChar, bool lastWasOperand,
                           int *is_valid) {
  if (prevChar == '+' || prevChar == '-' || prevChar == '*' ||
      prevChar == '/' || prevChar == '^') {
    *is_valid = 0;
  }
  if (!lastWasOperand && currentChar != '-' && currentChar != '+') {
    *is_valid = 0;  // Оператор без операнда
  }
}

bool isValidExpression(const char *expression) {
  int balance = 0;
  int flag = 0;
  int is_valid = 1;
  int flag_x = 1;
  bool lastWasOperand = false;  // Флаг для отслеживания последнего операнда
  char prevChar = '(';

  for (int i = 0; expression[i] != '\0' && is_valid; i++) {
    char currentChar = expression[i];
    if (currentChar == '(') {
      balance++;
      lastWasOperand = false;  // Сброс флага перед открывающей скобкой
      flag = 0;
      flag_x = 1;
    } else if (currentChar == ')') {
      balance--;
      if (balance < 0 || !lastWasOperand) {
        is_valid = 0;  // Несогласованные скобки или отсутствие операнда
      }
      lastWasOperand = true;
      flag = 0;
      flag_x = 0;
    } else if ((currentChar == 'x') && lastWasOperand) {
      is_valid = 0;
    } else if ((currentChar == 'x') && (flag_x == 1)) {
      lastWasOperand = true;
      flag_x = 0;
    } else if (isalpha(currentChar)) {
      is_valid =
          processFunction(expression, &i, &balance, &lastWasOperand, &is_valid);
      flag = 0;
      flag_x = 1;
    } else if ((isdigit(currentChar) && prevChar != 'x') ||
               (isdigit(prevChar) && currentChar == '.' && flag == 0)) {
      lastWasOperand = true;  // Установка флага после цифры или точки
      if (currentChar == '.') {
        flag = 1;
      }
      flag_x = 0;
    } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' ||
               currentChar == '/' || currentChar == '^') {
      checkOperatorValidity(currentChar, prevChar, lastWasOperand, &is_valid);
      lastWasOperand = false;  // Сброс флага перед оператором
      flag = 0;
      flag_x = 1;
    } else if (isspace(currentChar)) {
      is_valid = 0;  // Недопустимый символ, исключая пробелы
    }

    prevChar = currentChar;
  }

  return balance == 0 && lastWasOperand &&
         is_valid == 1;  // В конце должен быть операнд
}
////
// int main() {
//     const char expression[] = "sin(sin(sin(x)))";
//     if (isValidExpression(expression)) {
//         printf("The expression is valid.\n");
//     } else {
//         printf("The expression is not valid.\n");
//     }
//
//     return 0;
// }

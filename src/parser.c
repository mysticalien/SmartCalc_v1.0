#include "calc.h"

void parseNumber(const char **ptr, char *token) {
  int j = 0;
  char current = **ptr;

  while (isdigit(current) || current == '.') {
    token[j++] = current;
    (*ptr)++;
    current = **ptr;
  }
}

void processOperator(const char **ptr, char *tokens, int *lastWasOperand) {
  char current = **ptr;
  char token[MAX_LEN] = {'\0'};

  if ((current == '+' || current == '-') && !(*lastWasOperand)) {
    token[0] = (current == '+') ? 'p' : 'u';
    strcat(tokens, token);
    strcat(tokens, " ");
    (*ptr)++;
  } else {
    token[0] = current;
    strcat(tokens, token);
    strcat(tokens, " ");
    (*ptr)++;
  }

  *lastWasOperand = (current == 'x' || current == ')') ? 1 : 0;
}

void readAlphaToken(const char **ptr, char *token) {
  int j = 0;
  char current = **ptr;

  while (isalpha(current)) {
    token[j++] = current;
    (*ptr)++;
    current = **ptr;
  }

  (*ptr)++;
}

void generateTokens(const char *expression, char *tokens) {
  int lastWasOperand = 0;

  memset(tokens, '\0', MAX_LEN * 2 + 2);

  const char *ptr = expression;

  while (*ptr != '\0') {
    char current = *ptr;
    char token[MAX_LEN] = {'\0'};

    if (isdigit(current) || current == '.') {
      parseNumber(&ptr, token);
      strcat(tokens, token);
      strcat(tokens, " ");
      lastWasOperand = 1;
    } else if (current == 'x' || current == '+' || current == '-' ||
               current == '*' || current == '/' || current == '^' ||
               current == '(' || current == ')') {
      processOperator(&ptr, tokens, &lastWasOperand);
    } else if (isalpha(current)) {
      readAlphaToken(&ptr, token);
      strcat(tokens, token);
      strcat(tokens, " ");
    }
  }
  strcat(tokens, "w");
  strcat(tokens, " ");
}

// int main() {
//     char* expression = "3.1466666666+(-2*5)-sqrt(9.0)+mod(x)";
//     char tokens[MAX_LEN * 2 + 1] = {'\0'};
//     generateTokens(expression, tokens);
//     printf("Tokens: %s\n", tokens);
//
//     return 0;
// }

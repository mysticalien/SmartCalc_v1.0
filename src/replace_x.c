#include "calc.h"

int countOccurrences(const char *expression, char x) {
  int count = 0;
  for (; *expression != '\0'; ++expression) {
    if (*expression == x) {
      ++count;
    }
  }
  return count;
}

char *replaceX(const char *expression, const char *value_of_x) {
  int count = countOccurrences(expression, 'x');
  size_t value_len = strlen(value_of_x);
  size_t new_length = strlen(expression) - count + (count * (value_len + 2)) +
                      1;  // +2 for brackets, +1 for null terminator

  char *result = (char *)malloc(new_length);
  if (result == NULL) {
    perror("Failed to allocate memory for result string");
    return NULL;
  }

  const char *ptr = expression;
  char *res_ptr = result;
  while (*ptr) {
    if (*ptr == 'x') {
      *res_ptr++ = '(';

      memcpy(res_ptr, value_of_x, value_len);
      res_ptr += value_len;

      *res_ptr++ = ')';
      ptr++;
    } else {
      *res_ptr++ = *ptr++;
    }
  }
  *res_ptr = '\0';

  return result;
}

// int main() {
//     char *str = "(3.5+x)+sqrt(x)";
//     char *x_value = "4.5678";
//     char* result = replaceX(str, x_value);
////    char expression[100]; // Предполагается, что длина выражения не
/// превышает 100 символов /    char randomNumber[100]; // Предполагается, что
/// длина числа не превышает 100 символов
////
////    // Получение выражения от пользователя
////    printf("Введите выражение с символом 'x': ");
////    scanf("%s", expression);
////
////    // Получение числа от пользователя
////    printf("Введите число: ");
////    scanf("%s", randomNumber);
////
////    // Замена символа 'x' на введенное число
////    replaceX(expression, randomNumber);
//
//    // Вывод результата
//    printf("Результат: %s\n", result);
//    free(result);
//
//    return 0;
//}
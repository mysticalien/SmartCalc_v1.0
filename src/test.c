#include <check.h>

#include "calc.h"

//--------------------------s21_strncmp---------------------------------
#define EPSILON 0.000001
#define EPSILON2 0.01

START_TEST(test1) {
  const char *str = "(3.5+2.2)*(8.4-6.1)+sqrt(25)";
  long double result = 0;
  RPNcalculator(str, &result);
  ck_assert_ldouble_eq_tol(result, 18.110000, EPSILON);
}
END_TEST

START_TEST(test2) {
  const char *str = "(4.8*(7.2-3.6))/2+cos(60)";
  long double result = 0;
  RPNcalculator(str, &result);

  ck_assert_ldouble_eq_tol(result, 7.687587, EPSILON);
}
END_TEST

START_TEST(test3) {
  const char *str = "2^(3*(1.5+2))-10/2";
  long double result = 0;
  RPNcalculator(str, &result);

  ck_assert_ldouble_eq_tol(result, 1443.154688, EPSILON);
}
END_TEST

START_TEST(test4) {
  const char *str = "3+4";
  long double result = 0;
  RPNcalculator(str, &result);

  ck_assert_ldouble_eq_tol(result, 7.000000, EPSILON);
}
END_TEST

START_TEST(test5) {
  const char *str = "ln(1) + log(10)";
  long double result = 0;
  RPNcalculator(str, &result);

  ck_assert_ldouble_eq_tol(result, 0.000000, EPSILON);
}
END_TEST

START_TEST(test6) {
  const char *str = "ln(1)+log(10)";
  long double result = 0;
  RPNcalculator(str, &result);

  ck_assert_ldouble_eq_tol(result, 1.000000, EPSILON);
}
END_TEST

START_TEST(test7) {
  const char *str = "(-atan(7+(8*3)))/4";
  long double result = 0;
  RPNcalculator(str, &result);

  ck_assert_ldouble_eq_tol(result, -0.384637, EPSILON);
}
END_TEST

START_TEST(test8) {
  const char *str = "(-tan(7+(8*3)))/4";
  long double result = 0;
  RPNcalculator(str, &result);

  ck_assert_ldouble_eq_tol(result, 0.110424, EPSILON);
}
END_TEST

START_TEST(test9) {
  const char *str = "mod(-2)";
  long double result = 0;
  RPNcalculator(str, &result);

  ck_assert_ldouble_eq_tol(result, 2.000000, EPSILON);
}
END_TEST

START_TEST(test10) {
  const char *str = "2/0";
  long double result = 0;
  RPNcalculator(str, &result);

  ck_assert_ldouble_infinite(result);
}
END_TEST

START_TEST(test11) {
  const char *str = "-77.9999";
  long double result = 0;
  RPNcalculator(str, &result);

  ck_assert_ldouble_eq_tol(result, -77.999900, EPSILON);
}
END_TEST

START_TEST(test12) {
  const char *str = "(3*19*(3+4/(1*2)))";
  long double result = 0;
  RPNcalculator(str, &result);

  ck_assert_ldouble_eq_tol(result, 285.000000, EPSILON);
}
END_TEST

START_TEST(test13) {
  const char *str = "6+5*12^6+28*2-3-4";
  long double result = 0;
  RPNcalculator(str, &result);

  ck_assert_ldouble_eq_tol(result, 14929975.000000, EPSILON);
}
END_TEST

START_TEST(test14) {
  const char *str = "log(7)+5*12^2+567";
  long double result = 0;
  RPNcalculator(str, &result);

  ck_assert_ldouble_eq_tol(result, 1287.845098, EPSILON);
}
END_TEST

START_TEST(test15) {
  const char *str = "log(7+5*12^2+567)";
  long double result = 0;
  RPNcalculator(str, &result);

  ck_assert_ldouble_eq_tol(result, 3.111934, EPSILON);
}
END_TEST

START_TEST(test16) {
  const char *str = "cos(72+(log(3+2)*3)-96)/2";
  long double result = 0;
  RPNcalculator(str, &result);

  ck_assert_ldouble_eq_tol(result, -0.498063, EPSILON);
}
END_TEST

START_TEST(test17) {
  const char *str = "cos(72+(-log(3+2)*3)-96)/2";
  long double result = 0;
  RPNcalculator(str, &result);

  ck_assert_ldouble_eq_tol(result, 0.285050, EPSILON);
}
END_TEST

START_TEST(test18) {
  const char *str = "-7+15";
  long double result = 0;
  RPNcalculator(str, &result);

  ck_assert_ldouble_eq_tol(result, 8.000000, EPSILON);
}
END_TEST

Suite *s21_calc_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[42m-=CALC=-\033[0m");
  tc_core = tcase_create("CalcCore");

  tcase_add_test(tc_core, test1);
  tcase_add_test(tc_core, test2);
  tcase_add_test(tc_core, test3);
  tcase_add_test(tc_core, test4);
  tcase_add_test(tc_core, test5);
  tcase_add_test(tc_core, test6);
  tcase_add_test(tc_core, test7);
  tcase_add_test(tc_core, test8);
  tcase_add_test(tc_core, test9);
  tcase_add_test(tc_core, test10);
  tcase_add_test(tc_core, test11);
  tcase_add_test(tc_core, test12);
  tcase_add_test(tc_core, test13);
  tcase_add_test(tc_core, test14);
  tcase_add_test(tc_core, test15);
  tcase_add_test(tc_core, test16);
  tcase_add_test(tc_core, test17);
  tcase_add_test(tc_core, test18);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_loan_1) {
  long double result = calculateOverpaymentOnCredit(100000, 108333);
  ck_assert_ldouble_eq_tol(result, 8333.000000, EPSILON);
}
END_TEST

START_TEST(test_loan_2) {
  long double result = calculateMonthlyDifferentiatedPayment(100000, 24);
  ck_assert_ldouble_eq_tol(result, 4166.666667, EPSILON);
}
END_TEST

START_TEST(test_loan_3) {
  long double result = calculateMonthlyAnnuityPayment(100000, 24, 8);
  ck_assert_ldouble_eq_tol(result, 4522.729146, EPSILON);
}
END_TEST

START_TEST(test_loan_4) {
  long double result = calculateTotalAnnuityPayment(4522, 24);
  ck_assert_ldouble_eq_tol(result, 108528, EPSILON);
}
END_TEST

START_TEST(test_loan_5) {
  long double result = calculateTotalDifferentiatedPayment(100000, 24, 8);
  ck_assert_ldouble_eq_tol(result, 108333.333333, EPSILON);
}
END_TEST

Suite *s21_loan_calc_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[42m-=LOAN_CALC=-\033[0m");
  tc_core = tcase_create("LoanCalcCore");

  tcase_add_test(tc_core, test_loan_1);
  tcase_add_test(tc_core, test_loan_2);
  tcase_add_test(tc_core, test_loan_3);
  tcase_add_test(tc_core, test_loan_4);
  tcase_add_test(tc_core, test_loan_5);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_x1) {
  const char *str = "(3.5+x)+sqrt(x)";
  const char *x_value = "4.5678";
  char *new_string = replaceX(str, x_value);
  long double result = 0;
  RPNcalculator(new_string, &result);
  free(new_string);
  ck_assert_ldouble_eq_tol(result, 10.205041, EPSILON);
}
END_TEST

Suite *s21_replace_x_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[42m-=ReplaceX=-\033[0m");
  tc_core = tcase_create("ReplaceXCore");

  tcase_add_test(tc_core, test_x1);

  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(test_deposit_income_no_additional) {
  DepositInfo deposit;
  deposit.depositAmount = 10000.0;
  deposit.depositTerm = 12;
  deposit.interestRate = 15.0;
  deposit.termUnit = 1;        // в месяцах
  deposit.capitalization = 0;  // нет
  deposit.depositFrequency = 0;  // без дополнительных взносов
  deposit.additionalDepositAmount = 0;

  DepositResult result = calculateDepositIncome(deposit);
  ck_assert_double_eq_tol(result.totalAmount, 11479.45, EPSILON2);
  ck_assert_double_eq_tol(result.totalInterest, 1479.45, EPSILON2);
  ck_assert_double_eq_tol(result.tax, 0.0, EPSILON2);
}
END_TEST

START_TEST(test_deposit_income_with_additional) {
  DepositInfo deposit;
  deposit.depositAmount = 10000.0;
  deposit.depositTerm = 12;
  deposit.interestRate = 15.0;
  deposit.termUnit = 1;          // в месяцах
  deposit.capitalization = 2;    // ежемесячно
  deposit.depositFrequency = 3;  // раз в квартал
  deposit.additionalDepositAmount = 100.0;

  DepositResult result = calculateDepositIncome(deposit);
  ck_assert_double_eq_tol(result.totalAmount, 12170.62, EPSILON2);
  ck_assert_double_eq_tol(result.totalInterest, 1689.08, EPSILON2);
  ck_assert_double_eq_tol(result.tax, 0.00, EPSILON2);
}
END_TEST

// Тест для проверки расчета процентов с некорректными данными
START_TEST(test_deposit_income_invalid_data) {
  DepositInfo deposit;
  deposit.depositAmount = 10000.0;
  deposit.depositTerm = 2;
  deposit.interestRate = 15.0;
  deposit.termUnit = 0;          // в месяцах
  deposit.capitalization = 7;    // ежемесячно
  deposit.depositFrequency = 6;  // раз в квартал
  deposit.additionalDepositAmount = 100.0;

  DepositResult result = calculateDepositIncome(deposit);
  ck_assert_double_eq_tol(result.totalAmount, 0, EPSILON2);
  ck_assert_double_eq_tol(result.totalInterest, 0, EPSILON2);
  ck_assert_double_eq_tol(result.tax, 0, EPSILON2);
}
END_TEST

START_TEST(test_deposit_1) {
  DepositInfo deposit;
  deposit.depositAmount = 10000.0;
  deposit.depositTerm = 2;
  deposit.interestRate = 15.0;
  deposit.termUnit = 1;          // в месяцах
  deposit.capitalization = 1;    // ежемесячно
  deposit.depositFrequency = 1;  // раз в квартал
  deposit.additionalDepositAmount = 100.0;

  DepositResult result = calculateDepositIncome(deposit);
  ck_assert_double_eq_tol(result.totalAmount, 10318.44, EPSILON2);
  ck_assert_double_eq_tol(result.totalInterest, 284.01, EPSILON2);
  ck_assert_double_eq_tol(result.tax, 0, EPSILON2);
}
END_TEST

START_TEST(test_deposit_2) {
  DepositInfo deposit;
  deposit.depositAmount = 10000.0;
  deposit.depositTerm = 24;
  deposit.interestRate = 15.0;
  deposit.termUnit = 1;          // в месяцах
  deposit.capitalization = 3;    // ежемесячно
  deposit.depositFrequency = 3;  // раз в квартал
  deposit.additionalDepositAmount = 100.0;

  DepositResult result = calculateDepositIncome(deposit);
  ck_assert_double_eq_tol(result.totalAmount, 14703.19, EPSILON2);
  ck_assert_double_eq_tol(result.totalInterest, 3676.04, EPSILON2);
  ck_assert_double_eq_tol(result.tax, 0, EPSILON2);
}
END_TEST

START_TEST(test_deposit_3) {
  DepositInfo deposit;
  deposit.depositAmount = 10000.0;
  deposit.depositTerm = 24;
  deposit.interestRate = 15.0;
  deposit.termUnit = 1;          // в месяцах
  deposit.capitalization = 4;    // ежемесячно
  deposit.depositFrequency = 4;  // раз в квартал
  deposit.additionalDepositAmount = 100.0;

  DepositResult result = calculateDepositIncome(deposit);
  ck_assert_double_eq_tol(result.totalAmount, 13259.77, EPSILON2);
  ck_assert_double_eq_tol(result.totalInterest, 2565.78, EPSILON2);
  ck_assert_double_eq_tol(result.tax, 0, EPSILON2);
}
END_TEST

START_TEST(test_deposit_4) {
  DepositInfo deposit;
  deposit.depositAmount = 10000.0;
  deposit.depositTerm = 24;
  deposit.interestRate = 15.0;
  deposit.termUnit = 1;          // в месяцах
  deposit.capitalization = 5;    // ежемесячно
  deposit.depositFrequency = 5;  // раз в квартал
  deposit.additionalDepositAmount = 100.0;

  DepositResult result = calculateDepositIncome(deposit);
  ck_assert_double_eq_tol(result.totalAmount, 13960.13, EPSILON2);
  ck_assert_double_eq_tol(result.totalInterest, 3480.54, EPSILON2);
  ck_assert_double_eq_tol(result.tax, 0, EPSILON2);
}
END_TEST

Suite *deposit_calc_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("\033[42m-=DEPOSIT_CALC=-\033[0m");
  tc_core = tcase_create("DepositCalcCore");

  tcase_add_test(tc_core, test_deposit_income_no_additional);
  tcase_add_test(tc_core, test_deposit_income_with_additional);
  tcase_add_test(tc_core, test_deposit_income_invalid_data);
  tcase_add_test(tc_core, test_deposit_1);
  tcase_add_test(tc_core, test_deposit_2);
  tcase_add_test(tc_core, test_deposit_3);
  tcase_add_test(tc_core, test_deposit_4);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int failed = 0;
  Suite *string_tests[] = {s21_calc_suite(), s21_loan_calc_suite(),
                           s21_replace_x_suite(), deposit_calc_suite(), NULL};

  for (int i = 0; string_tests[i] != NULL; i++) {
    SRunner *runner;
    runner = srunner_create(string_tests[i]);
    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

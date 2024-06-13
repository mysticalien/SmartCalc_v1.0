#include "calc.h"

double convertYearsToMonths(double years) { return years * 12; }

long double calculateOverpaymentOnCredit(long double loanAmount,
                                         long double totalPayment) {
  return totalPayment - loanAmount;
}

long double calculateMonthlyDifferentiatedPayment(long double totalPayment,
                                                  double loanTermInMonths) {
  return totalPayment / loanTermInMonths;
}

long double calculateTotalAnnuityPayment(long double monthlyAnnuityPayment,
                                         double loanTermInMonths) {
  return monthlyAnnuityPayment * loanTermInMonths;
}

long double calculateMonthlyAnnuityPayment(long double principal,
                                           double periods,
                                           long double annualInterestRate) {
  long double interest =
      annualInterestRate / (12 * 100);  // Convert interest to monthly decimal
  long double annuityPayment = interest * powl(1 + interest, periods) /
                               (powl(1 + interest, periods) - 1);
  long double monthlyAnnuityPayment = annuityPayment * principal;

  return monthlyAnnuityPayment;
}

long double calculateTotalDifferentiatedPayment(
    long double loanAmount, double loanTermInMonths,
    long double annualInterestRate) {
  long double totalPayment = 0;
  long double interest =
      annualInterestRate / (12 * 100);  // Convert interest to monthly decimal
  int periods = loanTermInMonths;

  for (int month = 1; month <= periods; month++) {
    long double differentiatedPayment =
        loanAmount / periods +
        interest * (loanAmount - (loanAmount * (month - 1)) / periods);
    totalPayment += differentiatedPayment;
  }

  return totalPayment;
}

// int main() {
////    long double principal = 100000.0;
////    double periods = 2.0;
////    long double annualInterestRate = 8.0;
//
//    long double annuityPayment = calculateMonthlyAnnuityPayment(10000, 12, 5);
//
//    printf("%Lf", annuityPayment);
//    return 0;
//}

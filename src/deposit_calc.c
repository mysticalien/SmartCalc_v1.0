//
// Created by mysticalien on 6/12/24.
//
#include <math.h>
#include <stdio.h>

#include "calc.h"

double calculateInterest(double depositAmount, double interestRate,
                         int termInDays, int capitalization) {
  double ratePerPeriod = interestRate / 100.0;

  double totalInterest = 0.0;

  switch (capitalization) {
    case 0:  // Без капитализации
      totalInterest = depositAmount * ratePerPeriod * termInDays / 365.0;
      break;
    case 1:  // Ежедневная капитализация
      totalInterest =
          depositAmount * (pow(1 + ratePerPeriod / 365, termInDays) - 1);
      break;
    case 2:  // Ежемесячная капитализация
      totalInterest =
          depositAmount * (pow(1 + ratePerPeriod / 12, termInDays / 30.0) - 1);
      break;
    case 3:  // Раз в 2 месяца
      totalInterest =
          depositAmount * (pow(1 + ratePerPeriod / 6, termInDays / 60.0) - 1);
      break;
    case 4:  // Ежеквартальная капитализация
      totalInterest =
          depositAmount * (pow(1 + ratePerPeriod / 4, termInDays / 120.0) - 1);
      break;
    case 5:  // Раз в 4 месяца
      totalInterest =
          depositAmount * (pow(1 + ratePerPeriod / 3, termInDays / 120.0) - 1);
      break;
    case 6:  // Полугодовая капитализация
      totalInterest =
          depositAmount * (pow(1 + ratePerPeriod / 2, termInDays / 180.0) - 1);
      break;
    case 7:  // Ежегодная капитализация
      totalInterest =
          depositAmount * (pow(1 + ratePerPeriod, termInDays / 365.0) - 1);
      break;
    default:
      printf("Ошибка: Неверный тип капитализации\n");
      break;
  }

  return totalInterest;
}

double calculateTax(double interestAmount, double untaxableIncome) {
  // Предполагаемый фиксированный налоговый процент 13%
  double taxableIncome = interestAmount - untaxableIncome;
  if (taxableIncome <= 0)
    return 0.0;
  else
    return taxableIncome * 0.13;
}

DepositResult calculateDepositIncome(DepositInfo deposit) {
  DepositResult result = {0};  // Инициализация всех полей нулями

  deposit.additionalDeposits = (deposit.depositFrequency != 0);

  double totalAmount = deposit.depositAmount;
  double totalInterest = 0.0;

  // Установка значения ключевой ставки
  double keyRate = 0.16;

  int termInDays =
      (deposit.termUnit == 0) ? deposit.depositTerm : deposit.depositTerm * 30;

  // Рассчитываем начисленные проценты на основном вкладе
  totalInterest = calculateInterest(totalAmount, deposit.interestRate,
                                    termInDays, deposit.capitalization);

  // Добавляем начисленные проценты на дополнительные взносы, если они есть
  if (deposit.additionalDeposits) {
    int frequency = 0;
    switch (deposit.depositFrequency) {
      case 1:
        frequency = 12;
        break;  // ежемесячно
      case 2:
        frequency = 6;
        break;  // раз в 2 месяца
      case 3:
        frequency = 4;
        break;  // раз в квартал
      case 4:
        frequency = 3;
        break;  // раз в 4 месяца
      case 5:
        frequency = 2;
        break;  // раз в полгода
      case 6:
        frequency = 1;
        break;  // ежегодно
      default:
        return result;  // Возвращаем нулевую структуру в случае ошибки
    }

    // Проверяем, чтобы срок дополнительного взноса был не короче срока
    // основного вклада
    if (termInDays * frequency <= termInDays) {
      return result;  // Возвращаем нулевую структуру в случае ошибки
    } else {
      totalAmount +=
          ((termInDays / 360) * frequency) * deposit.additionalDepositAmount;
    }

    // Рассчитываем начисленные проценты на дополнительные взносы
    double additionalDepositInterest =
        calculateInterest(deposit.additionalDepositAmount, deposit.interestRate,
                          termInDays * frequency, deposit.capitalization);

    // Увеличиваем общую сумму на величину начисленных процентов на
    // дополнительные взносы
    totalAmount += additionalDepositInterest;

    // Добавляем начисленные проценты на дополнительные взносы к общей сумме
    // начисленных процентов
    totalInterest += additionalDepositInterest;
  }

  double untaxableIncome = 1000000.0 * keyRate;
  double tax = calculateTax(totalInterest, untaxableIncome);
  double netInterest = totalInterest - tax;
  totalAmount += netInterest;

  result.totalAmount = totalAmount;
  result.totalInterest = totalInterest;
  result.tax = tax;

  return result;
}

// int main() {
//     DepositInfo deposit;
//
//     printf("Введите сумму вклада: ");
//     scanf("%lf", &deposit.depositAmount);
//
//     printf("Введите срок вклада: ");
//     scanf("%d", &deposit.depositTerm);
//
//     printf("Введите процентную ставку: ");
//     scanf("%lf", &deposit.interestRate);
//
//     printf("Выберите срок в днях (0) или месяцах (1): ");
//     scanf("%d", &deposit.termUnit);
//
//     printf("Капитализация процентов (0 - нет, 1 - ежедневно, 2 - ежемесячно,
//     3 - раз в 2 месяца, 4 - раз в квартал, 5 - раз в 4 месяца, 6 - раз в
//     полгода, 7 - раз в год): "); scanf("%d", &deposit.capitalization);
//
//     printf("Выберите частоту пополнения вклада (0 - нет, 1 - ежемесячно, 2 -
//     раз в 2 месяца, 3 - раз в квартал, 4 - раз в 4 месяца, 5 - раз в полгода,
//     6 - раз в год): "); scanf("%d", &deposit.depositFrequency);
//
//     deposit.additionalDeposits = (deposit.depositFrequency != 0);
////    if (deposit.additionalDeposits) {
////        printf("Введите сумму дополнительного пополнения вклада: ");
////        scanf("%lf", &deposit.additionalDepositAmount);
////    }
//
//    printf("Введите сумму дополнительного пополнения вклада: ");
//    scanf("%lf", &deposit.additionalDepositAmount);
//    DepositResult result = calculateDepositIncome(deposit);
//
//    // Вывод результатов
//    printf("Начисленные проценты: %.2f\n", result.totalInterest);
//    printf("Сумма налога: %.2f\n", result.tax);
//    printf("Сумма на вкладе к концу срока: %.2f\n", result.totalAmount);
//
//    return 0;
//}
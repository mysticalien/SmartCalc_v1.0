#ifndef LOANCALC_H
#define LOANCALC_H

#include <QDialog>
#include <QMessageBox>

extern "C" {
#include "../../calc.h"
}

namespace Ui {
class LoanCalc;
}

class LoanCalc : public QDialog {
  Q_OBJECT

 public:
  explicit LoanCalc(QWidget *parent = nullptr);
  ~LoanCalc();

 private slots:
  void on_totalAmount_editingFinished();

  void on_term_editingFinished();

  void on_Annuity_clicked();

  void on_Differentiated_clicked();

  //    void on_LoanResult_clicked();

  void on_rate_editingFinished();

  void on_years_clicked();

  void on_months_clicked();

 private:
  Ui::LoanCalc *ui;
  long double total_amount;
  double term;
  //    bool annuity_clicked;
  //    bool differ_clicked;
  long double interest_rate;
  bool is_years;
};

#endif  // LOANCALC_H

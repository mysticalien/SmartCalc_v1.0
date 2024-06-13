#include "loancalc.h"

#include <QDoubleValidator>
#include <QIntValidator>
#include <QMessageBox>

#include "ui_loancalc.h"

LoanCalc::LoanCalc(QWidget *parent) : QDialog(parent), ui(new Ui::LoanCalc) {
  ui->setupUi(this);
  is_years = false;
  QIntValidator *intValidator = new QIntValidator(0, 100, this);

  ui->term->setValidator(intValidator);

  QDoubleValidator *doubleValidator = new QDoubleValidator(this);
  ui->totalAmount->setValidator(doubleValidator);
  ui->rate->setValidator(intValidator);
}

LoanCalc::~LoanCalc() { delete ui; }

void LoanCalc::on_totalAmount_editingFinished() {
  total_amount = ui->totalAmount->text().toDouble();
}

void LoanCalc::on_term_editingFinished() { term = ui->term->text().toDouble(); }

void LoanCalc::on_rate_editingFinished() {
  interest_rate = ui->rate->text().toDouble();
}

void LoanCalc::on_Annuity_clicked() {
  ui->Overpayment->setText("00.00");
  ui->totalPayment->setText("00.00");
  ui->Overpayment->setText("00.00");
  if (!ui->totalAmount->text().isEmpty() && !ui->term->text().isEmpty() &&
      !ui->rate->text().isEmpty() &&
      (ui->months->isChecked() ^ ui->years->isChecked())) {
    interest_rate = ui->rate->text().toDouble();
    term = ui->term->text().toDouble();
    total_amount = ui->totalAmount->text().toDouble();
    if (is_years) {
      term = convertYearsToMonths(term);
    }
    long double monthlyPayment =
        calculateMonthlyAnnuityPayment(total_amount, term, interest_rate);
    ui->monthlyPayment->setText(QString::number(monthlyPayment, 'g', 7));
    long double total_payment =
        calculateTotalAnnuityPayment(monthlyPayment, term);
    ui->totalPayment->setText(QString::number(total_payment, 'g', 7));
    long double overpayment =
        calculateOverpaymentOnCredit(total_amount, total_payment);
    ui->Overpayment->setText(QString::number(overpayment, 'g', 7));
  } else {
    ui->monthlyPayment->setText("Error: Not all fields filled");
    ui->totalPayment->setText("Error: Not all fields filled");
    ui->Overpayment->setText("Error: Not all fields filled");
    //    QMessageBox::warning(this, "Not all filled", "Please fill in all
    //    fields.");
  }
}

void LoanCalc::on_Differentiated_clicked() {
  ui->Overpayment->setText("00.00");
  ui->totalPayment->setText("00.00");
  ui->Overpayment->setText("00.00");
  if (!ui->totalAmount->text().isEmpty() && !ui->term->text().isEmpty() &&
      !ui->rate->text().isEmpty() &&
      (ui->months->isChecked() || ui->years->isChecked())) {
    interest_rate = ui->rate->text().toDouble();
    term = ui->term->text().toDouble();
    total_amount = ui->totalAmount->text().toDouble();
    if (is_years) {
      term = convertYearsToMonths(term);
    }
    long double monthlyPayment =
        calculateMonthlyDifferentiatedPayment(total_amount, term);
    ui->monthlyPayment->setText(QString::number(monthlyPayment, 'g', 7));
    long double total_payment =
        calculateTotalDifferentiatedPayment(total_amount, term, interest_rate);
    ui->totalPayment->setText(QString::number(total_payment, 'g', 7));
    long double overpayment =
        calculateOverpaymentOnCredit(total_amount, total_payment);
    ui->Overpayment->setText(QString::number(overpayment, 'g', 7));
  } else {
    ui->monthlyPayment->setText("Error: Not all fields filled");
    ui->totalPayment->setText("Error: Not all fields filled");
    ui->Overpayment->setText("Error: Not all fields filled");
    //    QMessageBox::warning(this, "Not all filled", "Please fill in all
    //    fields.");
  }
}

void LoanCalc::on_years_clicked() { is_years = true; }

void LoanCalc::on_months_clicked() { is_years = false; }

#include "depositcalc.h"

#include "ui_depositcalc.h"

depositcalc::depositcalc(QWidget *parent)
    : QDialog(parent), ui(new Ui::depositcalc) {
  ui->setupUi(this);
  QIntValidator *intValidator = new QIntValidator(0, 100, this);

  ui->lineEdit_deposit_term->setValidator(intValidator);

  QDoubleValidator *doubleValidator = new QDoubleValidator(this);
  ui->lineEdit_deposit_amount->setValidator(doubleValidator);
  ui->lineEdit_rate->setValidator(doubleValidator);
  ui->lineEdit_sum->setValidator(doubleValidator);
}

depositcalc::~depositcalc() { delete ui; }

void depositcalc::on_lineEdit_deposit_amount_editingFinished() {
  depositAmount = ui->lineEdit_deposit_amount->text().toDouble();
}

void depositcalc::on_lineEdit_deposit_term_editingFinished() {
  depositTerm = ui->lineEdit_deposit_term->text().toDouble();
}

void depositcalc::on_lineEdit_rate_editingFinished() {
  interestRate = ui->lineEdit_rate->text().toDouble();
}

void depositcalc::on_comboBox_term_currentIndexChanged(int index) {
  termUnit = index;
}

void depositcalc::on_comboBox_currency_currentIndexChanged(int index) {
  currency = index;
}

void depositcalc::on_lineEdit_sum_editingFinished() {
  additionalDepositAmount = ui->lineEdit_sum->text().toDouble();
}

void depositcalc::on_comboBox_replenishment_currentIndexChanged(int index) {
  depositFrequency = index;
}

void depositcalc::on_comboBox_capitalization_currentIndexChanged(int index) {
  capitalization = index;
}

void depositcalc::on_pushButton_result_clicked() {
  ui->label_interest2->setText("0.00");
  ui->label_taxAmount2->setText("0.00");
  ui->label_total2->setText("0.00");

  if (!ui->lineEdit_deposit_amount->text().isEmpty() &&
      !ui->lineEdit_deposit_term->text().isEmpty() &&
      !ui->lineEdit_rate->text().isEmpty() &&
      (ui->comboBox_term->currentIndex() != -1) &&
      (ui->comboBox_currency->currentIndex() != -1) &&
      (ui->comboBox_replenishment->currentIndex() != -1) &&
      (ui->comboBox_capitalization->currentIndex() != -1)) {
    DepositInfo deposit;
    deposit.depositAmount = depositAmount;
    deposit.depositTerm = depositTerm;
    deposit.interestRate = interestRate;
    deposit.termUnit = termUnit;
    deposit.capitalization = capitalization;
    deposit.currency = currency;
    deposit.depositFrequency = depositFrequency;
    if (depositFrequency != 0) {
      deposit.additionalDeposits = 1;
    } else {
      deposit.additionalDeposits = 0;
    }
    if (ui->lineEdit_sum->text().isEmpty()) {
      deposit.additionalDepositAmount = 0;
    } else {
      deposit.additionalDepositAmount = additionalDepositAmount;
    }
    DepositResult result = calculateDepositIncome(deposit);
    ui->label_interest2->setText(QString::number(result.totalInterest, 'f', 2));
    ui->label_taxAmount2->setText(QString::number(result.tax, 'f', 2));
    ui->label_total2->setText(QString::number(result.totalAmount, 'f', 2));
  } else {
    //      QMessageBox::warning(this, "Not all filled", "Please fill in all
    //      fields.");
    ui->label_interest2->setText("Error: Not all fields filled");
    ui->label_taxAmount2->setText("Error: Not all fields filled");
    ui->label_total2->setText("Error: Not all fields filled");
  }
}

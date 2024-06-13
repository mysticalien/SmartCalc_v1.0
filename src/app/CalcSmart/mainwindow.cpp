#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  xFlag = false;
  currentExpression = "";
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::x_set() { return !ui->x_input->text().isEmpty(); }

void MainWindow::updateExpressionLabel() {
  ui->expressionLabel->setText(currentExpression);
}

void MainWindow::addToCurrentExpression(const QString &textToAdd) {
  currentExpression += textToAdd;
  updateExpressionLabel();
}

void MainWindow::on_pushButton_1_clicked() { addToCurrentExpression("1"); }

void MainWindow::on_pushButton_2_clicked() { addToCurrentExpression("2"); }

void MainWindow::on_pushButton_3_clicked() { addToCurrentExpression("3"); }

void MainWindow::on_pushButton_0_clicked() { addToCurrentExpression("0"); }

void MainWindow::on_pushButton_dot_clicked() { addToCurrentExpression("."); }

void MainWindow::on_pushButton_plus_clicked() { addToCurrentExpression("+"); }

void MainWindow::on_pushButton_minus_clicked() { addToCurrentExpression("-"); }

void MainWindow::on_pushButton_mul_clicked() { addToCurrentExpression("*"); }

void MainWindow::on_pushButton_div_clicked() { addToCurrentExpression("/"); }

void MainWindow::on_pushButton_bracket2_clicked() {
  addToCurrentExpression(")");
}

void MainWindow::on_pushButton_bracket1_clicked() {
  addToCurrentExpression("(");
}

void MainWindow::on_pushButton_log_clicked() { addToCurrentExpression("log("); }

void MainWindow::on_pushButton_ln_clicked() { addToCurrentExpression("ln("); }

void MainWindow::on_pushButton_cos_clicked() { addToCurrentExpression("cos("); }

void MainWindow::on_pushButton_sin_clicked() { addToCurrentExpression("sin("); }

void MainWindow::on_pushButton_tan_clicked() { addToCurrentExpression("tan("); }

void MainWindow::on_pushButton_acos_clicked() {
  addToCurrentExpression("acos(");
}

void MainWindow::on_pushButton_asin_clicked() {
  addToCurrentExpression("asin(");
}

void MainWindow::on_pushButton_atan_clicked() {
  addToCurrentExpression("atan(");
}

void MainWindow::on_pushButton_sqrt_clicked() {
  addToCurrentExpression("sqrt(");
}

void MainWindow::on_pushButton_mod_clicked() { addToCurrentExpression("mod("); }

void MainWindow::on_pushButton_pow_clicked() { addToCurrentExpression("^"); }

void MainWindow::on_pushButton_4_clicked() { addToCurrentExpression("4"); }

void MainWindow::on_pushButton_5_clicked() { addToCurrentExpression("5"); }

void MainWindow::on_pushButton_6_clicked() { addToCurrentExpression("6"); }

void MainWindow::on_pushButton_7_clicked() { addToCurrentExpression("7"); }

void MainWindow::on_pushButton_8_clicked() { addToCurrentExpression("8"); }

void MainWindow::on_pushButton_9_clicked() { addToCurrentExpression("9"); }

void MainWindow::on_pushButton_result_clicked() {
  //    x = ui->x_input->text();
  std::string str = currentExpression.toStdString();
  bool flag = true;
  if (!isValidExpression(str.c_str())) {
    flag = false;
  }
  //    std::string x = currentExpression.toStdString();
  //    const char *cstr = str.c_str();

  if ((xFlag == false || (x_set() && xFlag == true)) && flag == true) {
    long double result = 0;
    if (xFlag == true) {
      x = ui->x_input->text();
      std::string x_value = x.toStdString();
      const char *cx_value = x_value.c_str();
      char *newExpression = replaceX(str.c_str(), cx_value);
      if (RPNcalculator(newExpression, &result) == 0) {
        ui->expressionLabel->setText(QString::number(result, 'g', 7));
      } else {
        ui->expressionLabel->setText("Error");
      }
      free(newExpression);
    } else {
      if (RPNcalculator(str.c_str(), &result) == 0) {
        ui->expressionLabel->setText(QString::number(result, 'g', 7));
      } else {
        ui->expressionLabel->setText("Error");
      }
    }
  } else {
    ui->expressionLabel->setText("Error");
  }
}

void MainWindow::on_pushButton_x_clicked() {
  addToCurrentExpression("x");
  xFlag = true;
}

void MainWindow::on_pushButton_ac_clicked() {
  currentExpression.clear();
  ui->expressionLabel->clear();
}

void MainWindow::on_pushButton_ce_clicked() {
  if (!currentExpression.isEmpty()) {
    currentExpression.chop(1);  // Удаляем последний символ из currentExpression
    updateExpressionLabel();
  }
}

void MainWindow::on_pushButton_graph_clicked() {
  std::string str = currentExpression.toStdString();
  const char *cstr = str.c_str();
  Plot plotDialog;
  plotDialog.makePlot(cstr);
  plotDialog.exec();
}

void MainWindow::on_pushButton_loan_clicked() {
  // Создание экземпляра класса LoanCalc
  LoanCalc *loanCalcWindow = new LoanCalc(this);

  // Отображение окна
  loanCalcWindow->show();
}

void MainWindow::on_pushButton_deposit_clicked() {
  // Создание экземпляра класса DepositCalc
  depositcalc *depositCalcWindow = new depositcalc(this);

  // Отображение окна
  depositCalcWindow->show();
}

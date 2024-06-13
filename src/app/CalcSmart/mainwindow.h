#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegularExpressionValidator>
#include <QString>
#include <QVector>

#include "depositcalc.h"
#include "loancalc.h"
#include "plot.h"

extern "C" {
#include "../../calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_1_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

  //    void connect_slots();

  void on_pushButton_0_clicked();

  void on_pushButton_dot_clicked();

  //    void on_pushButton_result_clicked();

  void on_pushButton_plus_clicked();

  void on_pushButton_minus_clicked();

  void on_pushButton_mul_clicked();

  void on_pushButton_div_clicked();

  void on_pushButton_bracket2_clicked();

  void on_pushButton_bracket1_clicked();

  void on_pushButton_log_clicked();

  void on_pushButton_ln_clicked();

  void on_pushButton_cos_clicked();

  void on_pushButton_sin_clicked();

  void on_pushButton_tan_clicked();

  void on_pushButton_acos_clicked();

  void on_pushButton_asin_clicked();

  void on_pushButton_atan_clicked();

  void on_pushButton_sqrt_clicked();

  void on_pushButton_mod_clicked();

  void on_pushButton_pow_clicked();

  void updateExpressionLabel();

  void addToCurrentExpression(const QString &textToAdd);

  void on_pushButton_4_clicked();

  void on_pushButton_5_clicked();

  void on_pushButton_6_clicked();

  void on_pushButton_7_clicked();

  void on_pushButton_8_clicked();

  void on_pushButton_9_clicked();

  void on_pushButton_result_clicked();

  void on_pushButton_x_clicked();

  void on_pushButton_ac_clicked();

  void on_pushButton_ce_clicked();

  void on_pushButton_graph_clicked();

  void on_pushButton_loan_clicked();

  void on_pushButton_deposit_clicked();

 private:
  Ui::MainWindow *ui;
  //    QRegularExpressionValidator x_input_validator;
  //    QRegularExpressionValidator input_validator;
  QString currentExpression;
  bool x_set();
  bool xFlag;
  QString x;
  //    Plot *plotDialog;

 signals:
  void makePlot(char *);
};
#endif  // MAINWINDOW_H

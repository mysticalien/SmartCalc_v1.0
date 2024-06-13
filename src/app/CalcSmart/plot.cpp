#include "plot.h"

#include <QIntValidator>

#include "ui_plot.h"

Plot::Plot(QWidget *parent) : QDialog(parent), ui(new Ui::Plot) {
  ui->setupUi(this);
  QIntValidator *intValidator = new QIntValidator(-1000000, 1000000, this);

  ui->xmin->setValidator(intValidator);
  ui->xmax->setValidator(intValidator);
  ui->ymin->setValidator(intValidator);
  ui->ymax->setValidator(intValidator);
}

Plot::~Plot() { delete ui; }

void Plot::makePlot(const char *str) {
  strncpy(expr, str, 300);
  minX = ui->xmin->text().toDouble();
  maxX = ui->xmax->text().toDouble();
  minY = ui->ymin->text().toDouble();
  maxY = ui->ymax->text().toDouble();
  renderPlot();
}

void Plot::renderPlot() {
  bool flag = true;
  if (!isValidExpression(expr)) {
    flag = false;
  }
  ui->MyPlot->clearGraphs();
  ui->MyPlot->clearItems();
  ui->MyPlot->clearPlottables();
  step = 0.1;

  ui->MyPlot->xAxis->setRange(minX, maxX);
  ui->MyPlot->yAxis->setRange(minY, maxY);
  N = (maxX - minX) / step + 2;
  if (N > 1000000) {
    N = 1000000;
  }

  for (int i = 0; i < N; i++) {
    long double result = 0;
    long double value = minX + i * step;
    char *newExpression = replaceX(expr, std::to_string(value).c_str());

    if (RPNcalculator(newExpression, &result) == 0) {
      vectorX.push_back(value);
      vectorY.push_back(result);
    }

    free(newExpression);
  }

  if (flag == true) {
    ui->MyPlot->addGraph();
    ui->MyPlot->graph(0)->setData(vectorX, vectorY);

    ui->MyPlot->xAxis->setLabel("X-axis");
    ui->MyPlot->yAxis->setLabel("Y-axis");

    ui->MyPlot->xAxis->grid()->setVisible(true);
    ui->MyPlot->yAxis->grid()->setVisible(true);

    ui->MyPlot->replot();
  }
}

void Plot::on_xmin_editingFinished() {
  minX = ui->xmin->text().toDouble();
  renderPlot();
}

void Plot::on_xmax_editingFinished() {
  maxX = ui->xmax->text().toDouble();
  renderPlot();
}

void Plot::on_ymin_editingFinished() {
  minY = ui->ymin->text().toDouble();
  renderPlot();
}

void Plot::on_ymax_editingFinished() {
  maxY = ui->ymax->text().toDouble();
  renderPlot();
}

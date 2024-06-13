#ifndef PLOT_H
#define PLOT_H

#include <QDialog>

extern "C" {
#include "../../calc.h"
}

namespace Ui {
class Plot;
}

class Plot : public QDialog {
  Q_OBJECT

 public:
  explicit Plot(QWidget *parent = nullptr);
  ~Plot();
  void makePlot(const char *str);

 private slots:
  //    void makePlot(const char *str);
  void on_xmin_editingFinished();

  void on_xmax_editingFinished();

  void on_ymin_editingFinished();

  void on_ymax_editingFinished();

 private:
  Ui::Plot *ui;
  char expr[300];
  double minX, maxX, minY, maxY;
  double step, tempX;
  QVector<double> vectorX, vectorY;
  int N;
  void renderPlot();
  void addScaleLabel();
};

#endif  // PLOT_H

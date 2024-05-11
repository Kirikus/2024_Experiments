#ifndef HISTOGRAM_2D_H
#define HISTOGRAM_2D_H

#include "abstractplotmodel.h"
#include "ui_options_histogram_2d.h"

class Histogram2D : public AbstractPlotModel {
  Q_OBJECT
 public:
  Histogram2D() { setBackground(QBrush(QColor("#FFFF00"))); }

  void Draw() override;
  void Options() override;

  static void SetDarkTheme(QCustomPlot* plot) {
    plot->setBackground(QBrush(QColor("#FFFF00")));
    // plot->yAxis->setTickLabelColor(Qt::white);
    // plot->xAxis->setTickLabelColor(Qt::white);
    plot->replot();
  }
  static void SetLightTheme(QCustomPlot* plot) {
    plot->setBackground(QBrush(QColor("#FFFF00")));
    // plot->yAxis->setTickLabelColor(Qt::black);
    // plot->xAxis->setTickLabelColor(Qt::black);
    plot->replot();
  }

 private:
  int x_ = 0;
  int y_ = 0;
  double granularity_ = 10;
  int index_x_ = 0;
  int index_y_ = 0;
  int index_granularity_ = 0;
};

class OptionsHistogram2D : public QDialog {
  Q_OBJECT

 public:
  OptionsHistogram2D(int index_x_, int index_y_, int index_granularity_);
  ~OptionsHistogram2D();

  int choose_AxisX();
  int choose_AxisY();
  double choose_granularity();

  Ui::DialogHistogram2D *get() { return ui; }

 private:
  Ui::DialogHistogram2D *ui;
};

#endif  // HISTOGRAM_2D_H

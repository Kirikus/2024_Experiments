#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "abstractplotmodel.h"
#include "ui_options_histogram.h"

class Histogram : public AbstractPlotModel {
  Q_OBJECT
 public:
  Histogram() {}

  void Draw() override;
  void Options() override;

 private:
  int var_ = 0;
  int granularity_ = 10;
};

class OptionsHistogram : public QDialog {
  Q_OBJECT

 public:
  OptionsHistogram(QWidget *parent = nullptr);
  ~OptionsHistogram();

  int choose_variable();
  int choose_granularity();

 private:
  Ui::DialogHistogram *ui;
};

#endif  // HISTOGRAM_H

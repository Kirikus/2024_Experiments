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
  int index_x_ = 0;
  int index_granularity_ = 0;
};

class OptionsHistogram : public QDialog {
  Q_OBJECT

 public:
  OptionsHistogram(int index_x_, int index_granularity_,  QWidget *parent = nullptr);
  ~OptionsHistogram();

  int choose_variable();
  int choose_granularity();

  Ui::DialogHistogram *get() { return ui; }

 private:
  Ui::DialogHistogram *ui;
};

#endif  // HISTOGRAM_H

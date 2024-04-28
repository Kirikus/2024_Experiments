#ifndef OPTIONS_HISTOGRAM_H
#define OPTIONS_HISTOGRAM_H

#include "ui_options_histogram.h"

class OptionsHistogram : public QDialog {
  Q_OBJECT

 public:
  OptionsHistogram(QWidget *parent = nullptr);
  ~OptionsHistogram();

  int choose_variable();
  int choose_column_size();

 private:
  Ui::DialogHistogram *ui;
};

#endif  // OPTIONS_HISTOGRAM_H

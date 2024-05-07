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

 private:
  int x_ = 0;
  int y_ = 0;
  int square_size_ = 1;
};

class OptionsHistogram2D : public QDialog {
  Q_OBJECT

 public:
  OptionsHistogram2D(QWidget *parent = nullptr);
  ~OptionsHistogram2D();

  int choose_AxisX();
  int choose_AxisY();
  int choose_square_size();

 private:
  Ui::DialogHistogram2D *ui;
};

#endif  // HISTOGRAM_2D_H

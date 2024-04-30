#ifndef OPTIONS_SCATTER_2D_H
#define OPTIONS_SCATTER_2D_H

#include "ui_options_scatter_2d.h"

class OptionsScatter2D : public QDialog {
  Q_OBJECT

 public:
  OptionsScatter2D(QWidget *parent = nullptr);
  ~OptionsScatter2D();

  int choose_AxisX();
  int choose_AxisY();

 private:
  Ui::DialogScattetPlot2D *ui;
};

#endif  // OPTIONS_SCATTER_2D_H

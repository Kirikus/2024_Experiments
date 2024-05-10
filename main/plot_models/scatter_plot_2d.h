#ifndef SCATTER_PLOT_2D_H
#define SCATTER_PLOT_2D_H

#include "abstractplotmodel.h"
#include "ui_options_scatter_2d.h"

class ScatterPlot2D : public AbstractPlotModel {
  Q_OBJECT
 public:
  ScatterPlot2D() {}

  void Draw() override;
  void Options() override;

 private:
  int x_ = 0;
  int y_ = 0;
  int index_x_ = 0;
  int index_y_ = 0;
};

class OptionsScatter2D : public QDialog {
  Q_OBJECT

 public:
  OptionsScatter2D(int index_x_, int index_y_);
  ~OptionsScatter2D();

  int choose_AxisX();
  int choose_AxisY();

  Ui::DialogScattetPlot2D *get() { return ui; }

 private:
  Ui::DialogScattetPlot2D *ui;
};

#endif  // SCATTER_PLOT_2D_H

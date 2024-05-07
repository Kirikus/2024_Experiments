#ifndef SCATTER_PLOT_2D_H
#define SCATTER_PLOT_2D_H

#include "abstractplotmodel.h"

class ScatterPlot2D : public AbstractPlotModel {
  Q_OBJECT
 public:
  ScatterPlot2D() {}

  void Draw() override;
  void Options() override;

 private:
  int x_ = 0;
  int y_ = 0;
};

#endif  // SCATTER_PLOT_2D_H

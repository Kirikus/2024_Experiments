#ifndef SCATTER_PLOT_2D_H
#define SCATTER_PLOT_2D_H

#include "abstractplotmodel.h"

class ScatterPlot2D : public AbstractPlotModel {
  Q_OBJECT
 public:
  ScatterPlot2D() {}

  void Draw() override;

  void set(int x0, int y0) {
    x = x0;
    y = y0;
  }

 private:
  int x = 0;
  int y = 0;
};

#endif  // SCATTER_PLOT_2D_H

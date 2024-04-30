#ifndef SCATTER_PLOT_H
#define SCATTER_PLOT_H

#include "qcustomplot.h"

class ScatterPlot : public QCustomPlot {
  Q_OBJECT
 public:
  ScatterPlot() {}

  void Draw();
};

#endif  // SCATTER_PLOT_H

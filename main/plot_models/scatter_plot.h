#ifndef SCATTER_PLOT_H
#define SCATTER_PLOT_H

#include "abstractplotmodel.h"

class ScatterPlot : public AbstractPlotModel {
  Q_OBJECT
 public:
  ScatterPlot() {}

  void Draw() override;
};

#endif  // SCATTER_PLOT_H

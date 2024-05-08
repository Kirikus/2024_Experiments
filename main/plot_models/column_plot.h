#ifndef COLUMN_PLOT_H
#define COLUMN_PLOT_H

#include "abstractplotmodel.h"

class ColumnPlot : public AbstractPlotModel {
  Q_OBJECT
 public:
  ColumnPlot() {}

  virtual void Draw() override;
};

#endif  // COLUMN_PLOT_H

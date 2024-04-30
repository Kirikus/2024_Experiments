#ifndef COLUMN_PLOT_H
#define COLUMN_PLOT_H

#include "qcustomplot.h"

class ColumnPlot : public QCustomPlot {
  Q_OBJECT
 public:
  ColumnPlot() {}

  void Draw();
};

#endif  // COLUMN_PLOT_H

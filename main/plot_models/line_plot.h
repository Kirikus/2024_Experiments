#ifndef LINE_PLOT_H
#define LINE_PLOT_H

#include "qcustomplot.h"

class LinePlot : public QCustomPlot {
  Q_OBJECT
 public:
  LinePlot() {}

  void Draw();
};

#endif  // LINE_PLOT_H

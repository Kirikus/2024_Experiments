#ifndef HISTOGRAM_2D_H
#define HISTOGRAM_2D_H

#include "qcustomplot.h"

class Histogram2D : public QCustomPlot {
  Q_OBJECT
 public:
  Histogram2D() {}

  void Draw();

  void set(int x0, int y0, int square_size0) {
    x = x0;
    y = y0;
    square_size = square_size0;
  }

 private:
  int x = 0;
  int y = 0;
  int square_size = 1;
};

#endif  // HISTOGRAM_2D_H

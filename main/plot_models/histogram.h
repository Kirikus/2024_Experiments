#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "qcustomplot.h"

class Histogram : public QCustomPlot {
  Q_OBJECT
 public:
  Histogram() {}

  void Draw();

  void set(int var0, int column_size0) {
      var = var0;
      column_size = column_size0;
  }

 private:
  int var = 0;
  int column_size = 1;
};

#endif  // HISTOGRAM_H

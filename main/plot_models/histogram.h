#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "abstractplotmodel.h"

class Histogram : public AbstractPlotModel {
  Q_OBJECT
 public:
  Histogram() {}

  void Draw() override;

  void set(int var0, int column_size0) {
      var = var0;
      column_size = column_size0;
  }

 private:
  int var = 0;
  int column_size = 1;
};

#endif  // HISTOGRAM_H

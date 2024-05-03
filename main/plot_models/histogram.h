#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "abstractplotmodel.h"

class Histogram : public AbstractPlotModel {
  Q_OBJECT
 public:
  Histogram() {}

  void Draw() override;

  void set(int var0, int column_size0) {
      var_ = var0;
      column_size_ = column_size0;
  }

 private:
  int var_ = 0;
  int column_size_ = 1;
};

#endif  // HISTOGRAM_H

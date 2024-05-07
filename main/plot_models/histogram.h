#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "abstractplotmodel.h"

class Histogram : public AbstractPlotModel {
  Q_OBJECT
 public:
  Histogram() {}

  void Draw() override;
  void Options() override;

 private:
  int var_ = 0;
  int column_size_ = 1;
};

#endif  // HISTOGRAM_H

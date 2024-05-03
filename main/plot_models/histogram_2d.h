#ifndef HISTOGRAM_2D_H
#define HISTOGRAM_2D_H

#include "abstractplotmodel.h"
#include <iostream>

class Histogram2D : public AbstractPlotModel {
  Q_OBJECT
 public:
  Histogram2D() {}

  void Draw() override;

  void set(int x0, int y0, int square_size0) {
    std::cout << x0 << ' ' << y0 << '\n';
    x_ = x0;
    y_ = y0;
    square_size_ = square_size0;
  }

 private:
  int x_ = 0;
  int y_ = 0;
  int square_size_ = 1;
};

#endif  // HISTOGRAM_2D_H

#ifndef HISTOGRAM_2D_H
#define HISTOGRAM_2D_H

#include "abstractplotmodel.h"

class Histogram2D : public AbstractPlotModel {
  Q_OBJECT
 public:
  Histogram2D() { setBackground(QBrush(QColor("#FFFF00"))); }

  void Draw() override;
  void Options() override;

 private:
  int x_ = 0;
  int y_ = 0;
  int square_size_ = 1;
};

#endif  // HISTOGRAM_2D_H

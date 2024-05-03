#ifndef ABSTRACTPLOTMODEL_H
#define ABSTRACTPLOTMODEL_H

#include "qcustomplot.h"

class AbstractPlotModel : public QCustomPlot {
  Q_OBJECT
 public:

  virtual void Draw() = 0;

};

#endif  // ABSTRACTPLOTMODEL_H

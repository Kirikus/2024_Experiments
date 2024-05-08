#ifndef LINE_PLOT_H
#define LINE_PLOT_H

#include "abstractplotmodel.h"

class LinePlot : public AbstractPlotModel {
  Q_OBJECT
 public:
  LinePlot() {}

  virtual void Draw() override;
};

#endif  // LINE_PLOT_H

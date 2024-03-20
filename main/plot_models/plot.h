#ifndef PLOT_H
#define PLOT_H

#include "../../lib/manager.h"
#include "../../qcustomplot_lib/qcustomplot.h"
#include "QString"
#include "QTabWidget"

class Plot : public QWidget {
  Q_OBJECT
 public:
  void setManager();
  virtual void draw(QCustomPlot*) = 0;
  virtual void setOptions() = 0;
};

class ScatterPlot : public Plot {
  Q_OBJECT
 private:
  QString title;
  QString X_axisname;
  QString Y_axisname;

 public:
  void draw(QCustomPlot*) override;
  void setOptions() override;
};

#endif  // PLOT_H

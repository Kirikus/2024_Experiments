#ifndef PLOT_H
#define PLOT_H

#include "../qcustomplot_lib/qcustomplot.h"
#include "QString"
#include "QTabWidget"
#include "manager.h"

class Plot {
  lib::Manager PlotManager;

 public:
  void setManager();
  virtual void draw() const = 0;
  virtual void setOptions() = 0;
};

class ChoicePlot : public Plot {
 private:
  lib::Manager PlotManager;
  QTabWidget plots;

 public:
  virtual void draw() const = 0;
  virtual void setOptions() = 0;
};

class ScatterPlot : public Plot {
 private:
  lib::Manager PlotManager;
  QString title;
  QString X_axisname;
  QString Y_axisname;

 public:
  void draw() const override;
  void setOptions() override;
};

class HistogramPlot : public Plot {
 private:
  lib::Manager PlotManager;
  QString title;
  QString X_axisname;
  QString Y_axisname;
  int bin_count;

 public:
  void draw() const override;
  void setOptions() override;
};

class TwoDimScatterPlot : public Plot {
 private:
  lib::Manager PlotManager;
  QString title;
  QString X_axisname;
  QString Y_axisname;
  int xVariable;
  int yVariable;

 public:
  void draw() const override;
  void setOptions() override;
};

class TwoDimColormapPlot : public Plot {
 private:
  lib::Manager PlotManager;
  QString title;
  QString X_axisname;
  QString Y_axisname;
  int bin_count;
  int xVariable;
  int yVariable;

 public:
  void draw() const override;
  void setOptions() override;
};

#endif  // PLOT_H

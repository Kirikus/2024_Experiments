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

class LinePlot : public Plot {
  Q_OBJECT
 private:
  std::vector<std::vector<int>> colors{
      {244, 202, 22}, {240, 116, 39}, {235, 76, 66},  {204, 57, 123},
      {148, 87, 235}, {49, 140, 231}, {32, 178, 170}, {80, 200, 120}};
  enum color {
    yellow,
    orange,
    red,
    fuchsia_purple,
    purple,
    blue,
    light_sea_green,
    green
  };
  QString title;
  QString X_axisname;
  QString Y_axisname;

 public:
  void draw(QCustomPlot*) override;
  void setOptions() override;
};

#endif  // PLOT_H

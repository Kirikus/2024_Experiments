#ifndef ABSTRACTPLOTMODEL_H
#define ABSTRACTPLOTMODEL_H

#include "QString"
#include "QTabWidget"
#include "manager/manager.h"
#include "qcustomplot.h"

class AbstractPlotModel : public QCustomPlot {
  Q_OBJECT
 public:

  virtual void Draw() = 0;
  virtual void Options() = 0;

  AbstractPlotModel(QCustomPlot* parent = nullptr) : QCustomPlot(parent) {}

  static void Zoom(QCustomPlot* plot) {
    plot->rescaleAxes();
    plot->replot();
  }

  static void SetDarkTheme(QCustomPlot* plot) {
    plot->setBackground(QBrush(QColor("#454545")));
    plot->yAxis->setTickLabelColor(Qt::white);
    plot->xAxis->setTickLabelColor(Qt::white);
    plot->replot();
  }
  static void SetLightTheme(QCustomPlot* plot) {
    plot->setBackground(QBrush(QColor("#ffffff")));
    plot->yAxis->setTickLabelColor(Qt::black);
    plot->xAxis->setTickLabelColor(Qt::black);
    plot->replot();
  }

  enum Types {
    LinePlot = 0,
    ScatterPlot,
    ColumnPlot,
    Histogram,
    ScatterPlot2D,
    Histogram2D,
  };
};

#endif  // ABSTRACTPLOTMODEL_H

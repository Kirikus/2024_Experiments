#ifndef ABSTRACTPLOTMODEL_H
#define ABSTRACTPLOTMODEL_H

#include "QString"
#include "QTabWidget"
#include "manager.h"
#include "qcustomplot.h"

class AbstractPlotModel : public QCustomPlot {
  Q_OBJECT
 public:
  AbstractPlotModel(QCustomPlot* parent = nullptr) : QCustomPlot(parent) {}

  virtual void Draw() = 0;

  static void Rescale(QCustomPlot* plot) {
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
};

#endif  // ABSTRACTPLOTMODEL_H

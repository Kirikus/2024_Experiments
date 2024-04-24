#ifndef ABSTRACTPLOTMODEL_H
#define ABSTRACTPLOTMODEL_H

#include "QString"
#include "QTabWidget"
#include "manager.h"
#include "qcustomplot.h"

class AbstractPlotModel : public QWidget {
  Q_OBJECT
 public:
  AbstractPlotModel(QWidget* parent = nullptr) : QWidget(parent) {}

  virtual void Draw(QCustomPlot*) = 0;
  virtual void SetOptions() = 0;
  static void SetDarkTheme(QCustomPlot* plot) {
    plot->setBackground(QBrush(QColor("#454545")));
    plot->yAxis->setTickLabelColor(Qt::white);
    plot->xAxis->setTickLabelColor(Qt::white);
  }
  static void SetLightTheme(QCustomPlot* plot) {
    plot->setBackground(QBrush(QColor("#ffffff")));
    plot->yAxis->setTickLabelColor(Qt::black);
    plot->xAxis->setTickLabelColor(Qt::black);
  }

};

#endif  // ABSTRACTPLOTMODEL_H

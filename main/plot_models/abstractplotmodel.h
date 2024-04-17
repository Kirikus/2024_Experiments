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
};

#endif  // ABSTRACTPLOTMODEL_H

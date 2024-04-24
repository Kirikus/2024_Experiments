#ifndef SCATTER_PLOT_H
#define SCATTER_PLOT_H

#include "abstractplotmodel.h"

class ScatterPlot : public AbstractPlotModel {
  Q_OBJECT
 public:
  ScatterPlot(QString x_label, QString y_label, QString title = "",
              QWidget* parent = nullptr)
      : AbstractPlotModel(parent),
        x_label(x_label),
        y_label(y_label),
        title(title) {}

  void Draw(QCustomPlot*);

 private:
  QString x_label;
  QString y_label;
  QString title;
};

#endif  // SCATTER_PLOT_H

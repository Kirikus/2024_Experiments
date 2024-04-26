#ifndef HISTOGRAM_2D_H
#define HISTOGRAM_2D_H

#include "abstractplotmodel.h"

class Histogram2D : public AbstractPlotModel {
  Q_OBJECT
 public:
  Histogram2D(QString x_label, QString y_label, QString title = "",
              QWidget* parent = nullptr)
      : AbstractPlotModel(parent),
        x_label(x_label),
        y_label(y_label),
        title(title) {}

  void Draw(QCustomPlot*, int, int);

 private:
  QString x_label;
  QString y_label;
  QString title;
};

#endif  // HISTOGRAM_2D_H

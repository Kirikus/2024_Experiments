#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "abstractplotmodel.h"

class Histogram : public AbstractPlotModel {
  Q_OBJECT
 public:
  Histogram(QString x_label, QString y_label, QString title = "",
            QWidget* parent = nullptr)
      : AbstractPlotModel(parent),
        x_label(x_label),
        y_label(y_label),
        title(title) {}

  void Draw(QCustomPlot*) override;
  void SetOptions() override;

 private:
  QString x_label;
  QString y_label;
  QString title;
};

#endif  // HISTOGRAM_H

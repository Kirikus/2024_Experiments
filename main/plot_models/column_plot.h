#ifndef COLUMN_PLOT_H
#define COLUMN_PLOT_H

#include "abstractplotmodel.h"

class ColumnPlot : public AbstractPlotModel {
  Q_OBJECT
 public:
  ColumnPlot(QString x_label, QString y_label, QString title = "",
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

#endif  // COLUMN_PLOT_H

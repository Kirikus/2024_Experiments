#include "column_plot.h"

#include "manager.h"

QCPBars* glob_bar = nullptr;

void ColumnPlot::Draw(QCustomPlot* plot) {
  if (glob_bar != nullptr) {
    QSharedPointer<QCPBarsDataContainer> emptyData =
        QSharedPointer<QCPBarsDataContainer>::create();
    // Присвоение пустого контейнера данных объекту QCPBars
    glob_bar->setData(emptyData);
    // delete glob_bar;
  }

  int n = lib::Manager::GetInstance()->GetVariablesCount();
  // QCPBars *bars = new QCPBars(plot->xAxis, plot->yAxis);
  // bars->setWidth(0.9/n);
  QCPBars* bar = new QCPBars(plot->xAxis, plot->yAxis); // нет delete
  for (int i = 0; i < n; ++i) {
    const lib::Variable& variable = lib::Manager::GetInstance()->GetVariable(i);

    QVector<double> xAxis_data;
    QVector<double> yAxis_data;
    for (int j = 0; j < variable.GetMeasurementsCount(); j++) {
      if (variable.measurements[j]) {
        xAxis_data.push_back((j + 0.55 + i * (0.9 / n) + 0.9 / (2 * n)));
        yAxis_data.push_back(variable.measurements[j]);
      }
    }
    bar->setWidth(0.9 / n);
    bar->addData(xAxis_data, yAxis_data);
    // bars->setData(emptyData);
    // delete bars;
  }

  plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  plot->replot();

  glob_bar = bar;
  // delete bars;
}

void ColumnPlot::SetOptions() {}

#include "column_plot.h"

#include "manager.h"
void ColumnPlot::Draw(QCustomPlot* plot) {
  int n = lib::Manager::GetInstance()->GetVariablesCount();
  // QCPBars *bars = new QCPBars(plot->xAxis, plot->yAxis);
  // bars->setWidth(0.9/n);
  QCPBars* bars = new QCPBars(plot->xAxis, plot->yAxis);
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
    bars->setWidth(0.9 / n);
    bars->addData(xAxis_data, yAxis_data);
    // bars->setData(emptyData);
    // delete bars;
  }

  plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  plot->replot();

  QSharedPointer<QCPBarsDataContainer> emptyData =
      QSharedPointer<QCPBarsDataContainer>::create();
  // Присвоение пустого контейнера данных объекту QCPBars
  bars->setData(emptyData);

  // delete bars;
}

void ColumnPlot::SetOptions() {}

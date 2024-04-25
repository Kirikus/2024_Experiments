#include "histogram.h"

#include "manager.h"

void Histogram::Draw(QCustomPlot* plot, int var, int column_size) {
  plot->clearPlottables();

  const lib::Variable& variable = lib::Manager::GetInstance()->GetVariable(var);

  double max_value = 0;

  for (int j = 0; j < variable.GetMeasurementsCount(); j++) {
    max_value = std::max(max_value, variable.measurements[j]);
  }

  QVector<double> xAxis_data;
  QVector<double> yAxis_data;

  for (int i = 0; i <= max_value; i += column_size) {
    int count = 0;
    for (int j = 0; j < variable.GetMeasurementsCount(); ++j) {
      if (i <= variable.measurements[j] &&
          variable.measurements[j] < i + column_size) {
        count++;
      }
    }
    xAxis_data.push_back(i + column_size / 2.0);
    yAxis_data.push_back(count);
  }

  QCPBars* bar = new QCPBars(plot->xAxis, plot->yAxis);

  bar->setWidth(column_size);
  bar->setData(xAxis_data, yAxis_data);
  bar->setBrush(QBrush(variable.visual.color));

  plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  plot->replot();
}

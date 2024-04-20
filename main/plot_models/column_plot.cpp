#include "column_plot.h"

#include <vector>

#include "manager.h"

std::vector<QCPBars*> glob_bars;

void ColumnPlot::Draw(QCustomPlot* plot) {
  for (int i = 0; i < glob_bars.size(); ++i) {
    QSharedPointer<QCPBarsDataContainer> emptyData =
        QSharedPointer<QCPBarsDataContainer>::create();
    // Присвоение пустого контейнера данных объекту QCPBars
    glob_bars[i]->setData(emptyData);
  }

  int n = lib::Manager::GetInstance()->GetVariablesCount();

  // QCPBars* bars = new QCPBars(plot->xAxis, plot->yAxis); // нет delete
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
    // QCPBars bar(plot->xAxis, plot->yAxis);
    // bar.setWidth(0.9 / n);
    // bar.addData(xAxis_data, yAxis_data);
    // bars->addData(bar);
    QCPBars* bar = new QCPBars(plot->xAxis, plot->yAxis);  // нет delete

    bar->setWidth(0.9 / n);
    bar->setData(xAxis_data, yAxis_data);
    bar->setBrush(QBrush(variable.visual.color));
    // if (i == 0) {
    //   bar->setBrush(QBrush(QColor(255, 0, 0)));
    // }
    glob_bars.push_back(bar);
    // bars->addData(xAxis_data, yAxis_data);
    // bars->setBrush(QBrush(QColor(255, 0, 0)));
  }
  // QSharedPointer<QCPBarsDataContainer> dataContainer = bars->data();
  // dataContainer->at(0)->setBrush(QBrush(QColor(255, 0, 0)));
  plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  plot->replot();

  // glob_bars = bars;
}

void ColumnPlot::SetOptions() {}

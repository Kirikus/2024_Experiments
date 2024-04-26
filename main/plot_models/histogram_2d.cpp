#include "histogram_2d.h"

#include "manager.h"

void Histogram2D::Draw(QCustomPlot* plot, int x, int y) {
  plot->clearGraphs();
  plot->clearPlottables();
  plot->legend->setVisible(true);

  QVector<int> var{x, y};

  const lib::Variable& variable0 =
      lib::Manager::GetInstance()->GetVariable(var[0]);
  double mx = variable0.GetMeasurementsCount();
  for (int i = 0; i < variable0.GetMeasurementsCount(); ++i) {
    mx = std::max(mx, variable0.measurements[i]);
  }

  const lib::Variable& variable1 =
      lib::Manager::GetInstance()->GetVariable(var[1]);
  mx = std::max(mx, (double)variable1.GetMeasurementsCount());
  for (int i = 0; i < variable1.GetMeasurementsCount(); ++i) {
    mx = std::max(mx, variable1.measurements[i]);
  }
  mx += 1;

  QVector<QVector<int>> density(int(mx) + 1, QVector<int>(int(mx) + 1));

  for (int i = 0; i < 2; ++i) {
    const lib::Variable& variable =
        lib::Manager::GetInstance()->GetVariable(var[i]);
    QCPGraph* graph = plot->addGraph();
    graph->setName(variable.naming.title);
    plot->setFont(QFont("Helvetica", 9));

    QVector<double> xAxis_data;
    QVector<double> yAxis_data;
    for (int j = 0; j < variable.GetMeasurementsCount(); j++) {
      if (variable.measurements[j]) {
        if (i == 1) {
          xAxis_data.push_back(variable.measurements[j]);
          yAxis_data.push_back(j + 1);
          for (int l = 0; l <= mx; ++l) {
            if (l <= variable.measurements[j] &&
                variable.measurements[j] < l + 1) {
              density[l][j + 1]++;
            }
          }

        } else {
          xAxis_data.push_back(j + 1);
          yAxis_data.push_back(variable.measurements[j]);
          for (int l = 0; l <= mx; ++l) {
            if (l <= variable.measurements[j] &&
                variable.measurements[j] < l + 1) {
              density[j + 1][l]++;
            }
          }
        }
      }
    }
    graph->setData(xAxis_data, yAxis_data);
  }

  QCPColorMap* colorMap = new QCPColorMap(plot->xAxis, plot->yAxis);

  colorMap->data()->setSize(mx + 1, mx + 1);
  colorMap->data()->setRange(QCPRange(0, mx), QCPRange(0, mx));

  for (int i = 0; i < mx; ++i) {
    for (int j = 0; j < mx; ++j) {
      colorMap->data()->setCell(i, j, density[i][j]);
    }
  }

  QCPColorGradient gradient;
  gradient.clearColorStops();
  gradient.setColorStopAt(0, QColor(255, 255, 0));
  gradient.setColorStopAt(0.5, QColor(255, 0, 0));
  gradient.setColorStopAt(1, QColor(128, 0, 128));
  colorMap->setGradient(gradient);

  colorMap->rescaleDataRange(false);

  plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  plot->replot();
}

#include "histogram_2d.h"

#include "manager.h"

void Histogram2D::Draw(QCustomPlot* plot, int x, int y) {
  plot->clearGraphs();
  plot->clearPlottables();

  int size_box = 200;

  QVector<QVector<int>> density(size_box, QVector<int>(size_box));

  const lib::Variable& variable_x = lib::Manager::GetInstance()->GetVariable(x);
  QCPGraph* graph = plot->addGraph();

  plot->setFont(QFont("Helvetica", 9));

  const lib::Variable& variable_y = lib::Manager::GetInstance()->GetVariable(y);

  for (int j = 0; j < variable_y.GetMeasurementsCount(); j++) {
    for (int l = -size_box / 2; l <= size_box / 2; ++l) {
      if (l <= variable_y.measurements[j] &&
          variable_y.measurements[j] < l + 1) {
        density[variable_x.measurements[j] + size_box / 2][l + size_box / 2]++;
      }
    }
  }

  QCPColorMap* colorMap = new QCPColorMap(plot->xAxis, plot->yAxis);

  colorMap->data()->setSize(size_box, size_box);
  colorMap->data()->setRange(QCPRange(-size_box / 2, size_box / 2),
                             QCPRange(-size_box / 2, size_box / 2));

  for (int i = 0; i < size_box; ++i) {
    for (int j = 0; j < size_box; ++j) {
      colorMap->data()->setCell(i, j, density[i][j]);
    }
  }

  QCPColorGradient gradient;
  gradient.clearColorStops();
  gradient.setColorStopAt(0, QColor(255, 255, 0));
  gradient.setColorStopAt(0.5, QColor(255, 0, 0));
  gradient.setColorStopAt(1, QColor(128, 0, 128));
  colorMap->setGradient(gradient);

  colorMap->rescaleDataRange(true);

  plot->moveLayer(plot->layer("grid"), plot->layer("main"),
                  QCustomPlot::limAbove);

  plot->xAxis->setLabel("Axis " + variable_x.naming.title);
  plot->yAxis->setLabel("Axis " + variable_y.naming.title);
  plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  plot->replot();
}

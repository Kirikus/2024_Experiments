#include "histogram_2d.h"

#include "manager/manager.h"

void Histogram2D::Draw() {
  // The color scheme automatically adjusts to the set of values

  clearGraphs();
  clearPlottables();

  int size_box = 200;

  QVector<QVector<double>> density(size_box, QVector<double>(size_box));
  QVector<QVector<bool>> flags(size_box, QVector<bool>(size_box, true));

  const lib::Variable& variable_x = lib::Manager::GetInstance()->GetVariable(x);
  QCPGraph* graph = addGraph();

  setFont(QFont("Helvetica", 9));

  const lib::Variable& variable_y = lib::Manager::GetInstance()->GetVariable(y);

  for (int j = 0; j < variable_y.GetMeasurementsCount(); j++) {
    for (int l = -size_box / 2; l <= size_box / 2; ++l) {
      if (l <= variable_y.measurements[j] &&
          variable_y.measurements[j] < l + 1) {
        density[variable_x.measurements[j] + size_box / 2][l + size_box / 2]++;
      }
    }
  }

  QCPColorMap* colorMap = new QCPColorMap(xAxis, yAxis);

  colorMap->data()->setSize(size_box, size_box);
  colorMap->data()->setRange(QCPRange(-size_box / 2, size_box / 2),
                             QCPRange(-size_box / 2, size_box / 2));

  for (int i = 0; i < size_box; ++i) {
    for (int j = 0; j < size_box; ++j) {
      if (flags[i][j]) {
        double med = 0;
        for (int l1 = 0; l1 < square_size; ++l1) {
          for (int l2 = 0; l2 < square_size; ++l2) {
            med += density[std::min(i + l1, size_box - 1)]
                          [std::min(j + l2, size_box - 1)];
            flags[std::min(i + l1, size_box - 1)]
                 [std::min(j + l2, size_box - 1)] = false;
          }
        }
        for (int l1 = 0; l1 < square_size; ++l1) {
          for (int l2 = 0; l2 < square_size; ++l2) {
            colorMap->data()->setCell(std::min(i + l1, size_box - 1),
                                      std::min(j + l2, size_box - 1),
                                      med / square_size * square_size);
          }
        }
      }
    }
  }

  QCPColorGradient gradient;
  gradient.clearColorStops();
  gradient.setColorStopAt(0, QColor(255, 255, 0));
  gradient.setColorStopAt(0.5, QColor(255, 0, 0));
  gradient.setColorStopAt(1, QColor(128, 0, 128));
  colorMap->setGradient(gradient);

  colorMap->setInterpolate(true);
  colorMap->rescaleDataRange(true);

  moveLayer(layer("grid"), layer("main"), QCustomPlot::limAbove);

  xAxis->setLabel("Axis " + variable_x.naming.title);
  yAxis->setLabel("Axis " + variable_y.naming.title);
  setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  replot();
}

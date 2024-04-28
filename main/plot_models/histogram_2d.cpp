#include "histogram_2d.h"

// #include <iostream>

#include "manager.h"

void Histogram2D::Draw(QCustomPlot* plot, int x, int y) {
  plot->clearGraphs();
  plot->clearPlottables();
  plot->legend->setVisible(true);

  int size_box = 200;

  // QVector<int> var{x, y};

  // const lib::Variable& variable0 =
  //     lib::Manager::GetInstance()->GetVariable(var[0]);
  // double mx = -1e9, mn = 1e9;
  // for (int i = 0; i < variable0.GetMeasurementsCount(); ++i) {
  //   mx = std::max(mx, variable0.measurements[i]);
  //   mn = std::min(mn, variable0.measurements[i]);
  // }

  // const lib::Variable& variable1 =
  //     lib::Manager::GetInstance()->GetVariable(var[1]);

  // for (int i = 0; i < variable1.GetMeasurementsCount(); ++i) {
  //   mx = std::max(mx, variable1.measurements[i]);
  //   mn = std::min(mn, variable1.measurements[i]);
  // }
  // mx++;

  // mn = std::min(0.0, mn);

  // QVector<QVector<int>> density(size_box, QVector<int>(size_box));

  // for (int i = 0; i < 2; ++i) {
  // const lib::Variable& variable =
  //     lib::Manager::GetInstance()->GetVariable(var[i]);
  // QCPGraph* graph = plot->addGraph();
  // graph->setName(variable.naming.title);
  // plot->setFont(QFont("Helvetica", 9));

  // for (int j = 0; j < variable.GetMeasurementsCount(); j++) {
  //   if (variable.measurements[j]) {
  //     if (i == 1) {
  //       for (int l = int(mn); l <= int(mx); ++l) {
  //         if (l <= variable.measurements[j] &&
  //             variable.measurements[j] < l + 1) {
  //           density[l - int(mn)][j + 1 - int(mn)]++;
  //         }
  //       }

  //     } else {
  //       for (int l = int(mn); l <= int(mx); ++l) {
  //         if (l <= variable.measurements[j] &&
  //             variable.measurements[j] < l + 1) {
  //           density[j + 1 - int(mn)][l - int(mn)]++;
  //         }
  //       }
  //     }
  //   }
  // }
  // }
  QVector<QVector<int>> density(size_box, QVector<int>(size_box));

  const lib::Variable& variable_x = lib::Manager::GetInstance()->GetVariable(x);
  QCPGraph* graph = plot->addGraph();
  // graph->setName(variable.naming.title);
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
      // std::cout << density[i][j] * 0.2 << ' ';
      colorMap->data()->setCell(i, j, density[i][j]);
    }
    // std::cout << '\n';
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

  plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  plot->replot();
}

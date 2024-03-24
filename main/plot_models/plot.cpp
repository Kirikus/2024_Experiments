#include "plot.h"

void LinePlot::draw(QCustomPlot* plot) {
  plot->xAxis->setRange(0, 6);
  plot->yAxis->setRange(0, 15);

  std::vector<int> colors{173, 255, 47,  0,   191, 255, 255, 69, 0,   255, 215,
                          0,   255, 105, 180, 138, 43,  226, 50, 205, 50};
  for (int i = 0; i < lib::Manager::getInstance()->getVariablesCount(); ++i) {
    auto graph = plot->addGraph(plot->xAxis, plot->yAxis);
    graph->setPen(
        QColor(colors[3 * i], colors[3 * i + 1], colors[3 * i + 2], 255));
    graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 9));

    QVector <double> xs = {1, 2, 3, 4, 5}, ys;
    auto var = lib::Manager::getInstance()->getVariableMeasurements(i);
    for (int j = 0; j < var.size(); ++j) {
        ys.push_back(var[j]);
    }
    graph->setData(xs, ys);
  }
  plot->replot();
}

void LinePlot::setOptions() {}

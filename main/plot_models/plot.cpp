#include "plot.h"

void LinePlot::draw(QCustomPlot* plot) {
  plot->xAxis->setRange(0, 6);
  plot->yAxis->setRange(0, 15);
  plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

  for (int i = 0; i < lib::Manager::getInstance()->getVariablesCount(); ++i) {
    auto graph = plot->addGraph(plot->xAxis, plot->yAxis);
    graph->setPen(QColor(colors[i][0], colors[i][1], colors[i][2]));
    graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 9));

    QVector<double> xs = {1, 2, 3, 4, 5}, ys;
    auto var = lib::Manager::getInstance()->getVariable(i).measurements;
    for (int j = 0; j < var.size(); ++j) {
      ys.push_back(var[j]);
    }
    graph->setData(xs, ys);
  }
  plot->replot();
}

void LinePlot::setOptions() {}

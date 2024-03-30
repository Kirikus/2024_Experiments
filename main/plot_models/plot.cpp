#include "plot.h"

#include <iostream>
#include <random>

#include "manager.h"

void LinePlot::draw(QCustomPlot* plot) {
  plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

  for (int graphIndex = 0; graphIndex < plot->graphCount(); ++graphIndex) {
    plot->graph(graphIndex)->data()->clear();
  }

  for (int i = 0; i < lib::Manager::getInstance()->getVariablesCount(); ++i) {
    auto graph = plot->addGraph(plot->xAxis, plot->yAxis);

    if (i <= 7)
      graph->setPen(QColor(colors[i][0], colors[i][1], colors[i][2]));
    else {
      std::mt19937 gen(i);
      std::uniform_int_distribution<> dis(0, 204);
      graph->setPen(QColor(dis(gen), dis(gen), dis(gen)));
    }

    graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 9));

    QVector<double> xs, ys;
    auto var = lib::Manager::getInstance()->getVariable(i).measurements;
    for (int j = 0; j < var.size(); ++j) {
      ys.push_back(var[j]);
      xs.push_back(j + 1);
    }
    graph->setData(xs, ys);

    auto& visual = lib::Manager::getInstance()->getVariable(i).variable_visual;
    // visible
    graph->setVisible(visual.visible);
    // width
    QPen graphPen = graph->pen();
    graphPen.setWidth(visual.width);
    graph->setPen(graphPen);
  }

  plot->replot();
}

void LinePlot::setOptions() {}

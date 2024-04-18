#include "dot_plot.h"

#include "manager.h"

void DotPlot::Draw(QCustomPlot* plot) {
  plot->clearGraphs();
  plot->legend->setVisible(true);

  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    const lib::Variable& variable = lib::Manager::GetInstance()->GetVariable(i);
    if (!variable.visual.visible) continue;
    QCPGraph* graph = plot->addGraph();
    graph->setName(variable.naming.title);
    plot->setFont(QFont("Helvetica", 9));

    graph->setLineStyle(QCPGraph::lsNone);

    graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    graph->setPen(QPen(QBrush(variable.visual.color), variable.visual.width,
                       variable.visual.line_type));

    QCPErrorBars* yError_bar = new QCPErrorBars(plot->xAxis, plot->yAxis);
    yError_bar->removeFromLegend();
    yError_bar->setDataPlottable(graph);

    QVector<double> xAxis_data;
    QVector<double> yAxis_data;
    QVector<double> yError_data;
    for (int j = 0; j < variable.GetMeasurementsCount(); j++) {
      if (variable.measurements[j]) {
        xAxis_data.push_back(j + 1);
        yAxis_data.push_back(variable.measurements[j]);
        switch (variable.error.type) {
          case lib::Variable::ErrorOptions::Types::kAbsolute:
            yError_data.push_back(variable.error.value);
            break;
          case lib::Variable::ErrorOptions::Types::kRelative:
            yError_data.push_back(variable.measurements[j] *
                                  variable.error.value * 0.5);
            break;
        }
      }
    }
    yError_bar->setData(yError_data);
    graph->setData(xAxis_data, yAxis_data);
  }
  plot->rescaleAxes();
  plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  plot->replot();
}

void DotPlot::SetOptions() {}

#include "line_plot.h"

#include "manager.h"

void LinePlot::Draw(QCustomPlot* plot) {
  plot->clearGraphs();
  plot->legend->setVisible(false);

  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    const lib::Variable& variable = lib::Manager::GetInstance()->GetVariable(i);
    if (!variable.visual.visible) continue;
    QCPGraph* graph = plot->addGraph();

    graph->setScatterStyle(variable.visual.point_shape);
    graph->setPen(QPen(QBrush(variable.visual.color), variable.visual.width,
                       variable.visual.line_type));

    QCPErrorBars* yError_bar = new QCPErrorBars(plot->xAxis, plot->yAxis);
    yError_bar->setDataPlottable(graph);

    QVector<double> xAxis_data;
    QVector<double> yAxis_data;
    QVector<double> yAxis_errors;
    for (int j = 0; j < variable.GetMeasurementsCount(); j++) {
      xAxis_data.push_back(j + 1);
      yAxis_data.push_back(variable.measurements[j]);
      switch (variable.error.type) {
        case lib::Variable::ErrorOptions::Types::kAbsolute:
          yAxis_errors.push_back(variable.error.value);
        case lib::Variable::ErrorOptions::Types::kRelative:
          yAxis_errors.push_back(variable.error.value);
      }
    }

    graph->setData(xAxis_data, yAxis_data);
    yError_bar->setData(yAxis_errors);
  }
  plot->rescaleAxes();
  plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  plot->replot();
}

void LinePlot::SetOptions() {}

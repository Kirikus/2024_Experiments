#include "scatter_plot_2d.h"

#include "manager.h"
#include "options_scatter_2d.h"

void ScatterPlot2D::Draw() {
  clearGraphs();

  if (lib::Manager::GetInstance()->GetVariablesCount() == 0) return;

  const lib::Variable& variable_x =
      lib::Manager::GetInstance()->GetVariable(x_);
  QCPGraph* graph = addGraph();

  setFont(QFont("Helvetica", 9));

  graph->setLineStyle(QCPGraph::lsNone);

  graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
  graph->setPen(QPen(QBrush(variable_x.visual.color), variable_x.visual.width,
                     variable_x.visual.line_type));

  QVector<double> xAxis_data;
  QVector<double> yAxis_data;

  const lib::Variable& variable_y =
      lib::Manager::GetInstance()->GetVariable(y_);

  for (int j = 0; j < variable_x.GetMeasurementsCount(); j++) {
    xAxis_data.push_back(variable_x.measurements[j]);
    yAxis_data.push_back(variable_y.measurements[j]);
  }
  xAxis->setLabel("Axis " + variable_x.naming.title);
  yAxis->setLabel("Axis " + variable_y.naming.title);
  graph->setData(xAxis_data, yAxis_data);

  setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  replot();
}

void ScatterPlot2D::Options() {
  OptionsScatter2D a;
  a.exec();

  x_ = a.choose_AxisX();
  y_ = a.choose_AxisY();

  Draw();
}

#include "scatter_plot.h"

#include "manager/manager.h"

void ScatterPlot::Draw() {
  clearGraphs();
  legend->setVisible(true);

  for (size_t i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    const lib::Variable& variable = lib::Manager::GetInstance()->GetVariable(i);
    if (!variable.visual.visible) continue;
    QCPGraph* graph = addGraph();
    graph->setName(variable.naming.title);
    setFont(QFont("Helvetica", 9));

    graph->setLineStyle(QCPGraph::lsNone);

    if (variable.visual.point_shape ==
        QCPScatterStyle::ScatterShape::ssNone) {
      graph->setScatterStyle(QCPScatterStyle::ScatterShape::ssDisc);
    } else {
      graph->setScatterStyle(variable.visual.point_shape);
    }

    graph->setPen(QPen(QBrush(variable.visual.color), variable.visual.width,
                       variable.visual.line_type));

    QVector<double> xAxis_data;
    QVector<double> yAxis_data;
    for (size_t j = 0; j < variable.GetMeasurementsCount(); j++) {
      if (variable.measurements[j]) {
        xAxis_data.push_back(j + 1);
        yAxis_data.push_back(variable.measurements[j]);
      }
    }
    graph->setData(xAxis_data, yAxis_data);
  }
  setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  replot();
}

void ScatterPlot::Options() {
  // nothing
}

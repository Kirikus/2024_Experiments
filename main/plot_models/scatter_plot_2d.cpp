// #include "scatter_plot_2d.h"
#include "C:\2024_Experiments\main\plot_models\scatter_plot_2d.h"

#include "manager.h"

void ScatterPlot2D::Draw(QCustomPlot* plot, int x, int y) {
    plot->clearGraphs();
    plot->legend->setVisible(true);

    QVector <int> var{x, y};

    for (int i = 0; i < 2; ++i) {
        const lib::Variable& variable = lib::Manager::GetInstance()->GetVariable(var[i]);
        QCPGraph* graph = plot->addGraph();
        graph->setName(variable.naming.title);
        plot->setFont(QFont("Helvetica", 9));

        graph->setLineStyle(QCPGraph::lsNone);

        graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
        graph->setPen(QPen(QBrush(variable.visual.color), variable.visual.width,
                           variable.visual.line_type));

        QVector<double> xAxis_data;
        QVector<double> yAxis_data;
        for (int j = 0; j < variable.GetMeasurementsCount(); j++) {
            if (variable.measurements[j]) {
                xAxis_data.push_back(j + 1);
                yAxis_data.push_back(variable.measurements[j]);
            }
        }
        graph->setData(xAxis_data, yAxis_data);
    }
    plot->rescaleAxes();
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    plot->replot();
}

#include "histogram.h"

#include <vector>

#include "manager.h"

std::vector<QCPBars*> glob_bars2;

void Histogram::Draw(QCustomPlot* plot) {
    for (int i = 0; i < glob_bars2.size(); ++i) {
        plot->clearPlottables();
    }

    plot->clearGraphs();
    plot->legend->setVisible(true);

    int n = lib::Manager::GetInstance()->GetVariablesCount();

    for (int i = 0; i < n; ++i) {
        const lib::Variable& variable = lib::Manager::GetInstance()->GetVariable(i);
        if (!variable.visual.visible) continue;

        QCPGraph* graph = plot->addGraph();
        graph->setName(variable.naming.title);
        plot->setFont(QFont("Helvetica", 9));

        graph->setScatterStyle(variable.visual.point_shape);
        graph->setPen(QPen(QBrush(variable.visual.color), variable.visual.width,
                           variable.visual.line_type));

        QVector<double> xAxis_data;
        QVector<double> yAxis_data;
        for (int j = 0; j < variable.GetMeasurementsCount(); j++) {
            if (variable.measurements[j]) {
                xAxis_data.push_back((j + 0.55 + i * (0.9 / n) + 0.9 / (2 * n)));
                yAxis_data.push_back(variable.measurements[j]);
            }
        }

        QCPBars* bar = new QCPBars(plot->xAxis, plot->yAxis);  // нет delete

        bar->setWidth(0.9 / n);
        bar->setData(xAxis_data, yAxis_data);
        bar->setBrush(QBrush(variable.visual.color));
        glob_bars2.push_back(bar);

        graph->setData(xAxis_data, yAxis_data);
    }
    plot->rescaleAxes();
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    plot->replot();
}

void Histogram::SetOptions() {}

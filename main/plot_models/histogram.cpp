#include "histogram.h"

#include "manager.h"

void Histogram::Draw(QCustomPlot* plot) {
    plot->clearPlottables();

    plot->legend->setVisible(true);

    const lib::Variable& variable = lib::Manager::GetInstance()->GetVariable(0);

    double max_value = 0;

    for (int j = 0; j < variable.GetMeasurementsCount(); j++) {
        max_value = std::max(max_value, variable.measurements[j]);
    }

    QVector<double> xAxis_data;
    QVector<double> yAxis_data;

    for (int i = 0; i<=max_value; ++i) {
        int count = 0;
        for (int j = 0; j<variable.GetMeasurementsCount(); ++j) {
            if (i <= variable.measurements[j] && variable.measurements[j] < i+1) {
                count++;
            }
        }
        xAxis_data.push_back(i+0.5);
        yAxis_data.push_back(count);
    }

    QCPBars* bar = new QCPBars(plot->xAxis, plot->yAxis);

    bar->setWidth(1);
    bar->setData(xAxis_data, yAxis_data);
    bar->setBrush(QBrush(variable.visual.color));

    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    plot->replot();
}

void Histogram::SetOptions() {}

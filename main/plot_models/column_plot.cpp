#include "column_plot.h"
#include "manager.h"

void ColumnPlot::Draw(QCustomPlot* plot) {
    // Предположим, что 'customPlot' это указатель на твой объект QCustomPlot.

    // Создаём объект QCPBars для гистограммы.
    QCPBars *bars = new QCPBars(plot->xAxis, plot->yAxis);

    // Подготавливаем данные для гистограммы.
    QVector<double> xData{1, 2, 3}, yData{2, 2, 3}; // xData - координаты по оси X, yData - высоты столбцов (частоты).

    // Устанавливаем данные для гистограммы.
    bars->setData(xData, yData);

    // Устанавливаем ширину столбцов.
    bars->setWidth(0.9);

    // Настраиваем оформление осей, если нужно.
    plot->xAxis->setLabel("Номер измерения");
    plot->yAxis->setLabel("Значение величины");

    // Настраиваем легенду, если нужно.
    bars->setName("Данные");
    plot->legend->setVisible(true);

    // Перерисовываем график.
    plot->replot();
}

void ColumnPlot::SetOptions() {}

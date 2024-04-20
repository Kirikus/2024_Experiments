#ifndef DOT_PLOT_H
#define DOT_PLOT_H

#include "abstractplotmodel.h"

class DotPlot : public AbstractPlotModel {
    Q_OBJECT
public:
    DotPlot(QString x_label, QString y_label, QString title = "",
             QWidget* parent = nullptr)
        : AbstractPlotModel(parent),
        x_label(x_label),
        y_label(y_label),
        title(title) {}

    void Draw(QCustomPlot*) override;
    void SetOptions() override;
private:
    QString x_label;
    QString y_label;
    QString title;
};

#endif // DOT_PLOT_H

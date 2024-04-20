#ifndef COMBO_PLOT_H
#define COMBO_PLOT_H

#include "abstractplotmodel.h"

class ComboPlot : public AbstractPlotModel {
    Q_OBJECT
public:
    ComboPlot(QString x_label, QString y_label, QString title = "",
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

#endif // COMBO_PLOT_H

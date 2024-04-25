#ifndef OPTIONS_HISTOGRAM_2D_H
#define OPTIONS_HISTOGRAM_2D_H

#include "ui_options_histogram_2d.h"

class OptionsHistogram2D : public QDialog {
    Q_OBJECT

public:
    OptionsHistogram2D(QWidget *parent = nullptr);
    ~OptionsHistogram2D();

    int choose_AxisX();
    int choose_AxisY();
    // добавить еще выбора размера квадрата
    void ok();

private:
    Ui::DialogHistogram2D *ui;
};

#endif // OPTIONS_HISTOGRAM_2D_H

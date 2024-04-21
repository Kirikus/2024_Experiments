#ifndef OPTIONS_H
#define OPTIONS_H

#include "ui_options.h"

class Options : public QDialog {
    Q_OBJECT

public:
    Options(QWidget *parent = nullptr);
    ~Options();

private:
    Ui::Dialog *ui;
};

#endif  // OPTIONS_H

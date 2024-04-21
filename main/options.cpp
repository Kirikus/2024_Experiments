#include "options.h"

Options::Options(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);
}
Options::~Options() {
    delete ui;
}

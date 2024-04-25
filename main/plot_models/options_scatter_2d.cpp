#include "options_scatter_2d.h"

#include "manager.h"

OptionsScatter2D::OptionsScatter2D(QWidget *parent)
    : QDialog(parent), ui(new Ui::DialogScattetPlot2D) {
  ui->setupUi(this);

  for (int i = 0; i < lib::Manager::GetInstance()->names_of_variables.size();
       ++i) {
    ui->AxisXComboBox->addItem(
        lib::Manager::GetInstance()->names_of_variables[i]);
  }

  for (int i = 0; i < lib::Manager::GetInstance()->names_of_variables.size();
       ++i) {
    ui->AxisYComboBox->addItem(
        lib::Manager::GetInstance()->names_of_variables[i]);
  }

  connect(ui->okPushButton, &QPushButton::clicked, this, &QDialog::close);
}

int OptionsScatter2D::choose_AxisX() {
  return ui->AxisXComboBox->currentIndex();
}

int OptionsScatter2D::choose_AxisY() {
  return ui->AxisYComboBox->currentIndex();
}

OptionsScatter2D::~OptionsScatter2D() { delete ui; }

#include "options_scatter_2d.h"

#include "manager.h"

OptionsScatter2D::OptionsScatter2D(QWidget *parent)
    : QDialog(parent), ui(new Ui::DialogScattetPlot2D) {
  ui->setupUi(this);

  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    ui->AxisXComboBox->addItem(
        lib::Manager::GetInstance()->GetVariable(i).naming.title);
  }

  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    ui->AxisYComboBox->addItem(
        lib::Manager::GetInstance()->GetVariable(i).naming.title);
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

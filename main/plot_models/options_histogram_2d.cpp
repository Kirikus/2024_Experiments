#include "options_histogram_2d.h"

#include "manager.h"

OptionsHistogram2D::OptionsHistogram2D(QWidget *parent)
    : QDialog(parent), ui(new Ui::DialogHistogram2D) {
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

int OptionsHistogram2D::choose_AxisX() {
  return ui->AxisXComboBox->currentIndex();
}

int OptionsHistogram2D::choose_AxisY() {
  return ui->AxisYComboBox->currentIndex();
}

OptionsHistogram2D::~OptionsHistogram2D() { delete ui; }

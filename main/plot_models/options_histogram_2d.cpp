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

  ui->SquareSizeComboBox->addItem("1");
  ui->SquareSizeComboBox->addItem("2");
  ui->SquareSizeComboBox->addItem("4");

  connect(ui->okPushButton, &QPushButton::clicked, this, &QDialog::close);
}

int OptionsHistogram2D::choose_square_size() {
  return std::pow(2, ui->SquareSizeComboBox->currentIndex());
}

int OptionsHistogram2D::choose_AxisX() {
  return ui->AxisXComboBox->currentIndex();
}

int OptionsHistogram2D::choose_AxisY() {
  return ui->AxisYComboBox->currentIndex();
}

OptionsHistogram2D::~OptionsHistogram2D() { delete ui; }

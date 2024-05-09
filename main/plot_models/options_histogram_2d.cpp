#include "options_histogram_2d.h"

#include "manager/manager.h"

OptionsHistogram2D::OptionsHistogram2D(QWidget *parent)
    : QDialog(parent), ui(new Ui::DialogHistogram2D) {
  ui->setupUi(this);

  setFixedSize(272, 153);
  setWindowTitle("Data Handler");
  setWindowIcon(QIcon("C:/2024_Experiments/images/mainwindow.png"));

  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    ui->subVarComboBox->addItem(
        lib::Manager::GetInstance()->GetVariable(i).naming.title);
  }

  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    ui->mainVarComboBox->addItem(
        lib::Manager::GetInstance()->GetVariable(i).naming.title);
  }

  ui->squareSizeComboBox->addItem("1");
  ui->squareSizeComboBox->addItem("2");
  ui->squareSizeComboBox->addItem("4");

  connect(ui->confirmPushButton, &QPushButton::clicked, this, &QDialog::close);
}

int OptionsHistogram2D::choose_square_size() {
  return std::pow(2, ui->squareSizeComboBox->currentIndex());
}

int OptionsHistogram2D::choose_AxisX() {
  return ui->subVarComboBox->currentIndex();
}

int OptionsHistogram2D::choose_AxisY() {
  return ui->mainVarComboBox->currentIndex();
}

OptionsHistogram2D::~OptionsHistogram2D() { delete ui; }

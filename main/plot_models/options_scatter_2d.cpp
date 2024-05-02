#include "options_scatter_2d.h"

#include "manager.h"

OptionsScatter2D::OptionsScatter2D(QWidget *parent)
    : QDialog(parent), ui(new Ui::DialogScattetPlot2D) {
  ui->setupUi(this);

  setFixedSize(272, 153);
  setWindowTitle("Data Handler");
  setWindowIcon(QIcon("C:/2024_Experiments/images/mainwindow.png"));

  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    ui->SubVarComboBox->addItem(
        lib::Manager::GetInstance()->GetVariable(i).naming.title);
  }

  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    ui->MainVarComboBox->addItem(
        lib::Manager::GetInstance()->GetVariable(i).naming.title);
  }

  connect(ui->ConfirmPushButton, &QPushButton::clicked, this, &QDialog::close);
}

int OptionsScatter2D::choose_AxisX() {
  return ui->SubVarComboBox->currentIndex();
}

int OptionsScatter2D::choose_AxisY() {
  return ui->MainVarComboBox->currentIndex();
}

OptionsScatter2D::~OptionsScatter2D() { delete ui; }

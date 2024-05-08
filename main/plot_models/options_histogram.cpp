#include "options_histogram.h"

#include "manager.h"

OptionsHistogram::OptionsHistogram(QWidget *parent)
    : QDialog(parent), ui(new Ui::DialogHistogram) {
  ui->setupUi(this);

  setFixedSize(272, 153);
  setWindowTitle("Data Handler");
  setWindowIcon(QIcon("C:/2024_Experiments/images/mainwindow.png"));

  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    ui->variableComboBox->addItem(
        lib::Manager::GetInstance()->GetVariable(i).naming.title);
  }

  ui->columnSizeComboBox->addItem("1");
  ui->columnSizeComboBox->addItem("2");
  ui->columnSizeComboBox->addItem("3");

  connect(ui->confirmPushButton, &QPushButton::clicked, this, &QDialog::close);
}

int OptionsHistogram::choose_variable() {
  return ui->variableComboBox->currentIndex();
}

int OptionsHistogram::choose_column_size() {
  return ui->columnSizeComboBox->currentIndex();
}

OptionsHistogram::~OptionsHistogram() { delete ui; }

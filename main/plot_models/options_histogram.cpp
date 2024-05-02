#include "options_histogram.h"

#include "manager.h"

OptionsHistogram::OptionsHistogram(QWidget *parent)
    : QDialog(parent), ui(new Ui::DialogHistogram) {
  ui->setupUi(this);

  setFixedSize(272, 153);
  setWindowTitle("Data Handler");
  setWindowIcon(QIcon("C:/2024_Experiments/images/mainwindow.png"));

  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); ++i) {
    ui->VariableComboBox->addItem(
        lib::Manager::GetInstance()->GetVariable(i).naming.title);
  }

  ui->ColumnSizeComboBox->addItem(QString("1"));
  ui->ColumnSizeComboBox->addItem(QString("2"));
  ui->ColumnSizeComboBox->addItem(QString("3"));

  connect(ui->ConfirmPushButton, &QPushButton::clicked, this, &QDialog::close);
}

int OptionsHistogram::choose_variable() {
  return ui->VariableComboBox->currentIndex();
}

int OptionsHistogram::choose_column_size() {
  return ui->ColumnSizeComboBox->currentIndex() + 1;
}

OptionsHistogram::~OptionsHistogram() { delete ui; }

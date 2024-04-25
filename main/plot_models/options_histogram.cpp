#include "options_histogram.h"

#include "manager.h"

OptionsHistogram::OptionsHistogram(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);

  for (int i = 0; i < lib::Manager::GetInstance()->names_of_variables.size();
       ++i) {
    ui->VariableComboBox->addItem(
        lib::Manager::GetInstance()->names_of_variables[i]);
  }

  ui->ColumnSizeComboBox->addItem(QString("1"));
  ui->ColumnSizeComboBox->addItem(QString("2"));
  ui->ColumnSizeComboBox->addItem(QString("3"));

  connect(ui->okPushButton, &QPushButton::clicked, this, &QDialog::close);
}

int OptionsHistogram::choose_variable() { return ui->VariableComboBox->currentIndex(); }

int OptionsHistogram::choose_column_size() {
  return ui->ColumnSizeComboBox->currentIndex() + 1;
}

OptionsHistogram::~OptionsHistogram() { delete ui; }

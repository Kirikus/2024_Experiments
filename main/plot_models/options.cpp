#include "options.h"

#include "manager.h"

Options::Options(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);

  for (int i = 0; i < lib::Manager::GetInstance()->names_of_variables.size();
       ++i) {
    ui->VariableComboBox->addItem(
        lib::Manager::GetInstance()->names_of_variables[i]);
  }
  // ui->ColumnSizeComboBox->addItem(
  //     lib::Manager::GetInstance()->QString("0.5"));
  // ui->ColumnSizeComboBox->addItem(
  //     lib::Manager::GetInstance()->QString("1"));
  // ui->ColumnSizeComboBox->addItem(
  //     lib::Manager::GetInstance()->QString("2"));

  connect(ui->okPushButton, SIGNAL(clicked()), this, SLOT(ok()));
}

void Options::ok() { this->close(); }

int Options::choose_variable() { return ui->VariableComboBox->currentIndex(); }
int Options::choose_column_size() { return ui->ColumnSizeComboBox->currentIndex(); }

Options::~Options() { delete ui; }

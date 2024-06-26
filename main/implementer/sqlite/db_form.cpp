#include "db_form.h"

#include "ui_db_form.h"

DB_Form::DB_Form(QWidget *parent) : QMainWindow(parent), ui(new Ui::DB_Form) {
  ui->setupUi(this);

  setWindowIcon(QIcon("C:/2024_Experiments/images/mainwindow.png"));
  setWindowTitle("Data Handler");
}

DB_Form::~DB_Form() { delete ui; }

QTableWidget *DB_Form::GetMeasurementsTableWidget() {
  return ui->measurementsTable;
}


void DB_Form::on_uploadBtn_clicked() { emit uploadBtn_is_clicked(); }

void DB_Form::on_deleteBtn_clicked() { emit deleteBtn_is_clicked(); }

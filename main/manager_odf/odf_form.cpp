#include "odf_form.h"

#include "manager_odf.h"
#include "ui_odf_form.h"

ODF_Form::ODF_Form(QWidget *parent) : QWidget(parent), ui(new Ui::ODF_Form) {
  ui->setupUi(this);

  setWindowIcon(QIcon("C:/2024_Experiments/images/mainwindow.png"));
  setWindowTitle("Data Handler");
}

ODF_Form::~ODF_Form() {
  delete ManagerODF::GetInstance()->form;
  delete ui;
}

QVBoxLayout *ODF_Form::GetLayout() { return ui->verticalLayout; }

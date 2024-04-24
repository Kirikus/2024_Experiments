#include "odf_form.h"

#include "manager_odf.h"
#include "ui_odf_form.h"

ODF_Form::ODF_Form(QWidget *parent) : QWidget(parent), ui(new Ui::ODF_Form) {
  setWindowIcon(QIcon("C:/2024_Experiments/images/mainwindow.png"));
  ODF_Form::QWidget::setWindowTitle("Open Document Format"); // doesn't work
  ODF_Form::QWidget::setFixedSize(860, 800);
  ui->setupUi(this);

  setWindowIcon(QIcon("C:/2024_Experiments/images/mainwindow.png"));
  setWindowTitle("Data Handler");
}

ODF_Form::~ODF_Form() {
  delete ManagerODF::GetInstance()->form;
  delete ui;
}

QVBoxLayout *ODF_Form::GetLayout() { return ui->verticalLayout; }

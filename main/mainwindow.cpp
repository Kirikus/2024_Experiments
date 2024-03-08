#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "manager.h"
#include "measurements_table.h"
#include "plot.h"
#include "qcustomplot.h"
#include "strategyIO.h"
#include "variable.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  lib::Variable a(5);
  lib::Variable b(6);
  lib::Variable c(3);
  a.measurements = {1, 2, 3, 4, 5};
  b.measurements = {4, 2, 11, 3, 5, 1};
  c.measurements = {4, 2, 11};
  lib::Manager::getInstance()->addVariable(a);
  lib::Manager::getInstance()->addVariable(b);
  lib::Manager::getInstance()->addVariable(c);

  ui->tableView->setModel(new lib::MeasurementsTable);

  ui->tableView->show();

  connect(ui->addRow, SIGNAL(clicked()), this, SLOT(addRow()));
  connect(ui->addColumn, SIGNAL(clicked()), this, SLOT(addColumn()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_deletePlot_clicked() {
  int index = ui->tabWidget_plots->currentIndex();
  ui->tabWidget_plots->removeTab(index);
}

void MainWindow::on_pushButton_addScatterPlot_clicked() {
  int count = ui->tabWidget_plots->count();
  ui->tabWidget_plots->addTab(new QCustomPlot,
                              "tab" + QString::number(count + 1));
}

void MainWindow::addRow() {
  ui->tableView->model()->insertRows(
      lib::Manager::getInstance()->getMeasurementsCount(), 1);
}
void MainWindow::addColumn() {
  ui->tableView->model()->insertColumns(
      lib::Manager::getInstance()->getVariablesCount(), 1);
}

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

  ui->tableMain->setModel(new lib::MeasurementsTable);

  ui->tableMain->show();

}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_deletePlotBtn_clicked() {
  int index = ui->tabWidgetPlots->currentIndex();
  ui->tabWidgetPlots->removeTab(index);
}

void MainWindow::on_addPlotBtn_clicked() {
  int count = ui->tabWidgetPlots->count();
  ui->tabWidgetPlots->addTab(new QCustomPlot,
                              "tab" + QString::number(count + 1));
}

void MainWindow::on_addRowBtn_clicked() {
  ui->tableMain->model()->insertRows(
      lib::Manager::getInstance()->getMeasurementsCount(), 1);
}

void MainWindow::on_addColumnBtn_clicked() {
  ui->tableMain->model()->insertColumns(
      lib::Manager::getInstance()->getVariablesCount(), 1);
}



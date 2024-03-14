#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "manager.h"
#include "plot.h"
#include "qcustomplot.h"
#include "strategyIO.h"
#include "table_models/measurements_table.h"
#include "table_models/naming_table.h"
#include "variable.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  lib::Variable a{{1, 2, 3, 4, 5}, "izmerenie_1", "x"};
  lib::Variable b{{4, 2, 11, 3, 5, 1}, "izmerenie_2"};
  lib::Variable c{{4, 2, 11}, "izmerenie_3", "z"};
  lib::Manager::getInstance()->addVariable(c);
  lib::Manager::getInstance()->addVariable(a);
  lib::Manager::getInstance()->addVariable(b);

  ui->tableViewMain->setModel(new lib::MeasurementsTable);
  ui->tableViewNaming->setModel(new lib::NamingTable);
  ui->tableViewMain->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui->tableViewNaming->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);

  ui->tableViewMain->show();
  ui->tableViewNaming->show();

  connect(ui->addRowBtn, SIGNAL(clicked()), this, SLOT(addRow()));
  connect(ui->addColumnBtn, SIGNAL(clicked()), this, SLOT(addColumn()));
  connect(ui->deleteRowBtn, SIGNAL(clicked()), this, SLOT(removeRow()));
  connect(ui->deleteColumnBtn, SIGNAL(clicked()), this, SLOT(removeColumn()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_deletePlotBtn_clicked() {
  int index = ui->tabWidgetPlots->currentIndex();
  ui->tabWidgetPlots->removeTab(index);
}

void MainWindow::on_addPlotBtn_clicked() {
  int count = ui->tabWidgetPlots->count();
  ui->tabWidgetPlots->addTab(new QCustomPlot,
                             "Plot " + QString::number(count + 1));
}

void MainWindow::addRow() {
  size_t count = lib::Manager::getInstance()->getMeasurementsCount();
  for (int i = 0; i < lib::Manager::getInstance()->getVariablesCount(); i++)
    if (count ==
        lib::Manager::getInstance()->getVariable(i).getMeasurementsCount())
      lib::Manager::getInstance()->getVariable(i).measurements.push_back(0);
  ui->tableViewMain->model()->insertRows(
      lib::Manager::getInstance()->getMeasurementsCount(), 1);
}

void MainWindow::removeRow() {
  size_t count = lib::Manager::getInstance()->getMeasurementsCount();
  if (count == 1) return;
  for (int i = 0; i < lib::Manager::getInstance()->getVariablesCount(); i++)
    if (count ==
        lib::Manager::getInstance()->getVariable(i).getMeasurementsCount())
      lib::Manager::getInstance()->getVariable(i).measurements.pop_back();
  ui->tableViewMain->model()->removeRows(
      lib::Manager::getInstance()->getMeasurementsCount(), 1);
}

void MainWindow::removeColumn() {
  if (lib::Manager::getInstance()->getVariablesCount() == 1) return;
  lib::Manager::getInstance()->deleteVariable();
  ui->tableViewMain->model()->removeColumns(
      lib::Manager::getInstance()->getVariablesCount(), 1);
  ui->tableViewNaming->model()->removeRows(
      lib::Manager::getInstance()->getVariablesCount(), 1);
}
void MainWindow::addColumn() {
  lib::Manager::getInstance()->addVariable(lib::Variable());
  ui->tableViewMain->model()->insertColumns(
      lib::Manager::getInstance()->getVariablesCount(), 1);
  ui->tableViewNaming->model()->insertRows(
      lib::Manager::getInstance()->getVariablesCount(), 1);
}

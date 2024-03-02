#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "manager.h"
#include "plot.h"
#include "qcustomplot.h"
#include "strategyIO.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  lib::Manager::getInstance();
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

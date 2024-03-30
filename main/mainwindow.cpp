#include "mainwindow.h"

#include <vector>

#include "./ui_mainwindow.h"
#include "QStandardPaths"
#include "manager.h"
#include "plot_models/plot.h"
#include "qcustomplot.h"
#include "strategyIO.h"
#include "table_models/delegates/color_delegate.h"
#include "table_models/delegates/combobox_delegate.h"
#include "table_models/errors_table.h"
#include "table_models/measurements_table.h"
#include "table_models/naming_table.h"
#include "table_models/plot_settings_table.h"
#include "variable.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  lib::Variable a{{1, 2, 3, 4, 5}, "izmerenie_1", "x"};
  lib::Variable b{{4, 2, 11, 3, 5, 1}, "izmerenie_2"};
  lib::Variable c{{5, 3, 12}, "izmerenie_3", "z"};
  lib::Variable d{{7, 3, 12, 10, 9, 13}, "izmerenie_3", "z"};

  lib::Manager::getInstance()->addVariable(c);
  lib::Manager::getInstance()->addVariable(a);
  lib::Manager::getInstance()->addVariable(b);
  lib::Manager::getInstance()->addVariable(d);

  plot->draw(ui->customPlot);

  ui->tableViewMain->setModel(new lib::MeasurementsTable);
  ui->tableViewNaming->setModel(new lib::NamingTable);
  ui->tableViewPlotsSets->setModel(new lib::PlotSettingsTable);
  ui->tableViewErrors->setModel(new lib::ErrorsTable);

  ui->tableViewPlotsSets->setItemDelegateForColumn(4, new ColorDelegate);
  ui->tableViewPlotsSets->setItemDelegateForColumn(
      2, new ComboBoxDelegate(lib::VisualOptions::point_forms.values()));
  ui->tableViewPlotsSets->setItemDelegateForColumn(
      3, new ComboBoxDelegate(lib::VisualOptions::line_types.values()));

  ui->tableViewErrors->setItemDelegateForColumn(
      0, new ComboBoxDelegate(lib::ErrorOptions::error_types.values()));

  ui->tableViewMain->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui->tableViewNaming->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui->tableViewPlotsSets->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  // ui->tableViewErrors->horizontalHeader()->setSectionResizeMode(
  //     QHeaderView::ResizeToContents);

  ui->tableViewMain->show();
  ui->tableViewNaming->show();
  ui->tableViewPlotsSets->show();
  ui->tableViewErrors->show();

  connect(ui->redrawPlotBtn, SIGNAL(clicked()), this, SLOT(Redraw()));

  connect(ui->addPlotBtn, SIGNAL(clicked()), this, SLOT(addPlot()));
  connect(ui->deletePlotBtn, SIGNAL(clicked()), this, SLOT(deletePlot()));

  connect(ui->LoadDataBtn, SIGNAL(clicked()), this, SLOT(load()));

  // delete column
  connect(ui->deleteColumnBtn, SIGNAL(clicked()), this,
          SLOT(ConfirmDeleteVariable()));
  connect(lib::Manager::getInstance(), SIGNAL(Variable_is_deleted()), this,
          SLOT(deleteColumn()));
  // add column
  connect(ui->addColumnBtn, SIGNAL(clicked()), lib::Manager::getInstance(),
          SLOT(addVariable()));
  connect(lib::Manager::getInstance(), SIGNAL(Variable_is_added()), this,
          SLOT(addColumn()));
  // delete row
  connect(ui->deleteRowBtn, SIGNAL(clicked()), this,
          SLOT(ConfirmDeleteMeasurments()));
  connect(lib::Manager::getInstance(), SIGNAL(Measurements_is_deleted()), this,
          SLOT(deleteRow()));
  // add row
  connect(ui->addRowBtn, SIGNAL(clicked()), lib::Manager::getInstance(),
          SLOT(addMeasurements()));
  connect(lib::Manager::getInstance(), SIGNAL(Measurements_is_added()), this,
          SLOT(addRow()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ConfirmDeleteVariable() {
  if (ui->tableViewMain->selectionModel()->hasSelection()) {
      int index_column = ui->tableViewMain->currentIndex().column();
      if (ConfirmingAction()) {
        lib::Manager::getInstance()->deleteVariable(index_column);
      }
    }
  else return;
}

void MainWindow::ConfirmDeleteMeasurments() {
  if (ConfirmingAction()) {
    lib::Manager::getInstance()->deleteMeasurements();
  }
}

bool MainWindow::ConfirmingAction() {
  // Create Dialog Window
  QDialog* Dialog = new QDialog();
  Dialog->setMinimumWidth(180);
  Dialog->setMinimumHeight(90);
  Dialog->setMaximumWidth(180);
  Dialog->setMaximumHeight(90);
  Dialog->setWindowTitle("Confirming window");
  // Create "Yes" and "No" buttons
  QDialogButtonBox* confirmButtonsBox =
      new QDialogButtonBox(QDialogButtonBox::Yes | QDialogButtonBox::Cancel);
  connect(confirmButtonsBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
  connect(confirmButtonsBox, SIGNAL(rejected()), Dialog, SLOT(reject()));
  confirmButtonsBox->setParent(Dialog);
  confirmButtonsBox->setGeometry(30, 35, 120, 60);
  confirmButtonsBox->show();
  // Create label
  QLabel* confirmLabel = new QLabel();
  QFont font(confirmLabel->font());
  font.setBold(false);
  font.setPointSize(10);
  confirmLabel->setFont(font);
  confirmLabel->setText("Are you sure?");
  confirmLabel->setGeometry(10, 10, 180, 30);
  confirmLabel->setParent(Dialog);
  confirmLabel->show();

  if (Dialog->exec() == QDialog::Accepted) return true;
  return false;
}

void MainWindow::load() {
  QString file_name = QFileDialog::getOpenFileName(
      this, tr("Select a file"),
      QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
      tr("Open CSV (*.csv);;Open JSON (*.json);;"));
  if (file_name.isEmpty()) return;
  if (file_name.endsWith(".csv")) {
    StrategyIO* loader = new StrategyIO_CSV;
    loader->load(file_name);
    delete loader;
  }
  if (file_name.endsWith(".json")) {
    StrategyIO* loader = new StrategyIO_JSON;
    loader->load(file_name);
    delete loader;
  }
  if (file_name.endsWith(".db")) {
    StrategyIO* loader = new StrategyIO_DB;
    loader->load(file_name);
    delete loader;
  }
}

void MainWindow::save() {}

void MainWindow::Redraw() { plot->draw(ui->customPlot); }

void MainWindow::deletePlot() {
  int index = ui->tabWidgetPlots->currentIndex();
  ui->tabWidgetPlots->removeTab(index);
}

void MainWindow::addPlot() {
  int count = ui->tabWidgetPlots->count();
  ui->tabWidgetPlots->addTab(new QCustomPlot,
                             "Plot " + QString::number(count + 1));
}

void MainWindow::addColumn() {
  ui->tableViewMain->model()->insertColumns(
      lib::Manager::getInstance()->getVariablesCount(), 1);
  ui->tableViewNaming->model()->insertRows(
      lib::Manager::getInstance()->getVariablesCount(), 1);
  ui->tableViewPlotsSets->model()->insertRows(
      lib::Manager::getInstance()->getVariablesCount(), 1);
  ui->tableViewErrors->model()->insertRows(
      lib::Manager::getInstance()->getVariablesCount(), 1);
}

void MainWindow::deleteColumn() {
  int index_column = ui->tableViewMain->currentIndex().column();
  if (index_column == -1) index_column = 0;
  ui->tableViewMain->model()->removeColumns(index_column, 1);
  ui->tableViewNaming->model()->removeRows(index_column, 1);
  ui->tableViewPlotsSets->model()->removeRows(index_column, 1);
  ui->tableViewErrors->model()->removeRows(index_column, 1);
}

void MainWindow::addRow() {
  ui->tableViewMain->model()->insertRows(
      lib::Manager::getInstance()->getMeasurementsCount(), 1);
}

void MainWindow::deleteRow() {
  ui->tableViewMain->model()->removeRows(
      lib::Manager::getInstance()->getMeasurementsCount(), 1);
}

#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "QStandardPaths"
#include "manager.h"
#include "plot_models/line_plot.h"
#include "plot_models/dot_plot.h"
#include "qcustomplot.h"
#include "strategyIO.h"
#include "table_models/delegates/color_delegate.h"
#include "table_models/delegates/combobox_delegate.h"
#include "table_models/errors_table.h"
#include "table_models/measurements_table.h"
#include "table_models/naming_table.h"
#include "table_models/plot_settings_table.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->tabWidgetPlots->addTab(new QCustomPlot, "DotPlot");

  setWindowIcon(QIcon("C:/2024_Experiments/images/mainwindow.png"));
  setWindowTitle("Data Handler");

  lib::Variable Foo({1, 2, 3, 4, 5}, lib::Variable::Naming("Foo"),
                    lib::Variable::VisualOptions(true, 4));
  lib::Variable bar({4, 2, 11, 3, 5, 1}, lib::Variable::Naming("bar", "x"));

  lib::Manager::GetInstance()->AddVariable(Foo);
  lib::Manager::GetInstance()->AddVariable(bar);

  SetupTables();

  ConnectingAction();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ConfirmDeleteVariable() {
  if (ui->tableViewMain->selectionModel()->hasSelection() &&
      ConfirmingAction("Are you sure you want to delete this variable?")) {
    lib::Manager::GetInstance()->DeleteVariable(
        ui->tableViewMain->currentIndex().column());
  }
}

void MainWindow::ConfirmDeleteMeasurments() {
  if (ui->tableViewMain->selectionModel()->hasSelection() &&
      ConfirmingAction("Are you sure you want to delete these measurements?")) {
    lib::Manager::GetInstance()->DeleteMeasurements(
        ui->tableViewMain->currentIndex().row());
  }
}

bool MainWindow::ConfirmingAction(QString delete_message) {
  QDialog dialog;
  dialog.setFixedSize(380, 90);
  dialog.setWindowFlag(Qt::SubWindow);
  dialog.setWindowTitle(" Data Handler");

  QDialogButtonBox button_box(QDialogButtonBox::Yes | QDialogButtonBox::Cancel);
  button_box.setGeometry(65, 40, 200, 50);
  button_box.setParent(&dialog);
  button_box.show();

  QLabel text_label;
  text_label.setGeometry(54, 8, 326, 32);
  text_label.setFont(QFont("Times", 10));
  text_label.setText(delete_message);
  text_label.setParent(&dialog);
  text_label.show();

  QLabel icon_label;
  icon_label.setGeometry(16, 8, 32, 32);
  icon_label.setPixmap(QPixmap("C:/2024_Experiments/images/warning.png"));
  icon_label.setParent(&dialog);
  icon_label.show();

  connect(&button_box, SIGNAL(accepted()), &dialog, SLOT(accept()));
  connect(&button_box, SIGNAL(rejected()), &dialog, SLOT(reject()));

  return dialog.exec() == QDialog::Accepted ? true : false;
}

void MainWindow::Load() {
  QString file_name = QFileDialog::getOpenFileName(
      this, tr("Select a file"),
      QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
      tr("Open CSV (*.csv);;Open JSON (*.json);;"));
  if (file_name.isEmpty()) return;
  if (file_name.endsWith(".csv")) {
    lib::StrategyIO* loader = new lib::StrategyIO_CSV;
    loader->Load(file_name);
    delete loader;
  }
  if (file_name.endsWith(".json")) {
    lib::StrategyIO* loader = new lib::StrategyIO_JSON;
    loader->Load(file_name);
    delete loader;
  }
  if (file_name.endsWith(".db")) {
    lib::StrategyIO* loader = new lib::StrategyIO_DB;
    loader->Load(file_name);
    delete loader;
  }
}

void MainWindow::Save() {
  QString file_name = QFileDialog::getOpenFileName(
      this, tr("Select a file"),
      QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
      tr("Open CSV (*.csv);;Open JSON (*.json);;"));
  if (file_name.isEmpty()) return;
  if (file_name.endsWith(".csv")) {
    lib::StrategyIO* saver = new lib::StrategyIO_CSV;
    saver->Save(file_name);
    delete saver;
  }
  if (file_name.endsWith(".json")) {
    lib::StrategyIO* saver = new lib::StrategyIO_JSON;
    saver->Save(file_name);
    delete saver;
  }
  if (file_name.endsWith(".db")) {
    lib::StrategyIO* saver = new lib::StrategyIO_DB;
    saver->Save(file_name);
    delete saver;
  }
}

void MainWindow::DeletePlot() {
  ui->tabWidgetPlots->removeTab(ui->tabWidgetPlots->currentIndex());
}

void MainWindow::AddPlot() {
  ui->tabWidgetPlots->addTab(new QCustomPlot, "Plot");
}

void MainWindow::AddColumn() {
  dynamic_cast<lib::MeasurementsTable*>(ui->tableViewMain->model())
      ->insertColumn(lib::Manager::GetInstance()->GetVariablesCount());
  dynamic_cast<lib::NamingTable*>(ui->tableViewNaming->model())
      ->insertRow(lib::Manager::GetInstance()->GetVariablesCount());
  dynamic_cast<lib::PlotSettingsTable*>(ui->tableViewPlotsSets->model())
      ->insertRow(lib::Manager::GetInstance()->GetVariablesCount());
  dynamic_cast<lib::ErrorsTable*>(ui->tableViewErrors->model())
      ->insertRow(lib::Manager::GetInstance()->GetVariablesCount());
}

void MainWindow::DeleteColumn() {
  int index_column = ui->tableViewMain->currentIndex().column();
  if (index_column == -1) index_column = 0;
  dynamic_cast<lib::MeasurementsTable*>(ui->tableViewMain->model())
      ->removeColumn(index_column);
  dynamic_cast<lib::NamingTable*>(ui->tableViewNaming->model())
      ->removeRow(index_column);
  dynamic_cast<lib::PlotSettingsTable*>(ui->tableViewPlotsSets->model())
      ->removeRow(index_column);
  dynamic_cast<lib::ErrorsTable*>(ui->tableViewErrors->model())
      ->removeRow(index_column);
}

void MainWindow::AddRow() {
  dynamic_cast<lib::MeasurementsTable*>(ui->tableViewMain->model())
      ->insertRow(lib::Manager::GetInstance()->GetMeasurementsCount());
}

void MainWindow::DeleteRow() {
  int index_row = ui->tableViewMain->currentIndex().row();
  if (index_row == -1) index_row = 0;
  qDebug() << index_row;
  dynamic_cast<lib::MeasurementsTable*>(ui->tableViewMain->model())
      ->removeRow(index_row);
}

void MainWindow::SetupTables() {
  ui->tableViewMain->setModel(new lib::MeasurementsTable);
  ui->tableViewNaming->setModel(new lib::NamingTable);
  ui->tableViewPlotsSets->setModel(new lib::PlotSettingsTable);
  ui->tableViewErrors->setModel(new lib::ErrorsTable);

  ui->tableViewPlotsSets->setItemDelegateForColumn(
      lib::PlotSettingsTable::columns_data::kColor, new ColorDelegate);
  ui->tableViewPlotsSets->setItemDelegateForColumn(
      lib::PlotSettingsTable::columns_data::kPointShape,
      new ComboBoxDelegate(
          lib::Variable::VisualOptions::point_shapes.values()));
  ui->tableViewPlotsSets->setItemDelegateForColumn(
      lib::PlotSettingsTable::columns_data::kLineType,
      new ComboBoxDelegate(lib::Variable::VisualOptions::line_types.values()));
  ui->tableViewErrors->setItemDelegateForColumn(
      lib::ErrorsTable::columns_data::kType,
      new ComboBoxDelegate(lib::ErrorsTable::error_types.values()));

  ui->tableViewMain->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui->tableViewNaming->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui->tableViewPlotsSets->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);
  ui->tableViewErrors->horizontalHeader()->setSectionResizeMode(
      QHeaderView::ResizeToContents);

  ui->tableViewMain->show();
  ui->tableViewNaming->show();
  ui->tableViewPlotsSets->show();
  ui->tableViewErrors->show();
}

void MainWindow::UpdatePlots() {
  LinePlot* line_plot = new LinePlot("x", "y", "test");
  line_plot->Draw(qobject_cast<QCustomPlot*>(ui->tabWidgetPlots->widget(0)));
  delete line_plot;

  DotPlot* dot_plot = new DotPlot("x", "y", "test");
  dot_plot->Draw(qobject_cast<QCustomPlot*>(ui->tabWidgetPlots->widget(1)));
  delete dot_plot;
}

void MainWindow::ConnectingAction() {
  connect(ui->redrawPlotBtn, SIGNAL(clicked()), this, SLOT(UpdatePlots()));

  connect(ui->addPlotBtn, SIGNAL(clicked()), this, SLOT(AddPlot()));
  connect(ui->deletePlotBtn, SIGNAL(clicked()), this, SLOT(DeletePlot()));

  connect(ui->LoadDataBtn, SIGNAL(clicked()), this, SLOT(Load()));
  connect(ui->SaveDataBtn, SIGNAL(clicked()), this, SLOT(Save()));

  connect(ui->deleteColumnBtn, SIGNAL(clicked()), this,
          SLOT(ConfirmDeleteVariable()));
  connect(lib::Manager::GetInstance(), SIGNAL(variable_is_deleted()), this,
          SLOT(DeleteColumn()));

  connect(ui->addColumnBtn, SIGNAL(clicked()), lib::Manager::GetInstance(),
          SLOT(AddVariable()));
  connect(lib::Manager::GetInstance(), SIGNAL(variable_is_added()), this,
          SLOT(AddColumn()));

  connect(ui->deleteRowBtn, SIGNAL(clicked()), this,
          SLOT(ConfirmDeleteMeasurments()));
  connect(lib::Manager::GetInstance(), SIGNAL(measurements_is_deleted()), this,
          SLOT(DeleteRow()));

  connect(ui->addRowBtn, SIGNAL(clicked()), lib::Manager::GetInstance(),
          SLOT(AddMeasurements()));
  connect(lib::Manager::GetInstance(), SIGNAL(measurements_is_added()), this,
          SLOT(AddRow()));
}

#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "QStandardPaths"
#include "manager.h"
#include "manager_odf/manager_odf.h"
#include "plot_models/column_plot.h"
#include "plot_models/histogram.h"
#include "plot_models/histogram_2d.h"
#include "plot_models/line_plot.h"
#include "plot_models/options_histogram.h"
#include "plot_models/options_histogram_2d.h"
#include "plot_models/options_scatter_2d.h"
#include "plot_models/scatter_plot.h"
#include "plot_models/scatter_plot_2d.h"
#include "qcustomplot.h"
#include "sqlite_database/db_form.h"
#include "sqlite_database/sqlite.h"
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

  setWindowIcon(QIcon("C:/2024_Experiments/images/mainwindow.png"));
  setWindowTitle("Data Handler");

  lib::Variable Foo({1, 2, 3, 4, 5}, lib::Variable::Naming("Foo"),
                    lib::Variable::VisualOptions(true, 1, {255, 0, 0},
                                                 QCPScatterStyle::ssCircle));
  lib::Variable bar({4, 2, 11, 3, 5, 1}, lib::Variable::Naming("bar"),
                    lib::Variable::VisualOptions(true, 1, {83, 204, 101},
                                                 QCPScatterStyle::ssCircle));
  lib::Variable var({5, 3, 3, 2, 6, 1}, lib::Variable::Naming("var"),
                    lib::Variable::VisualOptions(true, 1, {42, 182, 204},
                                                 QCPScatterStyle::ssCircle));

  lib::Manager::GetInstance()->AddVariable(Foo);
  lib::Manager::GetInstance()->AddVariable(bar);
  lib::Manager::GetInstance()->AddVariable(var);

  SetupTables();

  ConnectingAction();

  UpdatePlots();

  RescalePlots();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ConfirmDeleteVariables() {
  QList<int> column_indexes;
  for (int i = lib::Manager::GetInstance()->GetVariablesCount(); i > -1; i--)
    if (ui->tableViewMain->selectionModel()->isColumnSelected(i))
      column_indexes.push_back(i);

  QString str;

  if (column_indexes.size() == 1)
    str = "Are you sure you want to delete this variable?";
  else
    str = "Are you sure you want to delete these variables? (" +
          QVariant(column_indexes.size()).toString() + ")";

  if (!column_indexes.isEmpty() && ConfirmingAction(str)) {
    for (int i : column_indexes) lib::Manager::GetInstance()->DeleteVariable(i);
    UpdatePlots();
  }
}

void MainWindow::ConfirmDeleteMeasurments() {
  QList<int> rows_indexes;
  for (int i = lib::Manager::GetInstance()->GetMeasurementsCount(); i > 0; i--)
    if (ui->tableViewMain->selectionModel()->isRowSelected(i - 1))
      rows_indexes.push_back(i - 1);

  QString str = "Are you sure you want to delete these \nmeasurements: ";

  for (int i = rows_indexes.size(); i > 0 && i > rows_indexes.size() - 6; i--) {
    str += QVariant(rows_indexes[i - 1] + 1).toString();
    if (i != 1) str += ", ";
  }

  rows_indexes.size() < 7
      ? str += "?"
      : str +=
        "... (and " + QVariant(rows_indexes.size() - 6).toString() + " more) ?";

  if (!rows_indexes.isEmpty() && ConfirmingAction(str)) {
    for (int i : rows_indexes)
      lib::Manager::GetInstance()->DeleteMeasurements(i);
    UpdatePlots();
  }
}

void MainWindow::ClearData() {
  if (lib::Manager::GetInstance()->GetMeasurementsCount() > 0 &&
      ConfirmingAction("Are you sure to clear all data?"))
    lib::Manager::GetInstance()->Clear();
  UpdatePlots();
}

bool MainWindow::ConfirmingAction(QString delete_message) {
  QMessageBox message_box;

  message_box.setWindowTitle("  Data Handler");
  message_box.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint |
                             Qt::WindowTitleHint);
  message_box.setIconPixmap(QPixmap("C:/2024_Experiments/images/warning.png"));
  message_box.setFont(QFont("Helvetica", 10));
  message_box.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
  message_box.setDefaultButton(QMessageBox::Yes);
  message_box.setText(delete_message);

  return message_box.exec() == QMessageBox::Yes ? true : false;
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
  ui->ObjectLinePlot->Draw();
  ui->ObjectScatterPlot->Draw();
  ui->ObjectColumnPlot->Draw();
  ui->ObjectHistogram->Draw();
  ui->ObjectScatterPlot2D->Draw();
  ui->ObjectHistogram2D->Draw();
}

void MainWindow::RescalePlots() {
  for (int i = 0; i < ui->tabWidgetPlots->count(); i++)
    AbstractPlotModel::Rescale(
        qobject_cast<QCustomPlot*>(ui->tabWidgetPlots->widget(i)));
}

void MainWindow::OptionsPlot() {
  int index = ui->tabWidgetPlots->currentIndex();

  switch (index) {
    case 0:
      // nothing
      break;
    case 1:
      // nothing
      break;
    case 2:
      // nothing
      break;
    case 3: {
      OptionsHistogram a;
      a.exec();
      ui->ObjectHistogram->set(a.choose_variable(), a.choose_column_size());
      break;
    }
    case 4: {
      OptionsScatter2D a;
      a.exec();
      ui->ObjectScatterPlot2D->set(a.choose_AxisX(), a.choose_AxisY());
      break;
    }
    case 5: {
      OptionsHistogram2D a;
      a.exec();
      ui->ObjectHistogram2D->set(a.choose_AxisX(), a.choose_AxisY(),
                                 a.choose_square_size());
      break;
    }
  }
  UpdatePlots();
}

void MainWindow::ConnectingAction() {
  connect(ui->tableViewMain->model(),
          SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)), this,
          SLOT(UpdatePlots()), Qt::DirectConnection);
  connect(ui->tableViewErrors->model(),
          SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)), this,
          SLOT(UpdatePlots()), Qt::DirectConnection);
  connect(ui->tableViewNaming->model(),
          SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)), this,
          SLOT(UpdatePlots()), Qt::DirectConnection);
  connect(ui->tableViewPlotsSets->model(),
          SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)), this,
          SLOT(UpdatePlots()), Qt::DirectConnection);

  connect(ui->rescalePlotsBtn, SIGNAL(clicked()), this, SLOT(RescalePlots()));

  connect(ui->OptionsPlotBtn, SIGNAL(clicked()), this, SLOT(OptionsPlot()));

  connect(ui->deleteColumnBtn, SIGNAL(clicked()), this,
          SLOT(ConfirmDeleteVariables()));
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

  connect(ui->ClearDataBtn, SIGNAL(clicked()), this, SLOT(ClearData()));

  connect(ui->uploadToDatabaseBtn, SIGNAL(clicked()), this,
          SLOT(AddToDatabase()));

  connect(ui->actionDarkTheme, SIGNAL(triggered()), this, SLOT(DarkThemeOn()));

  connect(ui->actionLightTheme, SIGNAL(triggered()), this,
          SLOT(LightThemeOn()));

  connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(Load()));
  connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(Save()));
}

void MainWindow::on_actionCreateODF_triggered() {
  ManagerODF::GetInstance()->form->show();

  connect(ManagerODF::GetInstance()->form, SIGNAL(textBtn_is_clicked()), this,
          SLOT(AddTextBlock()));
  connect(ManagerODF::GetInstance()->form, SIGNAL(plotBtn_is_clicked()), this,
          SLOT(AddPlotBlock()));
  connect(ManagerODF::GetInstance()->form, SIGNAL(tableBtn_is_clicked()), this,
          SLOT(AddTableBlock()));
  connect(ManagerODF::GetInstance()->form, SIGNAL(AssembleBtn_is_clicked()),
          this, SLOT(AssembleODF()));
}

void MainWindow::AddTextBlock() {
  ManagerODF::GetInstance()->AddTextBlock(
      ManagerODF::GetInstance()->form->GetLayout());
}

void MainWindow::AddPlotBlock() {
  ManagerODF::GetInstance()->AddPlotBlock(
      ManagerODF::GetInstance()->form->GetLayout(),
      QPixmap(ui->ObjectLinePlot->toPixmap(256, 256)));
}

void MainWindow::AddTableBlock() {
  QList<int> column_indexes;
  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); i++)
    if (ui->tableViewMain->selectionModel()->isColumnSelected(i))
      column_indexes.push_back(i);
  if (column_indexes.isEmpty()) return;
  ManagerODF::GetInstance()->AddTableBlock(
      ManagerODF::GetInstance()->form->GetLayout(), column_indexes);
}

void MainWindow::AssembleODF() {
  QString file_name = QFileDialog::getSaveFileName(
      nullptr, QObject::tr("Save File"), "output_file.odf",
      QObject::tr("Open Document ('''.odf)"));
  if (file_name.isEmpty()) return;

  QTextDocumentWriter writer(file_name);
  writer.setFormat("odf");

  QTextDocument* document = new QTextDocument;
  QTextCursor* cursor = new QTextCursor(document);

  for (auto& block : ManagerODF::GetInstance()->blocks) block->Save(cursor);

  writer.setFormat("odf");
  writer.write(document);

  delete document;
  delete cursor;
}

void MainWindow::closeEvent(QCloseEvent* event) {
  if (lib::Manager::GetInstance()->GetVariablesCount() == 0 ||
      ConfirmingAction("Are you sure to close program?")) {
    event->accept();
    if (ManagerODF::GetInstance()->form != NULL)
      ManagerODF::GetInstance()->form->close();
  } else
    event->ignore();
}

void MainWindow::on_actionOpen_data_base_triggered() {
  lib::Manager::GetInstance()->GetSQLite().form->show();
}

void MainWindow::AddToDatabase() {
  QList<int> column_indexes;
  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); i++)
    if (ui->tableViewMain->selectionModel()->isColumnSelected(i))
      column_indexes.push_back(i);
  if (column_indexes.isEmpty()) return;
  for (int i : column_indexes)
    lib::Manager::GetInstance()->GetSQLite().AddToDatabase(
        lib::Manager::GetInstance()->GetVariable(i));
}

void MainWindow::DarkThemeOn() {
  QPalette darkPalette;

  darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
  darkPalette.setColor(QPalette::WindowText, Qt::white);
  darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
  darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
  darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
  darkPalette.setColor(QPalette::ToolTipText, Qt::white);
  darkPalette.setColor(QPalette::Text, Qt::white);
  darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
  darkPalette.setColor(QPalette::ButtonText, Qt::white);
  darkPalette.setColor(QPalette::BrightText, Qt::red);
  darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
  darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
  darkPalette.setColor(QPalette::HighlightedText, Qt::black);

  for (int i = 0; i < ui->tabWidgetPlots->count(); i++)
    AbstractPlotModel::SetDarkTheme(
        qobject_cast<QCustomPlot*>(ui->tabWidgetPlots->widget(i)));

  qApp->setPalette(darkPalette);
}

void MainWindow::LightThemeOn() {
  for (int i = 0; i < ui->tabWidgetPlots->count(); i++)
    AbstractPlotModel::SetLightTheme(
        qobject_cast<QCustomPlot*>(ui->tabWidgetPlots->widget(i)));

  qApp->setPalette(style()->standardPalette());
}

#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "IO/strategyIO.h"
#include "QStandardPaths"
#include "implementer/implementer.h"
#include "manager/manager.h"
#include "plot_models/abstractplotmodel.h"
#include "plot_models/column_plot.h"
#include "plot_models/histogram.h"
#include "plot_models/histogram_2d.h"
#include "plot_models/line_plot.h"
#include "plot_models/scatter_plot.h"
#include "plot_models/scatter_plot_2d.h"
#include "qcustomplot.h"
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

  lib::StrategyIO* loader = new lib::StrategyIO_CSV;
  loader->Load("C:/2024_Experiments/message.csv");
  delete loader;

  SetupTables();

  ConnectingAction();

  UpdatePlots();

  RescalePlots();

  DarkThemeOn();
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
      ConfirmingAction("Are you sure to clear all data?")) {
    lib::Manager::GetInstance()->Clear();
    UpdatePlots();
  }
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
  QString file_name = QFileDialog::getSaveFileName(
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
  auto plot =
      static_cast<AbstractPlotModel*>(ui->tabWidgetPlots->currentWidget());
  plot->Options();
}

void MainWindow::ConnectingAction() {
  connect(ui->tableViewMain->model(), &QAbstractTableModel::dataChanged, this,
          &MainWindow::UpdatePlots, Qt::DirectConnection);
  connect(ui->tableViewErrors->model(), &QAbstractTableModel::dataChanged, this,
          &MainWindow::UpdatePlots, Qt::DirectConnection);
  connect(ui->tableViewNaming->model(), &QAbstractTableModel::dataChanged, this,
          &MainWindow::UpdatePlots, Qt::DirectConnection);
  connect(ui->tableViewPlotsSets->model(), &QAbstractTableModel::dataChanged,
          this, &MainWindow::UpdatePlots, Qt::DirectConnection);

  connect(ui->rescalePlotsBtn, &QAbstractButton::clicked, this,
          &MainWindow::RescalePlots);
  connect(ui->optionsPlotBtn, &QAbstractButton::clicked, this,
          &MainWindow::OptionsPlot);

  connect(ui->deleteColumnBtn, &QAbstractButton::clicked, this,
          &MainWindow::ConfirmDeleteVariables);
  connect(lib::Manager::GetInstance(), &lib::Manager::variable_is_deleted, this,
          &MainWindow::DeleteColumn);

  connect(ui->addColumnBtn, &QAbstractButton::clicked,
          lib::Manager::GetInstance(), &lib::Manager::CreateNewVariable);
  connect(lib::Manager::GetInstance(), &lib::Manager::variable_is_added, this,
          &MainWindow::AddColumn);

  connect(ui->deleteRowBtn, &QAbstractButton::clicked, this,
          &MainWindow::ConfirmDeleteMeasurments);
  connect(lib::Manager::GetInstance(), &lib::Manager::measurements_is_deleted,
          this, &MainWindow::DeleteRow);

  connect(ui->addRowBtn, &QAbstractButton::clicked, lib::Manager::GetInstance(),
          &lib::Manager::AddMeasurements);
  connect(lib::Manager::GetInstance(), &lib::Manager::measurements_is_added,
          this, &MainWindow::AddRow);

  connect(ui->clearDataBtn, &QAbstractButton::clicked, this,
          &MainWindow::ClearData);

  connect(ui->uploadToDataBaseBtn, &QAbstractButton::clicked, this,
          &MainWindow::AddToDatabase);

  connect(ui->actionDarkTheme, &QAction::triggered, this,
          &MainWindow::DarkThemeOn);
  connect(ui->actionLightTheme, &QAction::triggered, this,
          &MainWindow::LightThemeOn);

  connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::Load);
  connect(ui->actionSave, &QAction::triggered, this, &MainWindow::Save);

  connect(Implementer::GetInstance()->odf_form, &ODF_Form::textBtn_is_clicked,
          this, &MainWindow::AddTextBlock);
  connect(Implementer::GetInstance()->odf_form, &ODF_Form::plotBtn_is_clicked,
          this, &MainWindow::AddPlotBlock);
  connect(Implementer::GetInstance()->odf_form, &ODF_Form::tableBtn_is_clicked,
          this, &MainWindow::AddTableBlock);
  connect(Implementer::GetInstance()->odf_form,
          &ODF_Form::assembleBtn_is_clicked, this, &MainWindow::AssembleODF);
}

void MainWindow::on_actionCreateODF_triggered() {
  Implementer::GetInstance()->odf_form->show();
}

void MainWindow::AddTextBlock() {
  Implementer::GetInstance()->AddTextBlock(
      Implementer::GetInstance()->odf_form->GetLayout());
}

void MainWindow::AddPlotBlock() {
  Implementer::GetInstance()->AddPlotBlock(
      Implementer::GetInstance()->odf_form->GetLayout(),
      QPixmap(ui->ObjectLinePlot->toPixmap(256, 256)));
}

void MainWindow::AddTableBlock() {
  QList<int> column_indexes;
  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); i++)
    if (ui->tableViewMain->selectionModel()->isColumnSelected(i))
      column_indexes.push_back(i);
  if (column_indexes.isEmpty()) return;
  Implementer::GetInstance()->AddTableBlock(
      Implementer::GetInstance()->odf_form->GetLayout(), column_indexes);
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

  for (auto& block : Implementer::GetInstance()->blocks) block->Save(cursor);

  writer.setFormat("odf");
  writer.write(document);

  delete document;
  delete cursor;
}

void MainWindow::closeEvent(QCloseEvent* event) {
  if (lib::Manager::GetInstance()->GetVariablesCount() == 0 ||
      ConfirmingAction("Are you sure to close program?")) {
    event->accept();
    if (Implementer::GetInstance()->odf_form)
      Implementer::GetInstance()->odf_form->close();
  } else
    event->ignore();
}

void MainWindow::on_actionOpenDataBase_triggered() {
  Implementer::GetInstance()->db_form->show();
}

void MainWindow::AddToDatabase() {
  QList<int> column_indexes;
  for (int i = 0; i < lib::Manager::GetInstance()->GetVariablesCount(); i++)
    if (ui->tableViewMain->selectionModel()->isColumnSelected(i))
      column_indexes.push_back(i);
  if (column_indexes.isEmpty()) return;
  for (int i : column_indexes)
    Implementer::GetInstance()->database->AddToDatabase(
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

  for (int i = 0; i < ui->tabWidgetPlots->count() - 1; i++)
    AbstractPlotModel::SetDarkTheme(
        qobject_cast<QCustomPlot*>(ui->tabWidgetPlots->widget(i)));
  Histogram2D::SetDarkTheme(qobject_cast<QCustomPlot*>(
      ui->tabWidgetPlots->widget(ui->tabWidgetPlots->count() - 1)));

  qApp->setPalette(darkPalette);
}

void MainWindow::LightThemeOn() {
  for (int i = 0; i < ui->tabWidgetPlots->count() - 1; i++)
    AbstractPlotModel::SetLightTheme(
        qobject_cast<QCustomPlot*>(ui->tabWidgetPlots->widget(i)));
  Histogram2D::SetLightTheme(qobject_cast<QCustomPlot*>(
      ui->tabWidgetPlots->widget(ui->tabWidgetPlots->count() - 1)));

  qApp->setPalette(style()->standardPalette());
}

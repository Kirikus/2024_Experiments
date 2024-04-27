#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "QStandardPaths"
#include "manager.h"
#include "manager_odf/manager_odf.h"
#include "plot_models/column_plot.h"
#include "plot_models/combo_plot.h"
#include "plot_models/dot_plot.h"
#include "plot_models/line_plot.h"
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

  ui->tabWidgetPlots->addTab(new QCustomPlot, "DotPlot");
  ui->tabWidgetPlots->addTab(new QCustomPlot, "ColumnPlot");
  ui->tabWidgetPlots->addTab(new QCustomPlot, "ComboPlot");

  setWindowIcon(QIcon("C:/2024_Experiments/images/mainwindow.png"));
  setWindowTitle("Data Handler");

  lib::Variable Foo({1, 2, 3, 4, 5}, lib::Variable::Naming("Foo"),
                    lib::Variable::VisualOptions(true, 4));
  lib::Variable bar({4, 2, 11, 3, 5, 1}, lib::Variable::Naming("bar", "x"));
  lib::Variable var({5, 3, 3, 2, 6, 1}, lib::Variable::Naming("var", "x"));

  lib::Manager::GetInstance()->AddVariable(Foo);
  lib::Manager::GetInstance()->AddVariable(bar);
  lib::Manager::GetInstance()->AddVariable(var);

  SetupTables();

  ConnectingAction();

  UpdatePlots();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::ConfirmDeleteVariables() {
  QList<int> column_indexes;
  for (int i = lib::Manager::GetInstance()->GetVariablesCount(); i > -1; i--)
    if (ui->tableViewMain->selectionModel()->isColumnSelected(i))
      column_indexes.push_back(i);
  if (!column_indexes.isEmpty() &&
      ConfirmingAction("Are you sure you want to delete this variables?"))
    for (int i : column_indexes) lib::Manager::GetInstance()->DeleteVariable(i);
}

void MainWindow::ConfirmDeleteMeasurments() {
  QList<int> rows_indexes;
  for (int i = lib::Manager::GetInstance()->GetMeasurementsCount(); i > -1; i--)
    if (ui->tableViewMain->selectionModel()->isRowSelected(i))
      rows_indexes.push_back(i);
  if (!rows_indexes.isEmpty() &&
      ConfirmingAction("Are you sure you want to delete these measurements?")) {
    for (int i : rows_indexes)
      lib::Manager::GetInstance()->DeleteMeasurements(i);
  }
}

void MainWindow::ClearData() {
  if (lib::Manager::GetInstance()->GetMeasurementsCount() > 0 &&
      ConfirmingAction("Are you sure to clear all data?"))
    lib::Manager::GetInstance()->Clear();
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

  ColumnPlot* column_plot = new ColumnPlot("x", "y", "test");
  column_plot->Draw(qobject_cast<QCustomPlot*>(ui->tabWidgetPlots->widget(2)));
  delete column_plot;

  ComboPlot* combo_plot = new ComboPlot("x", "y", "test");
  combo_plot->Draw(qobject_cast<QCustomPlot*>(ui->tabWidgetPlots->widget(3)));
  delete combo_plot;
}

void MainWindow::ConnectingAction() {
  connect(ui->redrawPlotBtn, SIGNAL(clicked()), this, SLOT(UpdatePlots()));

  connect(ui->addPlotBtn, SIGNAL(clicked()), this, SLOT(AddPlot()));
  connect(ui->deletePlotBtn, SIGNAL(clicked()), this, SLOT(DeletePlot()));

  connect(ui->LoadDataBtn, SIGNAL(clicked()), this, SLOT(Load()));
  connect(ui->SaveDataBtn, SIGNAL(clicked()), this, SLOT(Save()));

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

  connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(CreateHelpWindow()));
}

void MainWindow::on_actionCreate_ODF_triggered() {
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
      QPixmap(ui->customPlot->toPixmap(256, 256)));
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
      ConfirmingAction("Are you sure to close programm?")) {
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
  darkPalette.setColor(QPalette::Base, QColor(40, 40, 40));
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

  AbstractPlotModel::SetDarkTheme(
      qobject_cast<QCustomPlot*>(ui->tabWidgetPlots->widget(0)));
  AbstractPlotModel::SetDarkTheme(
      qobject_cast<QCustomPlot*>(ui->tabWidgetPlots->widget(1)));
  AbstractPlotModel::SetDarkTheme(
      qobject_cast<QCustomPlot*>(ui->tabWidgetPlots->widget(2)));
  AbstractPlotModel::SetDarkTheme(
      qobject_cast<QCustomPlot*>(ui->tabWidgetPlots->widget(3)));

  qApp->setPalette(darkPalette);
}

void MainWindow::LightThemeOn() {
  AbstractPlotModel::SetLightTheme(
      qobject_cast<QCustomPlot*>(ui->tabWidgetPlots->widget(0)));
  AbstractPlotModel::SetLightTheme(
      qobject_cast<QCustomPlot*>(ui->tabWidgetPlots->widget(1)));
  AbstractPlotModel::SetLightTheme(
      qobject_cast<QCustomPlot*>(ui->tabWidgetPlots->widget(2)));
  AbstractPlotModel::SetLightTheme(
      qobject_cast<QCustomPlot*>(ui->tabWidgetPlots->widget(3)));

  qApp->setPalette(style()->standardPalette());
}

void MainWindow::CreateHelpWindow() {
  QMessageBox message;
  QPixmap pix(QSize(720, 560));
  pix.fill(QColor(255, 255, 255));
  message.setIconPixmap(pix);
  message.setWindowFlag(Qt::Window);
  message.setWindowIcon(QIcon("C:/2024_Experiments/images/mainwindow.png"));
  message.setWindowTitle(" Data Handler");
  message.exec();
}

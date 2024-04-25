#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QFile>
#include <QFileDialog>
#include <QFont>
#include <QJsonObject>
#include <QJsonParseError>
#include <QLabel>
#include <QMainWindow>
#include <QStandardItem>

#include "manager_odf/odf_form.h"
#include "plot_models/abstractplotmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  bool ConfirmingAction(QString);
  void ConfirmDeleteMeasurments();
  void ConfirmDeleteVariable();

  void Load();
  void Save();

  void OptionsPlot();

  void AddColumn();
  void DeleteColumn();

  void AddRow();
  void DeleteRow();

  void SetupTables();

  void UpdatePlots();

  void ConnectingAction();

  void on_actionCreate_ODF_triggered();

  void AddTextBlock();
  void AddPlotBlock();
  void AddTableBlock();

  void AssembleODF();

  void closeEvent(QCloseEvent *event);

  void on_actionOpen_data_base_triggered();

  void AddToDatabase();

 private:
  Ui::MainWindow *ui;

  int var = 0;
  int column_size = 1;
  int AxisX = 0;
  int AxisY = 0;
  int HAxisX = 0;
  int HAxisY = 0;
  int SquareSize = 1;
};

#endif  // MAINWINDOW_H

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
  void ConfirmDeleteVariables();

  void Load();
  void Save();

  void DeletePlot();
  void AddPlot();

  void AddColumn();
  void DeleteColumns();

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

  void ClearData();

  void on_actionOpen_data_base_triggered();

  void AddToDatabase();

  void DarkThemeOn();
  void LightThemeOn();

 private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H

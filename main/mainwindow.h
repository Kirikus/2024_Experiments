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

  void DeletePlot();
  void AddPlot();

  void AddColumn();
  void DeleteColumn();

  void AddRow();
  void DeleteRow();

  void SetupTables();

  void UpdatePlots();

  void ConnectingAction();

 private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H

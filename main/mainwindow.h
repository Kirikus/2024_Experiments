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

#include "plot_models/plot.h"

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

  bool ConfirmingAction();

  void ConfirmDeleteMeasurments();

  void ConfirmDeleteVariable();

  void load();

  void save();

  void deletePlot();

  void addPlot();

  void addColumn();

  void deleteColumn();

  void addRow();

  void deleteRow();

  void Redraw();

 private:
  LinePlot *plot = new LinePlot;
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H

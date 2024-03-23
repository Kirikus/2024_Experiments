#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMainWindow>
#include <QStandardItem>

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

  void load();

  void save();

  void deletePlot();

  void addPlot();

  void addColumn();

  void deleteColumn();

  void addRow();

  void deleteRow();

 private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H

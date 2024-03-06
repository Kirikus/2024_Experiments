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

  void on_pushButton_deletePlot_clicked();

  void on_pushButton_addScatterPlot_clicked();

 private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H

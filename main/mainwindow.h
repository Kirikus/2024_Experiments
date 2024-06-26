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

  void OptionsPlot();

  void AddColumn();
  void DeleteColumn();

  void AddRow();
  void DeleteRow();

  void SetupTables();

  void UpdatePlots();

  void ZoomPlots();

  void ConnectingAction();

  void on_actionCreateODF_triggered();

  void AddTextBlock();
  void AddPlotBlock();
  void AddTableBlock();

  void AssembleODF();

  void closeEvent(QCloseEvent *event);

  void ClearData();

  void on_actionOpenDataBase_triggered();

  void AddToDatabase();

  void DarkThemeOn();
  void LightThemeOn();

  void on_tabWidgetPlots_tabBarClicked(int index);

  void AddCalculated();

private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H

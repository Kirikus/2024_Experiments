#include <QApplication>

#include "mainwindow.h"
#include "manager.h"

#include <QFile>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QFile styleSheetFile("C:/2024_Experiments/main/Theme.qss");
  styleSheetFile.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(styleSheetFile.readAll());
  a.setStyleSheet(styleSheet);

  MainWindow w;
  w.show();
  return a.exec();
}

#include <QApplication>
#include <QFile>

#include "mainwindow.h"
#include "manager.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  qApp->setStyle(QStyleFactory::create("Fusion"));

  MainWindow w;
  w.show();
  return a.exec();
}

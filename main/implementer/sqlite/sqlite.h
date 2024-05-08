#ifndef SQLITE_H
#define SQLITE_H

#include "QTableWidget"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "variable.h"

struct SQLite : QObject {
  Q_OBJECT

 public:
  SQLite();

  QSqlDatabase data;
  QSqlQuery* query;
  QTableWidget* table;

  void AddToDatabase(lib::Variable);

  void UpdateTables(QString);
  void InitializeTables();

 public slots:
  void DeleteFromDatabase();
  void UploadToManager();
};

#endif  // SQLITE_H

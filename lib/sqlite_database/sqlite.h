#ifndef SQLITE_H
#define SQLITE_H

#include "../variable.h"
#include "QTableWidget"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "db_form.h"

struct SQLite : QObject {
  Q_OBJECT

 public:
  SQLite();

  QSqlDatabase measurements_db;

  QSqlQuery* measurements_query;

  DB_Form* form;

  QTableWidget* measurements_table;

  void AddToDatabase(lib::Variable);

  void UpdateTables(QString);

  void InitializeTables();

 public slots:

  void DeleteFromDatabase();
  void UploadToManager();
};

#endif  // SQLITE_H

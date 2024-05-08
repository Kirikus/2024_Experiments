#include "sqlite.h"

#include "../implementer.h"
#include "QtSql/qsqlrecord.h"
#include "manager.h"

SQLite::SQLite() {
  data = QSqlDatabase::addDatabase("QSQLITE");
  data.setDatabaseName("./data.db");

  data.open();

  query = new QSqlQuery(data);
}

void SQLite::AddToDatabase(lib::Variable variable) {
  for (auto title : data.tables())
    if (variable.naming.title == title) return;

  query->exec("CREATE TABLE " + variable.naming.title + "(measurements real);");

  for (int i : variable.measurements)
    query->exec("INSERT INTO " + variable.naming.title +
                " (measurements) VALUES (" + QVariant(i).toString() + ")");

  UpdateTables(variable.naming.title);
}

void SQLite::DeleteFromDatabase() {
  QList<int> column_indexes;
  for (int i = 0; i < data.tables().size(); i++)
    if (table->selectionModel()->isColumnSelected(i))
      column_indexes.push_front(i);
  if (column_indexes.isEmpty()) return;
  for (int i : column_indexes) {
    table->removeColumn(i);
    query->exec("DROP TABLE " + data.tables()[i]);
  }
  if (table->columnCount()) return;
  while (table->rowCount()) table->removeRow(0);
}

void SQLite::UploadToManager() {
  QList<int> column_indexes;
  for (int i = 0; i < data.tables().size(); i++)
    if (table->selectionModel()->isColumnSelected(i))
      column_indexes.push_back(i);
  if (column_indexes.isEmpty()) return;
  for (int i : column_indexes) {
    lib::Variable variable;
    query->exec("select * from " + data.tables()[i]);
    while (query->next()) {
      variable.measurements.push_back(query->value(0).toDouble());
    }
    lib::Manager::GetInstance()->AddVariable(variable);
  }
}

void SQLite::UpdateTables(QString title) {
  table->insertColumn(table->columnCount());
  table->setColumnCount(table->columnCount());
  table->setHorizontalHeaderItem(table->columnCount() - 1,
                                 new QTableWidgetItem(title));
  for (auto i : data.tables()) {
    query->exec("select * from " + i);
    query->last();
    int first = query->at() + 1;
    query->exec("select * from " + title);
    query->last();
    int second = query->at();
    if (table->columnCount() == 1)
      for (int j = 0; j < first; j++) table->insertRow(table->rowCount());
    else if (second > first) {
      for (int j = 0; j < second - first; j++)
        table->insertRow(table->rowCount());
      table->setRowCount(table->rowCount());
    }
  }
  query->exec("select * from " + title);
  int i = 0;
  while (query->next()) {
    QTableWidgetItem* newItem =
        new QTableWidgetItem(query->value(0).toString());
    table->setItem(i, table->columnCount() - 1, newItem);
    i++;
  }
}

void SQLite::InitializeTables() {
  int iter = 0;
  if (data.tables().isEmpty()) return;
  while (table->columnCount() < data.tables().size()) {
    table->insertColumn(table->columnCount());
    table->setHorizontalHeaderItem(table->columnCount() - 1,
                                   new QTableWidgetItem(data.tables()[iter]));
    iter++;
  }

  int max_size = 0;
  for (auto i : data.tables()) {
    query->exec("select * from " + i);
    query->last();
    max_size = std::max(query->at() + 1, max_size);
  }
  for (int i = 0; i < max_size; i++) table->insertRow(table->rowCount());

  for (int i = 0; i < data.tables().size(); i++) {
    query->exec("select * from " + data.tables()[i]);
    int j = 0;
    while (query->next()) {
      QTableWidgetItem* newItem =
          new QTableWidgetItem(query->value(0).toString());
      table->setItem(j, i, newItem);
      j++;
    }
  }
}

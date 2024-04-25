#include "sqlite.h"

#include "../manager.h"
#include "qsqlrecord.h"

SQLite::SQLite() {
  measurements_db = QSqlDatabase::addDatabase("QSQLITE");
  measurements_db.setDatabaseName("./measurements_db.db");

  measurements_db.open();

  form = new DB_Form();

  measurements_table = form->GetMeasurementsTableWidget();

  measurements_query = new QSqlQuery(measurements_db);

  InitializeTables();

  connect(form, SIGNAL(deleteBtn_is_clicked()), this,
          SLOT(DeleteFromDatabase()));
  connect(form, SIGNAL(uploadBtn_is_clicked()), this, SLOT(UploadToManager()));
}

void SQLite::AddToDatabase(lib::Variable variable) {
  for (auto title : measurements_db.tables())
    if (variable.naming.title == title) return;

  measurements_query->exec("CREATE TABLE " + variable.naming.title +
                           "(measurements real);");

  for (int i : variable.measurements)
    measurements_query->exec("INSERT INTO " + variable.naming.title +
                             " (measurements) VALUES (" +
                             QVariant(i).toString() + ")");

  UpdateTables(variable.naming.title);
}

void SQLite::DeleteFromDatabase() {
  QList<int> column_indexes;
  for (int i = 0; i < measurements_db.tables().size(); i++)
    if (measurements_table->selectionModel()->isColumnSelected(i))
      column_indexes.push_front(i);
  if (column_indexes.isEmpty()) return;
  for (int i : column_indexes) {
    measurements_table->removeColumn(i);
    measurements_query->exec("DROP TABLE " + measurements_db.tables()[i]);
  }
  if (measurements_table->columnCount()) return;
  while (measurements_table->rowCount()) measurements_table->removeRow(0);
}

void SQLite::UploadToManager() {
  QList<int> column_indexes;
  for (int i = 0; i < measurements_db.tables().size(); i++)
    if (measurements_table->selectionModel()->isColumnSelected(i))
      column_indexes.push_back(i);
  if (column_indexes.isEmpty()) return;
  for (int i : column_indexes) {
    lib::Variable variable;
    measurements_query->exec("select * from " + measurements_db.tables()[i]);
    while (measurements_query->next()) {
      variable.measurements.push_back(measurements_query->value(0).toDouble());
    }
    lib::Manager::GetInstance()->AddVariable(variable);
  }
}

void SQLite::UpdateTables(QString title) {
  measurements_table->insertColumn(measurements_table->columnCount());
  measurements_table->setColumnCount(measurements_table->columnCount());
  measurements_table->setHorizontalHeaderItem(
      measurements_table->columnCount() - 1, new QTableWidgetItem(title));
  for (auto i : measurements_db.tables()) {
    measurements_query->exec("select * from " + i);
    measurements_query->last();
    int first = measurements_query->at() + 1;
    measurements_query->exec("select * from " + title);
    measurements_query->last();
    int second = measurements_query->at();
    if (measurements_table->columnCount() == 1)
      for (int j = 0; j < first; j++)
        measurements_table->insertRow(measurements_table->rowCount());
    else if (second > first) {
      for (int j = 0; j < second - first; j++)
        measurements_table->insertRow(measurements_table->rowCount());
      measurements_table->setRowCount(measurements_table->rowCount());
    }
  }
  measurements_query->exec("select * from " + title);
  int i = 0;
  while (measurements_query->next()) {
    QTableWidgetItem* newItem =
        new QTableWidgetItem(measurements_query->value(0).toString());
    measurements_table->setItem(i, measurements_table->columnCount() - 1,
                                newItem);
    i++;
  }
}

void SQLite::InitializeTables() {
  int iter = 0;
  if (measurements_db.tables().isEmpty()) return;
  while (measurements_table->columnCount() < measurements_db.tables().size()) {
    measurements_table->insertColumn(measurements_table->columnCount());
    measurements_table->setHorizontalHeaderItem(
        measurements_table->columnCount() - 1,
        new QTableWidgetItem(measurements_db.tables()[iter]));
    iter++;
  }

  int max_size = 0;
  for (auto i : measurements_db.tables()) {
    measurements_query->exec("select * from " + i);
    measurements_query->last();
    max_size = std::max(measurements_query->at() + 1, max_size);
  }
  for (int i = 0; i < max_size; i++)
    measurements_table->insertRow(measurements_table->rowCount());

  for (int i = 0; i < measurements_db.tables().size(); i++) {
    measurements_query->exec("select * from " + measurements_db.tables()[i]);
    int j = 0;
    while (measurements_query->next()) {
      QTableWidgetItem* newItem =
          new QTableWidgetItem(measurements_query->value(0).toString());
      measurements_table->setItem(j, i, newItem);
      j++;
    }
  }
}

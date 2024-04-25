#ifndef MANAGER_H
#define MANAGER_H

#include "QList"
#include "sqlite_database/sqlite.h"
#include "variable.h"

namespace lib {

class Manager : public QObject {
  Q_OBJECT

 private:
  QList<Variable> variables;
  QList<Variable> calculated;
  SQLite sqlite;

 public:
  static class Manager* GetInstance();

  void AugmentVariables();

  size_t GetVariablesCount() const { return variables.size(); }
  size_t GetMeasurementsCount() const;

  Variable& GetVariable(size_t index) { return variables[index]; }

  void ClearCalculated();
  void AddCalculated(Variable&);

  void Clear();

  SQLite& GetSQLite() { return sqlite; }

 public slots:
  void DeleteVariable(int index = 0);
  void AddVariable(const Variable& = Variable());
  void AddMeasurements();
  void DeleteMeasurements(int index = 0);

 signals:
  void variable_is_deleted();
  void variable_is_added();
  void measurements_is_deleted();
  void measurements_is_added();
};

}  // namespace lib

#endif  // MANAGER_H

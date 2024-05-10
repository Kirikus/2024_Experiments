#ifndef MANAGER_H
#define MANAGER_H

#include "QList"

#include "string"
#include "variable/variable.h"

namespace lib {

class Manager : public QObject {
  Q_OBJECT

 private:
  QList<Variable> variables;
  QList<Variable> calculated;

 public:
  static class Manager* GetInstance();

  void AugmentVariables();

  size_t GetVariablesCount() const { return variables.size(); }
  size_t GetMeasurementsCount() const;

  Variable& GetVariable(size_t index) { return variables[index]; }

  Variable& GetVariable(std::string name);

  void ClearCalculated();
  void AddCalculated(const Variable& = Variable());

  void Clear();

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

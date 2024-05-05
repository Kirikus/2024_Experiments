#ifndef MANAGER_H
#define MANAGER_H

#include "QList"
#include "string"
#include "variable.h"

namespace lib {

class Manager : public QObject {
  Q_OBJECT

 private:
  QList<Variable> variables;
  QList<Variable> calculated;

 public:
  static class Manager* GetInstance();

  Manager() {
    GetInstance()->AddVariable(Variable({1, 2, 3, 4, 5}, Variable::Naming("Foo")));

    GetInstance()->AddVariable(Variable({1, 2, 3, 4, 5}, Variable::Naming("Bar")));
  }

  void AugmentVariables();

  size_t GetVariablesCount() const { return variables.size(); }
  size_t GetMeasurementsCount() const;

  Variable& GetVariable(size_t index) { return variables[index]; }

  Variable& GetVariable(std::string name);

  void ClearCalculated();
  void AddCalculated(Variable&);

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

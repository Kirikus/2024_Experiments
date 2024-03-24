#ifndef MANAGER_H
#define MANAGER_H

#include "QList"
#include "formula_parser.h"
#include "variable.h"

namespace lib {

class Manager : public QObject {
  Q_OBJECT
 private:
  QList<Variable> variables;
  QList<Variable> calculated;

 public:
  static class Manager* getInstance();

  void augmentVariables();

  size_t getVariablesCount() const { return variables.size(); }
  size_t getMeasurementsCount() const;

  Variable& getVariable(size_t Column_index) { return variables[Column_index]; }
  QVector<double>& getVariableMeasurements(size_t Column_index) {
    return variables[Column_index].measurements;
  }

  void clearCalculated();
  void addCalculated(Variable&);

  void clear();
 public slots:
  void deleteVariable();
     void addVariable(const Variable& = Variable({0}));
  void addMeasurements();
  void deleteMeasurements();
 signals:
  void Variable_is_deleted();
  void Variable_is_added();
  void Measurements_is_deleted();
  void Measurements_is_added();
};

}  // namespace lib

#endif  // MANAGER_H

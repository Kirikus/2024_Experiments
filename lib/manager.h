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

  void addVariable(const Variable&);
  void deleteVariable();
  void augmentVariables();

  size_t getVariablesCount() const { return variables.size(); }
  size_t getMeasurementsCount() const;

  Variable& getVariable(size_t Column_index) { return variables[Column_index]; }

  void addMeasurementsRow();
  void removeMeasurementsRow();

  void clearCalculated();
  void addCalculated(Variable&);
 signals:
  void Variable_is_deleted();
};

}  // namespace lib

#endif  // MANAGER_H

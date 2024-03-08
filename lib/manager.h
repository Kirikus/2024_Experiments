#ifndef MANAGER_H
#define MANAGER_H

#include "QList"
#include "formula_parser.h"
#include "variable.h"

namespace lib {

class Manager {
 private:
  QList<Variable> variables;
  QList<Variable> calculated;
  size_t MeasurementsCount = 0;

 public:
  static class Manager* getInstance();

  void addVariable(const Variable&);
  void deleteVariable();

  size_t getVariablesCount() const { return variables.size(); }
  size_t getMeasurementsCount() const { return MeasurementsCount; }

  Variable& getVariable(size_t Column_index) { return variables[Column_index]; }

  void calculateMeasurementsCount();

  void addMeasurementsRow();
  void removeMeasurementsRow();

  void clearCalculated();
  void addCalculated(Variable&);
};

}  // namespace lib

#endif  // MANAGER_H
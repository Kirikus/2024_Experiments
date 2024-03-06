#ifndef MANAGER_H
#define MANAGER_H

#include "QList"
#include "formula_parser.h"
#include "variable_data.h"

namespace lib {

class Manager {
 private:
  QList<VariableData> variables;
  QList<VariableData> calculated;

 public:
  static class Manager* getInstance();

  void addVariableData(VariableData&);
  void deleteVariable();
  void addMeasurementsRow();
  void removeMeasurementsRow();
  void clearCalculated();
  void addCalculated(VariableData&);
};

}  // namespace lib

#endif  // MANAGER_H

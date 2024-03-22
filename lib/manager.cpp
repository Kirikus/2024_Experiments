#include "manager.h"

#include <QGlobalStatic>

Q_GLOBAL_STATIC(lib::Manager, instance)

lib::Manager* lib::Manager::getInstance() { return instance; }

void lib::Manager::addVariable(const Variable& CurrentVariable) {
  variables.append(CurrentVariable);
  augmentVariables();
}

void lib::Manager::deleteVariable() {
  if (variables.size() == 1) return;
  variables.pop_back();
  emit Variable_is_deleted();
}

void lib::Manager::augmentVariables() {
  for (size_t i = 0; i < getVariablesCount(); i++)
    while (getVariable(i).getMeasurementsCount() != getMeasurementsCount())
      variables[i].measurements.push_back(0);
}

size_t lib::Manager::getMeasurementsCount() const {
  size_t MeasurementsCount = 0;
  for (auto i = 0; i < getVariablesCount(); ++i)
    if (variables.at(i).measurements.size() > MeasurementsCount)
      MeasurementsCount = variables.at(i).measurements.size();
  return MeasurementsCount;
}

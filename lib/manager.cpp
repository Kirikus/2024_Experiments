#include "manager.h"

#include <QGlobalStatic>

Q_GLOBAL_STATIC(lib::Manager, instance)

lib::Manager* lib::Manager::getInstance() { return instance; }

void lib::Manager::addVariable(const Variable& CurrentVariable) {
  variables.append(CurrentVariable);
}

void lib::Manager::deleteVariable() {
  if (variables.size() != 0) variables.pop_back();
}

size_t lib::Manager::getMeasurementsCount() const {
  size_t MeasurementsCount = 0;
  for (auto i = 0; i < getVariablesCount(); ++i)
    if (variables.at(i).measurements.size() > MeasurementsCount)
      MeasurementsCount = variables.at(i).measurements.size();
  return MeasurementsCount;
}

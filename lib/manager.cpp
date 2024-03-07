#include "manager.h"

#include <QGlobalStatic>

Q_GLOBAL_STATIC(lib::Manager, instance)

lib::Manager* lib::Manager::getInstance() { return instance; }

void lib::Manager::addVariable(const Variable& CurrentVariable) {
  variables.append(CurrentVariable);
  calculateMeasurementsCount();
}

void lib::Manager::deleteVariable() {
  if (variables.size() != 0) variables.removeLast();
}

void lib::Manager::calculateMeasurementsCount() {
  MeasurementsCount = 0;
  for (auto i = 0; i < this->getVariablesCount(); ++i)
    if (variables.at(i).measurements.size() > MeasurementsCount)
      MeasurementsCount = variables.at(i).measurements.size();
}

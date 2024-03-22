#include "manager.h"

#include <QGlobalStatic>

Q_GLOBAL_STATIC(lib::Manager, instance)

lib::Manager* lib::Manager::getInstance() { return instance; }

void lib::Manager::addVariable(const Variable& CurrentVariable) {
  if (lib::Manager::getInstance()->getVariablesCount() == 0 &&
      CurrentVariable.measurements.size() == 0) {
    variables.append(CurrentVariable);
    addMeasurements();
    emit Variable_is_added();
  } else {
    variables.append(CurrentVariable);
    augmentVariables();
    emit Variable_is_added();
  }
}

void lib::Manager::addMeasurements() {
  size_t count = lib::Manager::getInstance()->getMeasurementsCount();
  if (lib::Manager::getInstance()->getVariablesCount() == 0) {
    addVariable(Variable({0}));
    emit Measurements_is_added();
  } else {
    for (int i = 0; i < lib::Manager::getInstance()->getVariablesCount(); i++)
      lib::Manager::getInstance()->getVariable(i).measurements.push_back(0);
    emit Measurements_is_added();
  }
}

void lib::Manager::deleteMeasurements() {
  size_t count = lib::Manager::getInstance()->getMeasurementsCount();
  if (count == 0) return;
  for (int i = 0; i < lib::Manager::getInstance()->getVariablesCount(); i++)
    if (count ==
        lib::Manager::getInstance()->getVariable(i).getMeasurementsCount())
      lib::Manager::getInstance()->getVariable(i).measurements.pop_back();
  emit Measurements_is_deleted();
}

void lib::Manager::deleteVariable() {
  if (variables.size() == 0) return;
  if (variables.size() == 1) {
    while (variables.first().getMeasurementsCount() != 0) deleteMeasurements();
    variables.pop_back();
    emit Variable_is_deleted();
  } else {
    variables.pop_back();
    emit Variable_is_deleted();
  }
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

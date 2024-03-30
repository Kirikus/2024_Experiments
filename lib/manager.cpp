#include "manager.h"

#include <QGlobalStatic>

Q_GLOBAL_STATIC(lib::Manager, instance)

lib::Manager* lib::Manager::getInstance() { return instance; }

void lib::Manager::addVariable(const Variable& CurrentVariable) {
  if (lib::Manager::getInstance()->getVariablesCount() == 0) {
    if (CurrentVariable.measurements.size() == 0) {
      variables.append(CurrentVariable);
      addMeasurements();
      emit Variable_is_added();
    } else {
      variables.append(CurrentVariable);
      for (int i = 0; i < CurrentVariable.getMeasurementsCount(); i++)
        addMeasurements();
      emit Variable_is_added();
    }
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

void lib::Manager::deleteMeasurements(int index_row) {
  size_t count = lib::Manager::getInstance()->getMeasurementsCount();
  if (count == 0) return;
  for (int i = 0; i < lib::Manager::getInstance()->getVariablesCount(); i++)
    if (count >= index_row)
      lib::Manager::getInstance()->getVariable(i).measurements.removeAt(
          index_row);
  emit Measurements_is_deleted();
}

void lib::Manager::deleteVariable(int index_column) {
  if (variables.size() == 0) return;
  if (variables.size() == 1) {
    while (lib::Manager::getInstance()->getMeasurementsCount() != 0)
      deleteMeasurements(lib::Manager::getInstance()->getMeasurementsCount());
    variables.removeAt(index_column);
    emit Variable_is_deleted();
  } else {
    variables.removeAt(index_column);
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

void lib::Manager::clear() {
  int test = getVariablesCount();
  for (int i = 0; i < test; i++) deleteVariable(i);
}

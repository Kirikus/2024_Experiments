#include "manager.h"

#include <QGlobalStatic>

Q_GLOBAL_STATIC(lib::Manager, instance)

namespace lib {

Manager* Manager::GetInstance() { return instance; }

void Manager::AddVariable(const Variable& variable) {
  variables.append(variable);
  if (variables.size() == 1)
    if (variable.measurements.isEmpty())
      AddMeasurements();
    else
      for (int i = 0; i < variable.GetMeasurementsCount(); i++)
        emit measurements_is_added();
  AugmentVariables();
  emit variable_is_added();
}

void Manager::AddMeasurements() {
  if (variables.isEmpty())
    AddVariable();
  else
    for (int i = 0; i < GetVariablesCount(); i++)
      GetVariable(i).measurements.push_back(0);
  emit measurements_is_added();
}

void Manager::DeleteMeasurements(int index) {
  if (GetMeasurementsCount() == 0) return;
  for (int i = 0; i < GetVariablesCount(); i++)
    GetVariable(i).measurements.removeAt(index);
  emit measurements_is_deleted();
}

void Manager::DeleteVariable(int index) {
  if (variables.isEmpty()) return;
  if (variables.size() == 1)
    while (GetMeasurementsCount() != 0) DeleteMeasurements();
  variables.removeAt(index);
  emit variable_is_deleted();
}

void Manager::AugmentVariables() {
  for (size_t i = 0; i < GetVariablesCount(); i++)
    while (GetVariable(i).GetMeasurementsCount() != GetMeasurementsCount())
      variables[i].measurements.push_back(0);
}

size_t Manager::GetMeasurementsCount() const {
  size_t MeasurementsCount = 0;
  for (size_t i = 0; i < GetVariablesCount(); i++)
    if (variables[i].measurements.size() > MeasurementsCount)
      MeasurementsCount = variables[i].measurements.size();
  return MeasurementsCount;
}

Variable& Manager::GetVariable(std::string name) {
  for (int i = 0; i < GetVariablesCount(); i++)
    if (GetVariable(i).naming.title == QString::fromStdString(name) ||
        GetVariable(i).naming.tag == QString::fromStdString(name)) {
      qDebug() << "mama";
      return GetVariable(i);
    }
}

void Manager::Clear() {
  while (GetVariablesCount() != 0) DeleteVariable();
}

}  // namespace lib

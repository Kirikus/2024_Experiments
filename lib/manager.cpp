#include "manager.h"

#include <QGlobalStatic>

Q_GLOBAL_STATIC(lib::Manager, instance)

lib::Manager* lib::Manager::getInstance() { return instance; }

void lib::Manager::addVariable(const Variable& CurrentVariable) {
  variables.append(CurrentVariable);
  mx = std::max(mx, int(CurrentVariable.getMeasurementsCount()));
  augmentVariables();
}

void lib::Manager::deleteVariable() {
  if (variables.size() != 0) variables.pop_back();
}

void lib::Manager::augmentVariables() {
    for (size_t i = 0; i < getVariablesCount(); i++) {
        while (getVariable(i).getMeasurementsCount() != mx) {
            variables[i].measurements.push_back(1);
        }
    }
}

#include "manager.h"

#include <QGlobalStatic>

Q_GLOBAL_STATIC(lib::Manager, instance)

lib::Manager* lib::Manager::getInstance() { return instance; }

void lib::Manager::addVariableData(VariableData& CurrentVariableData) {
  variables.append(CurrentVariableData);
}

void lib::Manager::deleteVariable() {
  if (variables.size() != 0) variables.removeLast();
}

#include "variable.h"

lib::Variable::Variable(QList<double> measurements, QString name_full,
                        QString name_short) {
  Variable::name_full = name_full;
  Variable::name_short = name_short;
  Variable::measurements = measurements;
}

lib::Variable::Variable() {}

#include "variable.h"

lib::Variable::Variable(QString name_full, QString name_short,
                        QList<double> measurements) {
  Variable::name_full = name_full;
  Variable::name_short = name_short;
  Variable::measurements = measurements;
}

lib::Variable::Variable(size_t t) {
  for (auto i = 0; i < t; i++) measurements.append(0);
}

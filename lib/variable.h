#ifndef VARIABLE_H
#define VARIABLE_H

#include "QList"

namespace lib {

// SimpleClass
class Variable {
 public:
  QString name_full;
  QString name_short;
  QList<double> measurements;
  size_t getMeasurementsCount() { return measurements.size(); }
  Variable(QString name_full, QString name_short = "",
               QList<double> measurements = QList<double>{});
  Variable(size_t t);
};

}  // namespace lib

#endif  // VARIABLE_H

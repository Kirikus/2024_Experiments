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
  size_t getMeasurementsCount() const { return measurements.size(); }
  Variable(QString name_full, QString name_short = "",
           QList<double> measurements = QList<double>{});
  Variable();
};

}  // namespace lib

#endif  // VARIABLE_H

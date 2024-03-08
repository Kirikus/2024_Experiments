#ifndef VARIABLE_H
#define VARIABLE_H

#include "QList"

namespace lib {

// SimpleClass
class Variable {
 public:
  QList<double> measurements;
  QString name_full = "NONE";
  QString name_short = "NONE";
  size_t getMeasurementsCount() const { return measurements.size(); }
  Variable(QList<double> measurements, QString name_full = "NONE",
           QString name_short = "NONE");
  Variable();
};

}  // namespace lib

#endif  // VARIABLE_H

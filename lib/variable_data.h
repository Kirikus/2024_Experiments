#ifndef MODULE_H
#define MODULE_H

#include "QList"

namespace lib {

class VariableData {
 private:
  QList<double> measurements;
  QString name_short;
  QString name_full;
  void* instrument;  // TODO: ...
  QList<double> errors;

 public:
  VariableData(QList<double> measurements, QString name_short,
               QString name_full, void* instrument, QList<double> errors)
      : measurements(measurements),
        name_short(name_short),
        name_full(name_full),
        instrument(instrument),
        errors(errors) {}
  VariableData(QList<double> measurements)
      : measurements(measurements),
        name_short(""),
        name_full(""),
        instrument(nullptr),
        errors({}) {}
  double getX() const { return measurements[0]; }
  double getY() const { return measurements[1]; }
};

}  // namespace lib

#endif  // MODULE_H

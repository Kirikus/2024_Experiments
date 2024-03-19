#ifndef VARIABLE_H
#define VARIABLE_H

#include "QColor"
#include "QList"

namespace lib {

struct VisualOptions {
  bool visible = true;
  int width = 1;
  QColor color = "black";
};

struct Variable {
  QList<double> measurements;
  QString name_full = "NONE";
  QString name_short = "NONE";
  VisualOptions variable_visual;

  size_t getMeasurementsCount() const { return measurements.size(); }

  Variable(QList<double> measurements, QString name_full = "NONE",
           QString name_short = "NONE");
  Variable();
};

}  // namespace lib

#endif  // VARIABLE_H

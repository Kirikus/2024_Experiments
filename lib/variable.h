#ifndef VARIABLE_H
#define VARIABLE_H

#include "../qcustomplot_lib/qcustomplot.h"
#include "QColor"
#include "QList"

namespace lib {

struct VisualOptions {
  bool visible = true;
  int width = 1;
  QColor color = "black";
  QCPScatterStyle::ScatterShape point_type =
      QCPScatterStyle::ScatterShape::ssNone;
  Qt::PenStyle line_type = Qt::SolidLine;
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

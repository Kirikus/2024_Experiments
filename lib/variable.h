#ifndef VARIABLE_H
#define VARIABLE_H

#include "../qcustomplot_lib/qcustomplot.h"
#include "QColor"
#include "QList"
#include "QMap"

namespace lib {

struct VisualOptions {
  bool visible = true;
  int width = 1;
  QColor color = "black";
  QCPScatterStyle::ScatterShape point_form =
      QCPScatterStyle::ScatterShape::ssNone;
  Qt::PenStyle line_type = Qt::SolidLine;
  static QMap<Qt::PenStyle, QString> line_types;
  static QMap<QCPScatterStyle::ScatterShape, QString> point_forms;
};

struct ErrorOptions {
  double error = 1;
  bool current_error_type = true;
  static QMap<bool, QString> error_types;
};

struct Variable {
  QList<double> measurements;

  QString name_full = "NONE";
  QString name_short = "NONE";

  VisualOptions variable_visual;
  ErrorOptions variable_error;

  size_t getMeasurementsCount() const { return measurements.size(); }

  Variable(QList<double> measurements, QString name_full = "NONE",
           QString name_short = "NONE");
  Variable();
};

}  // namespace lib

#endif  // VARIABLE_H

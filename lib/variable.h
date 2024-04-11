#ifndef VARIABLE_H
#define VARIABLE_H

#include "../qcustomplot_lib/qcustomplot.h"
#include "QColor"
#include "QList"
#include "QMap"

namespace lib {

struct Variable {
  QList<double> measurements;

  struct Naming {
    QString name_full = "unnamed";
    QString name_short = "unnamed";

    Naming(QString name_full, QString name_short)
        : name_full(name_full), name_short(name_short) {}
    Naming() {}
  } naming;

  struct VisualOptions {
    bool visible = true;
    int width = 1;
    QColor color = "black";
    QCPScatterStyle::ScatterShape point_form =
        QCPScatterStyle::ScatterShape::ssNone;
    Qt::PenStyle line_type = Qt::SolidLine;
    static QMap<Qt::PenStyle, QString> line_types;
    static QMap<QCPScatterStyle::ScatterShape, QString> point_forms;

    VisualOptions(bool visible, int width, QColor color,
                  QCPScatterStyle::ScatterShape point_form,
                  Qt::PenStyle line_type)
        : visible(visible),
          width(width),
          color(color),
          point_form(point_form),
          line_type(line_type) {}
    VisualOptions() {}
  } visual;

  struct ErrorOptions {
    double error = 1;
    bool current_error_type = true;
    static QMap<bool, QString> error_types;

    ErrorOptions(double error, bool current_error_type)
        : error(error), current_error_type(current_error_type) {}
    ErrorOptions() {}
  } errors;

  size_t getMeasurementsCount() const { return measurements.size(); }

  Variable(QList<double> measurements, QString name_full = "NONE",
           QString name_short = "NONE");
  Variable();
};

}  // namespace lib

#endif  // VARIABLE_H

#ifndef VARIABLE_H
#define VARIABLE_H

#include "../qcustomplot/qcustomplot.h"
#include "QColor"
#include "QList"
#include "QMap"

namespace lib {

struct Variable {
  QList<double> measurements;

  struct Naming {
    QString title;
    QString tag;

    Naming(QString title = "unnamed", QString tag = "")
        : title(title), tag(tag) {}
  } naming;

  struct VisualOptions {
    bool visible;
    int width;
    QColor color;
    QCPScatterStyle::ScatterShape point_shape;
    Qt::PenStyle line_type;

    static QMap<Qt::PenStyle, QString> line_types;
    static QMap<QCPScatterStyle::ScatterShape, QString> point_shapes;

    VisualOptions(bool visible = true, int width = 1, QColor color = "black",
                  QCPScatterStyle::ScatterShape point_shape =
                      QCPScatterStyle::ScatterShape::ssNone,
                  Qt::PenStyle line_type = Qt::SolidLine)
        : visible(visible),
          width(width),
          color(color),
          point_shape(point_shape),
          line_type(line_type) {}
  } visual;

  struct ErrorOptions {
    double value;
    int type;

    ErrorOptions(double value = 1.0, int type = Types::kAbsolute)
        : value(value), type(type) {}

    enum Types {
      kAbsolute = 0,
      kRelative,
    };
  } error;

  bool is_calculated;

  size_t GetMeasurementsCount() const { return measurements.size(); }

  Variable(QList<double> measurements = {}, Naming naming = Naming(),
           VisualOptions visual = VisualOptions(),
           ErrorOptions error = ErrorOptions(), bool is_calculated = false)
      : measurements(measurements),
        naming(naming),
        visual(visual),
        error(error),
        is_calculated(is_calculated) {}
};

}  // namespace lib

#endif  // VARIABLE_H

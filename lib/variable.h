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

    VisualOptions(bool visible, int width, QColor color,
                  QCPScatterStyle::ScatterShape point_shape,
                  Qt::PenStyle line_type)
        : visible(visible),
          width(width),
          color(color),
          point_shape(point_shape),
          line_type(line_type) {}

    VisualOptions()
        : visible(true),
          width(1),
          color("black"),
          point_shape(QCPScatterStyle::ScatterShape::ssNone),
          line_type(Qt::SolidLine) {}
  } visual;

  struct ErrorOptions {
    int type;
    double value;

    static QMap<int, QString> types;

    ErrorOptions(double value = 1.0, int type = TypesDesign::kAbsolute)
        : value(value), type(type) {}

    enum TypesDesign {
      kAbsolute = 0,
      kRelative,
    };
  } error;

  size_t GetMeasurementsCount() const { return measurements.size(); }

  Variable(QList<double> measurements = {}, Naming naming = Naming(),
           VisualOptions visual = VisualOptions(),
           ErrorOptions error = ErrorOptions())
      : measurements(measurements),
        naming(naming),
        visual(visual),
        error(error) {}
};

}  // namespace lib

#endif  // VARIABLE_H

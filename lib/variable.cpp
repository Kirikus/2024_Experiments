#include "variable.h"

lib::Variable::Variable(QList<double> measurements, QString name_full,
                        QString name_short) {
  Variable::naming.name_full = name_full;
  Variable::naming.name_short = name_short;
  Variable::measurements = measurements;
}

lib::Variable::Variable() {}

QMap<bool, QString> lib::Variable::ErrorOptions::error_types = {
    {false, "Relative"},
    {true, "Absolute"},
};

QMap<Qt::PenStyle, QString> lib::Variable::VisualOptions::line_types = {
    {Qt::SolidLine, "Solid line"},
    {Qt::DashLine, "Dash line"},
    {Qt::DotLine, "Dot line"},
    {Qt::DashDotLine, "Dash dot line"},
    {Qt::DashDotDotLine, "Dash dot dot line"},
    {Qt::CustomDashLine, "Random dash line"},

};

QMap<QCPScatterStyle::ScatterShape, QString>
    lib::Variable::VisualOptions::point_forms = {
        {QCPScatterStyle::ScatterShape::ssNone, "Standart"},
        {QCPScatterStyle::ScatterShape::ssCross, "Cross"},
        {QCPScatterStyle::ScatterShape::ssCircle, "Circle"},
        {QCPScatterStyle::ScatterShape::ssDisc, "Disc"},
        {QCPScatterStyle::ScatterShape::ssSquare, "Square"},
        {QCPScatterStyle::ScatterShape::ssDiamond, "Rhombus"},
        {QCPScatterStyle::ScatterShape::ssStar, "Star"},
        {QCPScatterStyle::ScatterShape::ssCrossCircle, "Cross circle"},
        {QCPScatterStyle::ScatterShape::ssPlusCircle, "Plus circle"},
};

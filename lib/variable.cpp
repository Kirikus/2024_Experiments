#include "variable.h"

namespace lib {

QMap<int, QString> Variable::ErrorOptions::types = {
    {Variable::ErrorOptions::TypesDesign::kRelative, "Relative"},
    {Variable::ErrorOptions::TypesDesign::kAbsolute, "Absolute"},
};

QMap<Qt::PenStyle, QString> Variable::VisualOptions::line_types = {
    {Qt::SolidLine, "Solid line"},
    {Qt::DashLine, "Dash line"},
    {Qt::DotLine, "Dot line"},
    {Qt::DashDotLine, "Dash dot line"},
    {Qt::DashDotDotLine, "Dash dot dot line"},
    {Qt::CustomDashLine, "Random dash line"},

};

QMap<QCPScatterStyle::ScatterShape, QString>
    Variable::VisualOptions::point_shapes = {
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

}  // namespace lib

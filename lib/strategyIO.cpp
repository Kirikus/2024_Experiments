#include "strategyIO.h"

#include "manager.h"

namespace lib {

void StrategyIO_JSON::Save(const QString& output_file) {
  QFile file;
  file.setFileName(output_file);
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  QJsonArray json_array;
  for (int i = 0; i < Manager::GetInstance()->GetVariablesCount(); i++) {
    QJsonObject json_object;

    json_object["Naming"] = QJsonObject(
        {QPair("title", Manager::GetInstance()->GetVariable(i).naming.title),
         QPair("tag", Manager::GetInstance()->GetVariable(i).naming.tag)});

    json_object["Error"] = QJsonObject(
        {QPair("type", Manager::GetInstance()->GetVariable(i).error.type),
         QPair("value", Manager::GetInstance()->GetVariable(i).error.value)});

    json_object["Visual"] = QJsonObject(
        {QPair("visible",
               Manager::GetInstance()->GetVariable(i).visual.visible),
         QPair("width", Manager::GetInstance()->GetVariable(i).visual.width),
         QPair("color",
               Manager::GetInstance()->GetVariable(i).visual.color.name()),
         QPair("point_shape",
               Variable::VisualOptions::point_shapes
                   [Manager::GetInstance()->GetVariable(i).visual.point_shape]),
         QPair("line_type",
               Variable::VisualOptions::line_types
                   [Manager::GetInstance()->GetVariable(i).visual.line_type])});

    QJsonArray json_measurements;
    for (const auto& j : Manager::GetInstance()->GetVariable(i).measurements)
      json_measurements.append(j);
    json_object["Measurements"] = json_measurements;

    json_array.append(json_object);
  }
  QJsonDocument json_document(json_array);
  file.write(json_document.toJson());

  file.close();
}

void StrategyIO_JSON::Load(const QString& input_file) {
  QFile file;
  file.setFileName(input_file);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QString data = file.readAll();
  file.close();

  QList<Variable> variables;
  QList<double> measurements;

  QJsonDocument document = QJsonDocument::fromJson(data.toUtf8());
  QJsonArray json_array = document.array();
  for (int i = 0; i < json_array.size(); i++) {
    Variable variable;
    QJsonObject json_object = json_array[i].toObject();

    QJsonArray json_measurements = json_object["Measurements"].toArray();
    for (const auto& j : json_measurements)
      variable.measurements.append(j.toDouble());

    QJsonObject json_naming = json_object["Naming"].toObject();
    variable.naming = Variable::Naming(json_naming["title"].toString("unnamed"),
                                       json_naming["tag"].toString(""));

    QJsonObject json_error = json_object["Error"].toObject();
    variable.error = Variable::ErrorOptions(json_error["value"].toDouble(),
                                            json_error["type"].toInt());

    QJsonObject json_visual = json_object["Visual"].toObject();
    variable.visual = Variable::VisualOptions(
        json_visual["visible"].toBool(), json_visual["width"].toInt(),
        QColor(json_visual["color"].toString()),
        Variable::VisualOptions::point_shapes.key(
            json_visual["point_shape"].toString()),
        Variable::VisualOptions::line_types.key(
            json_visual["line_type"].toString()));

    variables.append(variable);
  }
  if (!variables.isEmpty()) {
    Manager::GetInstance()->Clear();
    for (auto i : variables) Manager::GetInstance()->AddVariable(i);
  }
}

void StrategyIO_CSV::Save(const QString& output_file) {
  QFile file;
  file.setFileName(output_file);
  file.open(QIODevice::WriteOnly | QIODevice::Text);

  QTextStream output_stream(&file);

  for (int i = 0; i < Manager::GetInstance()->GetVariablesCount(); i++) {
    for (int j = 0; j < Manager::GetInstance()->GetMeasurementsCount(); j++)
      output_stream << Manager::GetInstance()->GetVariable(i).measurements[j]
                    << ',';
    output_stream << '\n';

    output_stream << Manager::GetInstance()->GetVariable(i).naming.title << ','
                  << Manager::GetInstance()->GetVariable(i).naming.tag;
    output_stream << ',' << '\n';

    output_stream << Manager::GetInstance()->GetVariable(i).error.type << ','
                  << Manager::GetInstance()->GetVariable(i).error.value;
    output_stream << ',' << '\n';

    output_stream
        << Manager::GetInstance()->GetVariable(i).visual.visible << ','
        << Manager::GetInstance()->GetVariable(i).visual.width << ','
        << Manager::GetInstance()->GetVariable(i).visual.color.name() << ','
        << Variable::VisualOptions::point_shapes
               [Manager::GetInstance()->GetVariable(i).visual.point_shape]
        << ','
        << Variable::VisualOptions::line_types
               [Manager::GetInstance()->GetVariable(i).visual.line_type];

    if (i != Manager::GetInstance()->GetVariablesCount() - 1)
      output_stream << ',';
    output_stream << '\n';
  }
  file.close();
}

void StrategyIO_CSV::Load(const QString& input_file) {
  QFile file;
  file.setFileName(input_file);
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  Manager::GetInstance()->Clear();

  QTextStream input_stream(&file);

  while (!input_stream.atEnd()) {
    Variable variable;
    QStringList measurements = input_stream.readLine().split(u',');
    QStringList naming = input_stream.readLine().split(u',');
    QStringList error = input_stream.readLine().split(u',');
    QStringList visual = input_stream.readLine().split(u',');

    for (int i = 0; i < measurements.size() - 1; i++)
      variable.measurements.append(measurements[i].toDouble());

    variable.naming = Variable::Naming(naming[0], naming[1]);

    variable.error =
        Variable::ErrorOptions(error[1].toDouble(), error[0].toInt() == 1);

    variable.visual = Variable::VisualOptions(
        visual[0].toInt(), visual[1].toInt(), QColor(visual[2]),
        Variable::VisualOptions::point_shapes.key(visual[3]),
        Variable::VisualOptions::line_types.key(visual[4]));

    Manager::GetInstance()->AddVariable(variable);
  }
  file.close();
}

void StrategyIO_DB::Save(const QString&) {}

void StrategyIO_DB::Load(const QString&) {}

}  // namespace lib

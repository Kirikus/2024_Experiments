#include "strategyIO.h"

#include "manager.h"

void StrategyIO_JSON::save(const QString& output_file) {
  QFile file;
  file.setFileName(output_file);
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  QJsonArray json_array;
  for (int i = 0; i < lib::Manager::getInstance()->getVariablesCount(); i++) {
    QJsonObject json_object;

    json_object["Naming"] = QJsonObject(
        {QPair("full_name",
               lib::Manager::getInstance()->getVariable(i).naming.name_full),
         QPair("short_name",
               lib::Manager::getInstance()->getVariable(i).naming.name_short)});

    json_object["Errors"] = QJsonObject(
        {QPair("type", lib::Manager::getInstance()
                           ->getVariable(i)
                           .errors.current_error_type),
         QPair("value",
               lib::Manager::getInstance()->getVariable(i).errors.error)});

    json_object["Visual"] = QJsonObject(
        {QPair("visible",
               lib::Manager::getInstance()->getVariable(i).visual.visible),
         QPair("width",
               lib::Manager::getInstance()->getVariable(i).visual.width),
         QPair("color",
               lib::Manager::getInstance()->getVariable(i).visual.color.name()),
         QPair("point_form", lib::Variable::VisualOptions::point_forms
                                 [lib::Manager::getInstance()
                                      ->getVariable(i)
                                      .visual.point_form]),
         QPair("line_type", lib::Variable::VisualOptions::line_types
                                [lib::Manager::getInstance()
                                     ->getVariable(i)
                                     .visual.line_type])});
    QJsonArray json_measurements;
    for (const auto& j :
         lib::Manager::getInstance()->getVariable(i).measurements)
      json_measurements.append(j);
    json_object["Measurements"] = json_measurements;

    json_array.append(json_object);
  }
  QJsonDocument json_document(json_array);
  file.write(json_document.toJson());

  file.close();
}

void StrategyIO_JSON::load(const QString& input_file) {
  QString data;
  QFile file;
  file.setFileName(input_file);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  data = file.readAll();
  file.close();
  QList<lib::Variable> Variables;
  QList<double> measurements;

  QJsonDocument document = QJsonDocument::fromJson(data.toUtf8());
  QJsonArray json_array = document.array();
  for (int i = 0; i < json_array.size(); i++) {
    lib::Variable variable;
    QJsonObject json_object = json_array[i].toObject();

    QJsonArray json_measurements = json_object["Measurements"].toArray();
    if (json_measurements.empty()) continue;
    for (const auto& j : json_measurements)
      variable.measurements.append(j.toDouble());

    QJsonObject json_naming = json_object["Naming"].toObject();
    variable.naming =
        lib::Variable::Naming(json_naming["full_name"].toString("unnamed"),
                              json_naming["short_name"].toString("unnamed"));

    QJsonObject json_errors = json_object["Errors"].toObject();
    variable.errors = lib::Variable::ErrorOptions(
        json_errors["value"].toDouble(), json_errors["type"].toBool());

    QJsonObject json_visual = json_object["Visual"].toObject();
    variable.visual = lib::Variable::VisualOptions(
        json_visual["visible"].toBool(), json_visual["width"].toInt(),
        QColor(json_visual["color"].toString()),
        lib::Variable::VisualOptions::point_forms.key(
            json_visual["point_form"].toString()),
        lib::Variable::VisualOptions::line_types.key(
            json_visual["line_type"].toString()));

    Variables.append(variable);
  }
  if (Variables.size() != 0) {
    lib::Manager::getInstance()->clear();
    for (auto i : Variables) lib::Manager::getInstance()->addVariable(i);
  }
}

void StrategyIO_DB::save(const QString&) {}

void StrategyIO_DB::load(const QString&) {}

void StrategyIO_CSV::save(const QString&) {}

void StrategyIO_CSV::load(const QString&) {}

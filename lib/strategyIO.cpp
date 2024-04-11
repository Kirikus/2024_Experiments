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

    // variable.naming =
    // lib::Variable::Naming(json_object["Naming"].toObject());

    // variable.errors =
    // lib::Variable::ErrorOptions{json_object["Errors"].toObject()};

    // QString short_name = main_json_object["short_name"].toString();
    // QString full_name = main_json_object["full_name"].toString();
    // if (!full_name.isEmpty()) Variable.name_full = full_name;
    // if (!short_name.isEmpty()) Variable.name_short = short_name;

    // QJsonObject error_options = main_json_object["error_options"].toObject();
    // QJsonObject visual_options =
    // main_json_object["visual_options"].toObject();

    // QString error_type = error_options["type"].toString();
    // double error_value = error_options["value"].toDouble();
    // if (error_type == "absolute")
    //     Variable.variable_error.current_error_type = true;
    // if (error_type == "relative")
    //     Variable.variable_error.current_error_type = false;

    // bool visual_visible = visual_options["visible"].toBool();
    // int visual_width = visual_options["width"].toInt();

    // QJsonArray json_measurements =
    // main_json_object["measurements"].toArray(); for (const auto& j :
    // json_measurements)
    //   Variable.measurements.push_back(j.toDouble());
    // if (Variable.measurements.size() == 0) return;
    // if (error_value > 0) Variable.variable_error.error = error_value;
    // Variable.variable_visual.visible = visual_visible;
    // if (visual_width > 0) Variable.variable_visual.width = visual_width;
    // Variables.append(Variable);
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

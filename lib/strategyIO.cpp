#include "strategyIO.h"

#include "manager.h"

void StrategyIO_JSON::save(const QString&) {}

void StrategyIO_JSON::load(const QString& input_file) {
  QString data;
  QFile file;
  file.setFileName(input_file);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  data = file.readAll();
  file.close();

  QJsonDocument document = QJsonDocument::fromJson(data.toUtf8());
  QJsonObject main_json_object = document.object();

  lib::Variable variable;
  QString short_name = main_json_object["short_name"].toString();
  QString full_name = main_json_object["full_name"].toString();
  QJsonArray json_measurements = main_json_object["measurements"].toArray();
  for (const auto& j : json_measurements)
    variable.measurements.push_back(j.toDouble());
  if (variable.getMeasurementsCount() != 0)
    // TODO
    variable.name_full = full_name;
  variable.name_short = short_name;
  lib::Manager::getInstance()->deleteVariable();
  lib::Manager::getInstance()->deleteVariable();
  lib::Manager::getInstance()->addVariable(variable);
}

void StrategyIO_DB::save(const QString&) {}

void StrategyIO_DB::load(const QString&) {}

void StrategyIO_CSV::save(const QString&) {}

void StrategyIO_CSV::load(const QString&) {}

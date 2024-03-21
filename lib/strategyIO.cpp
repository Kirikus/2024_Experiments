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
}

void StrategyIO_DB::save(const QString&) {}

void StrategyIO_DB::load(const QString&) {}

void StrategyIO_CSV::save(const QString&) {}

void StrategyIO_CSV::load(const QString&) {}

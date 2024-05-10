#ifndef IMPLEMENTER_H
#define IMPLEMENTER_H

#include "odf/block/block.h"
#include "odf/odf_form.h"
#include "sqlite/db_form.h"
#include "sqlite/sqlite.h"

struct Implementer : public QObject {
  Q_OBJECT
 public:
  static class Implementer* GetInstance();
  Implementer();

  void AddPlotBlock(QVBoxLayout*, QPixmap);
  void AddTextBlock(QVBoxLayout*);
  void AddTableBlock(QVBoxLayout*, QList<int>);

  ODF_Form* odf_form;
  DB_Form* db_form;

  QList<Block*> blocks;
  SQLite* database;
};

#endif  // IMPLEMENTER_H

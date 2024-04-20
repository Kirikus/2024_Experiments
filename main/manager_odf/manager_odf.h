#ifndef MANAGER_ODF_H
#define MANAGER_ODF_H

#include "block/block.h"
#include "odf_form.h"

struct ManagerODF {
  void AddPlotBlock(QVBoxLayout*, QPixmap);
  void AddTextBlock(QVBoxLayout*);
  void AddTableBlock(QVBoxLayout*, QList<int>);

  static class ManagerODF* GetInstance();

  QList<Block*> blocks;

  ODF_Form* form = nullptr;
};

#endif  // MANAGER_ODF_H

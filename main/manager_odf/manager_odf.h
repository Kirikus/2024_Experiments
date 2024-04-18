#ifndef MANAGER_ODF_H
#define MANAGER_ODF_H

#include "block/block.h"

struct ManagerODF {
  void AddPlotBlock(QVBoxLayout*, QPixmap);
  void AddTextBlock(QVBoxLayout*);
  void AddTableBlock(QVBoxLayout*);

  static class ManagerODF* GetInstance();

  QList<Block*> blocks;
};

#endif  // MANAGER_ODF_H

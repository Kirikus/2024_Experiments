#ifndef PLOT_BLOCK_H
#define PLOT_BLOCK_H

#include "block.h"

class PlotBlock : public Block {
 public:
  PlotBlock(QVBoxLayout*, QPixmap);
  ~PlotBlock() override;

  virtual void Save(QTextCursor*) override;
  virtual void RemoveFromBlockChain(QVBoxLayout*) override;
  virtual void AddToBlockChain(QVBoxLayout*, int position) override;

 private:
  QLabel* label;
  QPixmap* pixmap;
};

#endif  // PLOT_BLOCK_H

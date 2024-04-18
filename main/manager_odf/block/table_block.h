#ifndef TABLE_BLOCK_H
#define TABLE_BLOCK_H

#include "block.h"

class TableBlock : public Block {
 public:
  TableBlock(QVBoxLayout*);
  ~TableBlock() override;

  virtual void Save(QTextCursor*) override;
  virtual void RemoveFromBlockChain(QVBoxLayout*) override;
  virtual void AddToBlockChain(QVBoxLayout*, int position) override;

 private:
  QTableWidget* table;
};

#endif  // TABLE_BLOCK_H

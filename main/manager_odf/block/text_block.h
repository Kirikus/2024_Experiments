#ifndef TEXT_BLOCK_H
#define TEXT_BLOCK_H

#include "block.h"

class TextBlock : public Block {
 public:
  TextBlock(QVBoxLayout*);
  ~TextBlock() override;

  virtual void Save(QTextCursor*) override;
  virtual void RemoveFromBlockChain(QVBoxLayout*) override;
  virtual void AddToBlockChain(QVBoxLayout*, int position) override;

 private:
  QLineEdit* text_line;
};

#endif  // TEXT_BLOCK_H

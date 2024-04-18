#ifndef BLOCK_H
#define BLOCK_H

#include <QTextCursor>

#include "QLabel"
#include "QLineEdit"
#include "QPushButton"
#include "QTableWidget"
#include "QVBoxLayout"

class Block {
 public:
  Block();
  virtual ~Block();

  virtual void Save(QTextCursor*) = 0;
  virtual void RemoveFromBlockChain(QVBoxLayout*) = 0;
  virtual void AddToBlockChain(QVBoxLayout*, int position) = 0;

 protected:
  QPushButton* deleteBtn;
  QPushButton* upBtn;
  QPushButton* downBtn;
  QHBoxLayout* layout;
};

#endif  // BLOCK_H

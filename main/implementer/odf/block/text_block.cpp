#include "text_block.h"

TextBlock::TextBlock(QVBoxLayout *block_chain)
    : Block(), text_line(new QLineEdit) {
  text_line->setFixedSize(512, 32);
  layout->addWidget(text_line);
  block_chain->addLayout(layout);
}

TextBlock::~TextBlock() { layout->removeWidget(text_line); }

void TextBlock::Save(QTextCursor *cursor) {
  cursor->insertText(text_line->text());
}

void TextBlock::RemoveFromBlockChain(QVBoxLayout *block_chain) {
  block_chain->removeItem(layout);
  text_line->hide();
  deleteBtn->hide();
  upBtn->hide();
  downBtn->hide();
}

void TextBlock::AddToBlockChain(QVBoxLayout *block_chain, int position) {
  block_chain->insertItem(position, layout);
  text_line->show();
  deleteBtn->show();
  upBtn->show();
  downBtn->show();
}

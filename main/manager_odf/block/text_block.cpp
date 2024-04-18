#include "text_block.h"

TextBlock::TextBlock(QVBoxLayout *block_chain)
    : Block(), text_line(new QLineEdit) {
  layout->addWidget(text_line);
  block_chain->addLayout(layout);
  text_line->show();
}

TextBlock::~TextBlock() { layout->removeWidget(text_line); }

void TextBlock::Save(QTextCursor *cursor) {
  cursor->insertText(text_line->text());
}

void TextBlock::RemoveFromBlockChain(QVBoxLayout *block_chain) {
  block_chain->removeItem(layout);
}

void TextBlock::AddToBlockChain(QVBoxLayout *block_chain, int position) {
  block_chain->insertItem(position, layout);
}

#include "plot_block.h"

PlotBlock::PlotBlock(QVBoxLayout *block_chain, QPixmap pixmap)
    : Block(), label(new QLabel), pixmap(new QPixmap(pixmap)) {
  label->setPixmap(pixmap);
  layout->addWidget(label);
  block_chain->addLayout(layout);
  label->show();
}

PlotBlock::~PlotBlock() { layout->removeWidget(label); }

void PlotBlock::Save(QTextCursor *) {}

void PlotBlock::RemoveFromBlockChain(QVBoxLayout *block_chain) {
  block_chain->removeItem(layout);
}

void PlotBlock::AddToBlockChain(QVBoxLayout *black_chain, int position) {
  black_chain->insertItem(position, layout);
}

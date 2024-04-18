#include "plot_block.h"

PlotBlock::PlotBlock(QVBoxLayout *block_chain, QPixmap pixmap)
    : Block(), label(new QLabel), pixmap(new QPixmap(pixmap)) {
  label->setFixedSize(256, 256);
  label->setPixmap(pixmap);
  layout->addWidget(label);
  block_chain->addLayout(layout);
}

PlotBlock::~PlotBlock() { layout->removeWidget(label); }

void PlotBlock::Save(QTextCursor *cursor) {
  QImage image = pixmap->toImage();
  cursor->document()->addResource(QTextDocument::ImageResource, QUrl("plot"),
                                  image);
  QTextImageFormat format;
  format.setQuality(100);
  format.setName("plot");

  cursor->insertImage(image);
  cursor->insertBlock();
}

void PlotBlock::RemoveFromBlockChain(QVBoxLayout *block_chain) {
  block_chain->removeItem(layout);
  label->hide();
  deleteBtn->hide();
  upBtn->hide();
  downBtn->hide();
}

void PlotBlock::AddToBlockChain(QVBoxLayout *black_chain, int position) {
  black_chain->insertItem(position, layout);
  label->show();
  deleteBtn->show();
  upBtn->show();
  downBtn->show();
}

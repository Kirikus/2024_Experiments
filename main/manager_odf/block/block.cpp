#include "block.h"

Block::Block()
    : deleteBtn(new QPushButton("delete")),
      upBtn(new QPushButton("up")),
      downBtn(new QPushButton("down")),
      layout(new QHBoxLayout) {
  layout->addWidget(deleteBtn);
  layout->addWidget(upBtn);
  layout->addWidget(downBtn);
  deleteBtn->show();
  upBtn->show();
  downBtn->show();
}

Block::~Block() {
  layout->removeWidget(deleteBtn);
  layout->removeWidget(upBtn);
  layout->removeWidget(downBtn);
  layout->disconnect();
}

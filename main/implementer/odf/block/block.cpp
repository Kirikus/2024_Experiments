#include "block.h"

#include "../../implementer.h"

Block::Block()
    : deleteBtn(new QPushButton("delete")),
      upBtn(new QPushButton("up")),
      downBtn(new QPushButton("down")),
      layout(new QHBoxLayout) {
  deleteBtn->setFixedSize(70, 50);
  upBtn->setFixedSize(70, 50);
  downBtn->setFixedSize(70, 50);
  layout->addWidget(deleteBtn);
  layout->addWidget(upBtn);
  layout->addWidget(downBtn);
  layout->setSpacing(20);

  connect(deleteBtn, SIGNAL(clicked()), this, SLOT(DeleteBlock()));
  connect(upBtn, SIGNAL(clicked()), this, SLOT(SwapUpBlock()));
  connect(downBtn, SIGNAL(clicked()), this, SLOT(SwapDownBlock()));
}

Block::~Block() {
  layout->removeWidget(deleteBtn);
  layout->removeWidget(upBtn);
  layout->removeWidget(downBtn);
  layout->disconnect();
}

void Block::DeleteBlock() {
  this->RemoveFromBlockChain(Implementer::GetInstance()->odf_form->GetLayout());
  for (int i = 0; i < Implementer::GetInstance()->blocks.size(); i++)
    if (Implementer::GetInstance()->blocks[i] == this)
      Implementer::GetInstance()->blocks.removeAt(i);
}

void Block::SwapUpBlock() {
  for (int i = 1; i < Implementer::GetInstance()->blocks.size(); i++)
    if (Implementer::GetInstance()->blocks[i] == this) {
      this->RemoveFromBlockChain(
          Implementer::GetInstance()->odf_form->GetLayout());
      this->AddToBlockChain(Implementer::GetInstance()->odf_form->GetLayout(),
                            i - 1);
      Implementer::GetInstance()->blocks[i - 1]->RemoveFromBlockChain(
          Implementer::GetInstance()->odf_form->GetLayout());
      Implementer::GetInstance()->blocks[i - 1]->AddToBlockChain(
          Implementer::GetInstance()->odf_form->GetLayout(), i);

      Implementer::GetInstance()->blocks.swapItemsAt(i, i - 1);
    }
}

void Block::SwapDownBlock() {
  for (int i = 0; i < Implementer::GetInstance()->blocks.size() - 1; i++)
    if (Implementer::GetInstance()->blocks[i] == this) {
      this->RemoveFromBlockChain(
          Implementer::GetInstance()->odf_form->GetLayout());
      this->AddToBlockChain(Implementer::GetInstance()->odf_form->GetLayout(),
                            i + 1);
      Implementer::GetInstance()->blocks[i + 1]->RemoveFromBlockChain(
          Implementer::GetInstance()->odf_form->GetLayout());
      Implementer::GetInstance()->blocks[i + 1]->AddToBlockChain(
          Implementer::GetInstance()->odf_form->GetLayout(), i);

      Implementer::GetInstance()->blocks.swapItemsAt(i + 1, i);
      return;
    }
}

#include "block.h"

#include "../manager_odf.h"

Block::Block()
    : deleteBtn(new QPushButton("delete")),
      upBtn(new QPushButton("up")),
      downBtn(new QPushButton("down")),
      layout(new QHBoxLayout) {
  deleteBtn->setFixedSize(90, 45);
  upBtn->setFixedSize(90, 45);
  downBtn->setFixedSize(90, 45);
  layout->addWidget(deleteBtn);
  layout->addWidget(upBtn);
  layout->addWidget(downBtn);
  layout->setSpacing(60);

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
  this->RemoveFromBlockChain(ManagerODF::GetInstance()->form->GetLayout());
  for (int i = 0; i < ManagerODF::GetInstance()->blocks.size(); i++)
    if (ManagerODF::GetInstance()->blocks[i] == this)
      ManagerODF::GetInstance()->blocks.removeAt(i);
}

void Block::SwapUpBlock() {
  for (int i = 1; i < ManagerODF::GetInstance()->blocks.size(); i++)
    if (ManagerODF::GetInstance()->blocks[i] == this) {
      this->RemoveFromBlockChain(ManagerODF::GetInstance()->form->GetLayout());
      this->AddToBlockChain(ManagerODF::GetInstance()->form->GetLayout(),
                            i - 1);
      ManagerODF::GetInstance()->blocks[i - 1]->RemoveFromBlockChain(
          ManagerODF::GetInstance()->form->GetLayout());
      ManagerODF::GetInstance()->blocks[i - 1]->AddToBlockChain(
          ManagerODF::GetInstance()->form->GetLayout(), i);

      ManagerODF::GetInstance()->blocks.swapItemsAt(i, i - 1);
    }
}

void Block::SwapDownBlock() {
  for (int i = 0; i < ManagerODF::GetInstance()->blocks.size() - 1; i++)
    if (ManagerODF::GetInstance()->blocks[i] == this) {
      this->RemoveFromBlockChain(ManagerODF::GetInstance()->form->GetLayout());
      this->AddToBlockChain(ManagerODF::GetInstance()->form->GetLayout(),
                            i + 1);
      ManagerODF::GetInstance()->blocks[i + 1]->RemoveFromBlockChain(
          ManagerODF::GetInstance()->form->GetLayout());
      ManagerODF::GetInstance()->blocks[i + 1]->AddToBlockChain(
          ManagerODF::GetInstance()->form->GetLayout(), i);

      ManagerODF::GetInstance()->blocks.swapItemsAt(i + 1, i);
      return;
    }
}

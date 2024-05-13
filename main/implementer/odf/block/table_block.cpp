#include "table_block.h"

#include "manager/manager.h"

TableBlock::TableBlock(QVBoxLayout *block_chain, QList<int> column_indexes)
    : Block(), table(new QTableWidget) {
  table->setFixedSize(256, 256);
  lib::Manager *manager = lib::Manager::GetInstance();

  table->setColumnCount(column_indexes.size());
  table->setRowCount(manager->GetMeasurementsCount());

  for (size_t i = 0; i < size_t(column_indexes.size()); i++) {
    table->setHorizontalHeaderItem(
        i, new QTableWidgetItem(
               manager->GetVariable(column_indexes[i]).naming.title));
    for (size_t j = 0; j < manager->GetMeasurementsCount(); j++) {
      table->setItem(
          j, i,
          new QTableWidgetItem(
              QString::number(
                  manager->GetVariable(column_indexes[i]).measurements[j]),
              QTableWidgetItem::Type));
      table->item(j, i)->setFlags(Qt::NoItemFlags);
    }
  }

  layout->addWidget(table);
  block_chain->addLayout(layout);
}

TableBlock::~TableBlock() { layout->removeWidget(table); }

void TableBlock::Save(QTextCursor *cursor) {
  cursor->insertTable(table->rowCount() + 1, table->columnCount());
  for (int i = 0; i < table->columnCount();
       i++, cursor->movePosition(QTextCursor::NextCell))
    cursor->insertText(table->horizontalHeaderItem(i)->text());
  for (int i = 0; i < table->rowCount(); i++)
    for (int j = 0; j < table->columnCount();
         j++, cursor->movePosition(QTextCursor::NextCell))
      cursor->insertText(table->item(i, j)->text());
  cursor->insertBlock();
}

void TableBlock::RemoveFromBlockChain(QVBoxLayout *block_chain) {
  block_chain->removeItem(layout);
  table->hide();
  deleteBtn->hide();
  upBtn->hide();
  downBtn->hide();
}

void TableBlock::AddToBlockChain(QVBoxLayout *block_chain, int position) {
  block_chain->insertItem(position, layout);
  table->show();
  deleteBtn->show();
  upBtn->show();
  downBtn->show();
}

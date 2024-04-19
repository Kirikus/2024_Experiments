#include "manager_odf.h"

#include "block/plot_block.h"
#include "block/table_block.h"
#include "block/text_block.h"

Q_GLOBAL_STATIC(ManagerODF, instance)

ManagerODF* ManagerODF::GetInstance() { return instance; }

void ManagerODF::AddTextBlock(QVBoxLayout* block_chain) {
  blocks.push_back(new TextBlock(block_chain));
}

void ManagerODF::AddTableBlock(QVBoxLayout* block_chain,
                               QList<int> column_indexes) {
  blocks.push_back(new TableBlock(block_chain, column_indexes));
}

void ManagerODF::AddPlotBlock(QVBoxLayout* block_chain, QPixmap pixmap) {
  // QPixmap pixmap = plot->toPixmap(400, 400);

  blocks.push_back(new PlotBlock(block_chain, pixmap));
}

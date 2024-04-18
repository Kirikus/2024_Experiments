#include "plot_block.h"

PlotBlock::PlotBlock(QVBoxLayout *, QPixmap) {}

PlotBlock::~PlotBlock() {}

void PlotBlock::Save(QTextCursor *) {}

void PlotBlock::RemoveFromBlockChain(QVBoxLayout *) {}

void PlotBlock::AddToBlockChain(QVBoxLayout *, int position) {}

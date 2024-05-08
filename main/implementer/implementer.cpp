#include "implementer.h"

#include "odf/block/plot_block.h"
#include "odf/block/table_block.h"
#include "odf/block/text_block.h"

Q_GLOBAL_STATIC(Implementer, instance)

Implementer* Implementer::GetInstance() { return instance; }

Implementer::Implementer() {
  database = new SQLite;
  db_form = new DB_Form;

  database->table = db_form->GetMeasurementsTableWidget();
  database->InitializeTables();

  odf_form = new ODF_Form;

  connect(db_form, &DB_Form::deleteBtn_is_clicked, database,
          &SQLite::DeleteFromDatabase);
  connect(db_form, &DB_Form::uploadBtn_is_clicked, database,
          &SQLite::UploadToManager);
}

void Implementer::AddTextBlock(QVBoxLayout* block_chain) {
  blocks.push_back(new TextBlock(block_chain));
}

void Implementer::AddTableBlock(QVBoxLayout* block_chain,
                                QList<int> column_indexes) {
  blocks.push_back(new TableBlock(block_chain, column_indexes));
}

void Implementer::AddPlotBlock(QVBoxLayout* block_chain, QPixmap pixmap) {
  blocks.push_back(new PlotBlock(block_chain, pixmap));
}

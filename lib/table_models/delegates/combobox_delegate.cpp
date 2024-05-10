#include "combobox_delegate.h"

#include "QComboBox"

QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const {
  return new QComboBox(parent);
}

void ComboBoxDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const {
  QComboBox *combo_box = static_cast<QComboBox *>(editor);
  QString current_text = index.model()->data(index, Qt::DisplayRole).toString();
  for (auto &item : options) {
    combo_box->addItem(item);
  }
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const {
  QComboBox *combo_box = static_cast<QComboBox *>(editor);
  model->setData(index, combo_box->currentText(), Qt::EditRole);
}

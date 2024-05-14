#include "color_delegate.h"

#include <qcolor.h>

#include <QColorDialog>

QWidget *ColorDelegate::createEditor(QWidget *parent,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const {
  Q_UNUSED(option)
  Q_UNUSED(index)
  return new QColorDialog(parent);
}

void ColorDelegate::setEditorData(QWidget *editor,
                                  const QModelIndex &index) const {
  QColorDialog *color_dialog = static_cast<QColorDialog *>(editor);
  color_dialog->move(600, 300);
  QColor color = index.model()->data(index, Qt::BackgroundRole).toString();
  color_dialog->setCurrentColor(color);
}

void ColorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                 const QModelIndex &index) const {
  QColorDialog *color_dialog = static_cast<QColorDialog *>(editor);
  auto color = color_dialog->currentColor();
  model->setData(index, color, Qt::EditRole);
}

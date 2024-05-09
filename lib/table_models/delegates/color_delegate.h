#ifndef COLOR_DELEGATE_H
#define COLOR_DELEGATE_H

#include <QStyledItemDelegate>

class ColorDelegate : public QStyledItemDelegate {
  Q_OBJECT
 public:
  ColorDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

  QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                        const QModelIndex& index) const override;
  void setEditorData(QWidget* editor, const QModelIndex& index) const override;
  void setModelData(QWidget* editor, QAbstractItemModel* model,
                    const QModelIndex& index) const override;
};

#endif  // COLOR_DELEGATE_H

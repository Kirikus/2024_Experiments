#ifndef COMBOBOX_DELEGATE_H
#define COMBOBOX_DELEGATE_H

#include <QStyledItemDelegate>

class ComboBoxDelegate : public QStyledItemDelegate {
  Q_OBJECT
 private:
  QStringList options;

 public:
  ComboBoxDelegate(QStringList options, QObject* parent = nullptr)
      : QStyledItemDelegate(parent), options(options) {}

  QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                        const QModelIndex& index) const override;
  void setEditorData(QWidget* editor, const QModelIndex& index) const override;
  void setModelData(QWidget* editor, QAbstractItemModel* model,
                    const QModelIndex& index) const override;
};

#endif  // COMBOBOX_DELEGATE_H

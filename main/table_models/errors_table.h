#ifndef ERRORS_TABLE_H
#define ERRORS_TABLE_H

#include <QAbstractTableModel>

namespace lib {

class ErrorsTable : public QAbstractTableModel {
  Q_OBJECT
 public:
  explicit ErrorsTable(QObject *parent = nullptr)
      : QAbstractTableModel(parent) {}

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

  void insertRow(int);
  void removeRow(int);

  enum columns_data { kType = 0, kValue, kCount };

  static QMap<int, QString> error_types;
};

}  // namespace lib

#endif  // ERRORS_TABLE_H

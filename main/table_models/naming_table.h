#ifndef NAMING_TABLE_H
#define NAMING_TABLE_H

#include <QAbstractTableModel>

namespace lib {

class NamingTable : public QAbstractTableModel {
  Q_OBJECT
 public:
  explicit NamingTable(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

  bool insertRows(int row, int count, const QModelIndex &parent);

  bool removeRows(int row, int count, const QModelIndex &parent);
};

}  // namespace lib

#endif  // NAMING_TABLE_H

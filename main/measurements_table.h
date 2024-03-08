#ifndef MEASUREMENTS_TABLE_H
#define MEASUREMENTS_TABLE_H

#include <QAbstractTableModel>

namespace lib {

class MeasurementsTable : public QAbstractTableModel {
  Q_OBJECT
 public:
  explicit MeasurementsTable(QObject *parent = nullptr);

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

  bool insertRows(int position, int rows,
                  const QModelIndex &parent = QModelIndex());
  bool insertColumns(int position, int columns,
                     const QModelIndex &parent = QModelIndex());
  bool removeRows(int position, int rows,
                  const QModelIndex &parent = QModelIndex());
  bool removeColumns(int position, int columns,
                     const QModelIndex &parent = QModelIndex());
};

}  // namespace lib

#endif  // MEASUREMENTS_TABLE_H

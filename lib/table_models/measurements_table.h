#ifndef MEASUREMENTS_TABLE_H
#define MEASUREMENTS_TABLE_H

#include <QAbstractTableModel>

namespace lib {

class MeasurementsTable : public QAbstractTableModel {
  Q_OBJECT
 public:
  explicit MeasurementsTable(QObject *parent = nullptr)
      : QAbstractTableModel(parent) {}

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

  void insertRow(int);
  void removeRow(int);

  void insertColumn(int);
  void removeColumn(int);
};

}  // namespace lib

#endif  // MEASUREMENTS_TABLE_H

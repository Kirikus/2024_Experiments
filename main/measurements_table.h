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
  Qt::ItemFlags flags(const QModelIndex &index) const override;

  void insertRow(int row, const QModelIndex &parent);
  void insertColumn(int column, const QModelIndex &parent);
};

}  // namespace lib

#endif  // MEASUREMENTS_TABLE_H

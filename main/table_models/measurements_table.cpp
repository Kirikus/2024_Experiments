#include "measurements_table.h"

#include "QVariant"
#include "manager.h"

namespace lib {

int MeasurementsTable::rowCount(const QModelIndex &parent) const {
  return Manager::GetInstance()->GetMeasurementsCount();
}

int MeasurementsTable::columnCount(const QModelIndex &parent) const {
  return Manager::GetInstance()->GetVariablesCount();
}

QVariant MeasurementsTable::data(const QModelIndex &index, int role) const {
  switch (role) {
    case Qt::DisplayRole:
      return Manager::GetInstance()
                     ->GetVariable(index.column())
                     .measurements[index.row()]
                 ? QVariant(Manager::GetInstance()
                                ->GetVariable(index.column())
                                .measurements[index.row()])
                 : QVariant();

    default:
      return QVariant();
  }
}

bool MeasurementsTable::setData(const QModelIndex &index, const QVariant &value,
                                int role) {
  if (!value.canConvert<double>()) return false;
  switch (role) {
    case Qt::EditRole:
      Manager::GetInstance()
          ->GetVariable(index.column())
          .measurements[index.row()] = value.toDouble();
      emit dataChanged(index, index);
      return true;

    default:
      return false;
  }
}

QVariant MeasurementsTable::headerData(int section, Qt::Orientation orientation,
                                       int role) const {
  switch (role) {
    case Qt::DisplayRole:
      switch (orientation) {
        case Qt::Vertical:
          return section + 1;
        case Qt::Horizontal:
          return Manager::GetInstance()->GetVariable(section).naming.title;
      }
    default:
      return QVariant();
  }
}

Qt::ItemFlags MeasurementsTable::flags(const QModelIndex &index) const {
  return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void MeasurementsTable::insertRow(int index) {
  beginInsertRows(QModelIndex(), index, index);
  endInsertRows();
}

void MeasurementsTable::insertColumn(int index) {
  beginInsertColumns(QModelIndex(), index, index);
  endInsertColumns();
}

void MeasurementsTable::removeRow(int index) {
  beginRemoveRows(QModelIndex(), index, index);
  endRemoveRows();
}

void MeasurementsTable::removeColumn(int index) {
  beginRemoveColumns(QModelIndex(), index, index);
  endRemoveColumns();
}

}  // namespace lib

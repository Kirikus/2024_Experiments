#include "measurements_table.h"

#include "QVariant"
#include "manager.h"

lib::MeasurementsTable::MeasurementsTable(QObject *parent)
    : QAbstractTableModel(parent) {}

int lib::MeasurementsTable::rowCount(const QModelIndex &parent) const {
  return lib::Manager::getInstance()->getMeasurementsCount();
}

int lib::MeasurementsTable::columnCount(const QModelIndex &parent) const {
  return lib::Manager::getInstance()->getVariablesCount();
}

QVariant lib::MeasurementsTable::data(const QModelIndex &index,
                                      int role) const {
  int row = index.row();
  int column = index.column();

  if (Manager::getInstance()->getVariable(column).getMeasurementsCount() <= row)
    return QVariant();
  if (role == Qt::DisplayRole) {
    if (Manager::getInstance()->getVariable(column).measurements[row] == 0)
      return QVariant();
    return QVariant(
        Manager::getInstance()->getVariable(column).measurements[row]);
  }
  return QVariant();
}

bool lib::MeasurementsTable::setData(const QModelIndex &index,
                                     const QVariant &value, int role) {
  int row = index.row();
  int column = index.column();

  if (role == Qt::EditRole) {
    if (!value.canConvert<double>()) return false;

    if (Manager::getInstance()->getVariable(column).getMeasurementsCount() <=
        row) {
      Manager::getInstance()->getVariable(column).measurements.append(
          value.toDouble());
      emit dataChanged(index, index);
      return true;
    }
    Manager::getInstance()->getVariable(column).measurements[row] =
        value.toDouble();
    emit dataChanged(index, index);
    return true;
  }
  return false;
}

QVariant lib::MeasurementsTable::headerData(int section,
                                            Qt::Orientation orientation,
                                            int role) const {
  if (role != Qt::DisplayRole) return QVariant();

  if (orientation == Qt::Vertical) return section + 1;

  return Manager::getInstance()->getVariable(section).naming.name_short != "NONE"
             ? Manager::getInstance()->getVariable(section).naming.name_short
             : Manager::getInstance()->getVariable(section).naming.name_full;
}

Qt::ItemFlags lib::MeasurementsTable::flags(const QModelIndex &index) const {
  return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool lib::MeasurementsTable::insertRows(int position, int rows,
                                        const QModelIndex &parent) {
  beginInsertRows(QModelIndex(), position, position + rows - 1);
  endInsertRows();
  return true;
}

bool lib::MeasurementsTable::insertColumns(int position, int columns,
                                           const QModelIndex &parent) {
  beginInsertColumns(QModelIndex(), position, position + columns - 1);
  endInsertColumns();
  return true;
}

bool lib::MeasurementsTable::removeRows(int position, int rows,
                                        const QModelIndex &parent) {
  beginRemoveRows(QModelIndex(), position, position + rows - 1);
  endRemoveRows();
  return true;
}

bool lib::MeasurementsTable::removeColumns(int position, int columns,
                                           const QModelIndex &parent) {
  beginRemoveColumns(QModelIndex(), position, position + columns - 1);
  endRemoveColumns();
  return true;
}

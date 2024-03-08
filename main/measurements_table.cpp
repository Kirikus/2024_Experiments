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

Qt::ItemFlags lib::MeasurementsTable::flags(const QModelIndex &index) const {
  return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void lib::MeasurementsTable::insertRow(int row, const QModelIndex &parent) {
  beginInsertRows(QModelIndex(), row, row);
}

void lib::MeasurementsTable::insertColumn(int column,
                                          const QModelIndex &parent) {
  beginInsertColumns(QModelIndex(), column, column);
}
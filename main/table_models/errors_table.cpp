#include "errors_table.h"

#include "QVariant"
#include "manager.h"

namespace Errors_shell {
enum data : int {
  columnCount = 2,
  error_type = 0,
  error = 1,
};
}  // namespace Errors_shell

lib::ErrorsTable::ErrorsTable(QObject *parent) : QAbstractTableModel(parent) {}

int lib::ErrorsTable::rowCount(const QModelIndex &parent) const {
  return Manager::getInstance()->getVariablesCount();
}

int lib::ErrorsTable::columnCount(const QModelIndex &parent) const {
  return Errors_shell::data::columnCount;
}

QVariant lib::ErrorsTable::data(const QModelIndex &index, int role) const {
  int row = index.row();
  int column = index.column();
  auto &errors = Manager::getInstance()->getVariable(row).errors;

  switch (role) {
    case Qt::DisplayRole: {
      switch (column) {
        case Errors_shell::data::error_type:
          return errors.error_types.value(errors.current_error_type);
        case Errors_shell::data::error:
          return Manager::getInstance()->getVariable(row).errors.error;
      }
    }
    default:
      return QVariant();
  }
}

bool lib::ErrorsTable::setData(const QModelIndex &index, const QVariant &value,
                               int role) {
  int row = index.row();
  int column = index.column();
  auto &errors = Manager::getInstance()->getVariable(row).errors;

  switch (role) {
    case Qt::EditRole: {
      switch (column) {
        case Errors_shell::data::error_type:
          errors.current_error_type =
              Variable::ErrorOptions::error_types.key(value.toString());
          emit dataChanged(index, index);
          return true;
        case Errors_shell::data::error:
          if (!value.canConvert<double>() or value.toDouble() < 0) return false;
          Manager::getInstance()->getVariable(row).errors.error =
              value.toDouble();
          emit dataChanged(index, index);
          return true;
      }
    }
    default:
      return false;
  }
}

QVariant lib::ErrorsTable::headerData(int section, Qt::Orientation orientation,
                                      int role) const {
  if (role != Qt::DisplayRole) return QVariant();

  if (orientation == Qt::Vertical)
    return QString(
        Manager::getInstance()->getVariable(section).naming.name_full);
  if (orientation == Qt::Horizontal)
    if (section == 0) return QString("Type of error");
  if (section == 1) return QString("Error");
  return QVariant();
}

Qt::ItemFlags lib::ErrorsTable::flags(const QModelIndex &index) const {
  return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool lib::ErrorsTable::insertRows(int position, int rows,
                                  const QModelIndex &parent) {
  beginInsertRows(QModelIndex(), position, position + rows - 1);
  endInsertRows();
  return true;
}

bool lib::ErrorsTable::removeRows(int position, int rows,
                                  const QModelIndex &parent) {
  beginRemoveRows(QModelIndex(), position, position + rows - 1);
  endRemoveRows();
  return true;
}

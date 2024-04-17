#include "errors_table.h"

#include "QVariant"
#include "manager.h"

namespace lib {

QMap<int, QString> ErrorsTable::error_types = {
    {Variable::ErrorOptions::Types::kRelative, "Relative"},
    {Variable::ErrorOptions::Types::kAbsolute, "Absolute"},
};

int ErrorsTable::rowCount(const QModelIndex &parent) const {
  return Manager::GetInstance()->GetVariablesCount();
}

int ErrorsTable::columnCount(const QModelIndex &parent) const {
  return columns_data::kCount;
}

QVariant ErrorsTable::data(const QModelIndex &index, int role) const {
  switch (role) {
    case Qt::DisplayRole: {
      switch (index.column()) {
        case columns_data::kType:
          return error_types.value(
              Manager::GetInstance()->GetVariable(index.row()).error.type);
        case columns_data::kValue:
          return Manager::GetInstance()->GetVariable(index.row()).error.value;
      }
    }
    default:
      return QVariant();
  }
}

bool ErrorsTable::setData(const QModelIndex &index, const QVariant &value,
                          int role) {
  switch (role) {
    case Qt::EditRole: {
      switch (index.column()) {
        case columns_data::kType:
          Manager::GetInstance()->GetVariable(index.row()).error.type =
              error_types.key(value.toString());
          emit dataChanged(index, index);
          return true;
        case columns_data::kValue:
          if (!value.canConvert<double>() || value.toDouble() < 0) return false;
          Manager::GetInstance()->GetVariable(index.row()).error.value =
              value.toDouble();
          emit dataChanged(index, index);
          return true;
      }
    }
    default:
      return false;
  }
}

QVariant ErrorsTable::headerData(int section, Qt::Orientation orientation,
                                 int role) const {
  switch (role) {
    case Qt::DisplayRole:
      switch (orientation) {
        case Qt::Vertical:
          return QString(
              Manager::GetInstance()->GetVariable(section).naming.title);
        case Qt::Horizontal:
          switch (section) {
            case columns_data::kType:
              return QString("Type of error");
            case columns_data::kValue:
              return QString("Error");
          }
      }
    default:
      return QVariant();
  }
}

Qt::ItemFlags ErrorsTable::flags(const QModelIndex &index) const {
  return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void ErrorsTable::insertRow(int index) {
  beginInsertRows(QModelIndex(), index, index);
  endInsertRows();
}

void ErrorsTable::removeRow(int index) {
  beginRemoveRows(QModelIndex(), index, index);
  endRemoveRows();
}

}  // namespace lib

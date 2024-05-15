#include "measurements_table.h"

#include "QVariant"
#include "manager/manager.h"

namespace lib {

int MeasurementsTable::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return Manager::GetInstance()->GetMeasurementsCount();
}

int MeasurementsTable::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return Manager::GetInstance()->GetVariablesCount();
}

QVariant MeasurementsTable::data(const QModelIndex &index, int role) const {
  const Variable &variable =
      Manager::GetInstance()->GetVariable(index.column());
  QString value_str = QVariant(variable.measurements[index.row()]).toString();
  switch (role) {
    case Qt::DisplayRole:
      if (variable.measurements[index.row()]) {
        switch (variable.error.type) {
          case Variable::ErrorOptions::Types::kAbsolute:
            return value_str + " ± " +
                   QVariant(variable.error.value).toString();
          case Variable::ErrorOptions::Types::kRelative:
            return value_str + " ± " +
                   QVariant(variable.measurements[index.row()] *
                            variable.error.value * 0.5)
                       .toString();
          default:
            return QVariant();
        }
      } else
        return QVariant();
    default:
      return QVariant();
  }
}

bool MeasurementsTable::setData(const QModelIndex &index, const QVariant &value,
                                int role) {
  if (!value.canConvert<double>()) return false;
  switch (role) {
    case Qt::EditRole:
      if (value.toString() == "") return false;
      if (value.toDouble()) {
        Manager::GetInstance()
            ->GetVariable(index.column())
            .measurements[index.row()] = value.toDouble();
        emit dataChanged(index, index);
        return true;
      } else
        return false;
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
        default:
          auto naming = Manager::GetInstance()->GetVariable(section).naming;
          QString cstr;
          Manager::GetInstance()->GetVariable(section).is_calculated
              ? cstr = " # "
              : "";
          return naming.tag.isEmpty() ? cstr + naming.title + cstr
                                      : naming.title + "\n(" + naming.tag + ")";
      }
    default:
      return QVariant();
  }
}

Qt::ItemFlags MeasurementsTable::flags(const QModelIndex &index) const {
  return !Manager::GetInstance()->GetVariable(index.column()).is_calculated
             ? QAbstractItemModel::flags(index) | Qt::ItemIsEditable
             : QAbstractItemModel::flags(index) | Qt::NoItemFlags;
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

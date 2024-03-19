#include "plot_settings_table.h"

#include "QVariant"
#include "manager.h"

namespace plot_settings_shell {
int columnCount = 5;
QString visible = "Visible";
QString width = "Width";
QString point_form = "Point form";
QString line_type = "Line type";
QString color = "Color";
};  // namespace plot_settings_shell

lib::PlotSettingsTable::PlotSettingsTable(QObject *parent) {}

int lib::PlotSettingsTable::rowCount(const QModelIndex &parent) const {
  return Manager::getInstance()->getVariablesCount();
}

int lib::PlotSettingsTable::columnCount(const QModelIndex &parent) const {
  return plot_settings_shell::columnCount;
}

QVariant lib::PlotSettingsTable::data(const QModelIndex &index,
                                      int role) const {
  int row = index.row();
  int column = index.column();
  auto &visual = Manager::getInstance()->getVariable(row).variable_visual;
  if (role == Qt::DisplayRole) switch (column) {
      case 0:
        return QVariant();
      case 1:
        return visual.width;
      case 2:
        return QVariant();  // TODO"
      case 3:
        return QVariant();  // TODO"
    }
  return QVariant();
}

bool lib::PlotSettingsTable::setData(const QModelIndex &index,
                                     const QVariant &value, int role) {
  int row = index.row();
  int column = index.column();
  auto &visual = Manager::getInstance()->getVariable(row).variable_visual;
  if (role == Qt::EditRole) {
    switch (column) {
      case 1:
        if (!value.toInt()) return false;
        visual.width = value.toInt();
        emit dataChanged(index, index);
        return true;
      case 2:
        // TODO
        emit dataChanged(index, index);
        return true;
      case 3:
        // TODO
        emit dataChanged(index, index);
        return true;
      case 4:
        visual.color = value.value<QColor>();
        emit dataChanged(index, index);
        return true;
    }
  }
  return false;
}

QVariant lib::PlotSettingsTable::headerData(int section,
                                            Qt::Orientation orientation,
                                            int role) const {
  if (role != Qt::DisplayRole) return QVariant();
  if (orientation == Qt::Vertical)
    return QString(Manager::getInstance()->getVariable(section).name_short);
  switch (section) {
    case 0:
      return QString("Visible");
    case 1:
      return QString("Width");
    case 2:
      return QString("Point type");
    case 3:
      return QString("Line type");
    case 4:
      return QString("Color");
  }
  return QVariant();
}

Qt::ItemFlags lib::PlotSettingsTable::flags(const QModelIndex &index) const {
  return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

bool lib::PlotSettingsTable::insertRows(int row, int count,
                                        const QModelIndex &parent) {
  beginInsertRows(parent, row, row + count - 1);
  endInsertRows();
  return true;
}

bool lib::PlotSettingsTable::removeRows(int row, int count,
                                        const QModelIndex &parent) {
  beginRemoveRows(parent, row, row + count - 1);
  endRemoveRows();
  return true;
}

#include "plot_settings_table.h"

#include "QVariant"
#include "manager.h"

namespace PlotSettings_shell {
enum data : int {
  columnCount = 5,
  visible = 0,
  width = 1,
  point_form = 2,
  line_type = 3,
  color = 4
};
}  // namespace PlotSettings_shell

lib::PlotSettingsTable::PlotSettingsTable(QObject *parent) {}

int lib::PlotSettingsTable::rowCount(const QModelIndex &parent) const {
  return Manager::getInstance()->getVariablesCount();
}

int lib::PlotSettingsTable::columnCount(const QModelIndex &parent) const {
  return PlotSettings_shell::data::columnCount;
}

QVariant lib::PlotSettingsTable::data(const QModelIndex &index,
                                      int role) const {
  int row = index.row();
  int column = index.column();
  auto &visual = Manager::getInstance()->getVariable(row).variable_visual;
  switch (role) {
    case Qt::BackgroundRole:
      if (column == PlotSettings_shell::data::color) return visual.color;
    case Qt::CheckStateRole:
      if (column == PlotSettings_shell::data::visible)
        return visual.visible ? Qt::Checked : Qt::Unchecked;
      break;
    case Qt::DisplayRole:
      switch (column) {
        case PlotSettings_shell::data::width:
          return visual.width;
        case PlotSettings_shell::data::point_form:
          if (visual.point_form == QCPScatterStyle::ScatterShape::ssNone)
            return QString("Standart");
          return visual.point_forms.value(visual.point_form);
        case PlotSettings_shell::data::line_type:
          return QVariant::fromValue(visual.line_type);
      }
  }
  return QVariant();
}

bool lib::PlotSettingsTable::setData(const QModelIndex &index,
                                     const QVariant &value, int role) {
  int row = index.row();
  int column = index.column();
  auto &visual = Manager::getInstance()->getVariable(row).variable_visual;
  switch (role) {
    case Qt::CheckStateRole:
      if (column == PlotSettings_shell::data::visible) {
        if (!value.canConvert<int>()) return false;
        if (value.toInt() < Qt::Unchecked || value.toInt() > Qt::Checked)
          return false;
        visual.visible =
            static_cast<Qt::CheckState>(value.toInt()) == Qt::Checked;
        break;
      }
    case Qt::EditRole:
      switch (column) {
        case PlotSettings_shell::data::width:
          if (!value.toInt()) return false;
          visual.width = value.toInt();
          emit dataChanged(index, index);
          return true;
        case PlotSettings_shell::data::point_form:
          visual.point_form = VisualOptions::point_forms.key(value.toString());
          emit dataChanged(index, index);
          return true;
        case PlotSettings_shell::data::line_type:
          visual.line_type = VisualOptions::line_types.key(value.toString());
          emit dataChanged(index, index);
          return true;
        case PlotSettings_shell::data::color:
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
    case PlotSettings_shell::data::visible:
      return QString("Visible");
    case PlotSettings_shell::data::width:
      return QString("Width");
    case PlotSettings_shell::data::point_form:
      return QString("Point form");
    case PlotSettings_shell::data::line_type:
      return QString("Line type");
    case PlotSettings_shell::data::color:
      return QString("Color");
  }
  return QVariant();
}

Qt::ItemFlags lib::PlotSettingsTable::flags(const QModelIndex &index) const {
  int column = index.column();
  switch (column) {
    case PlotSettings_shell::data::visible:
      return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable |
             QAbstractItemModel::flags(index);
    case PlotSettings_shell::data::width:
    case PlotSettings_shell::data::point_form:
    case PlotSettings_shell::data::line_type:
    case PlotSettings_shell::data::color:
      return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
  }
  return Qt::ItemIsEditable;
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

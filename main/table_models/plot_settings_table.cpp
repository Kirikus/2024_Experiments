#include "plot_settings_table.h"

#include "QVariant"
#include "manager.h"

namespace lib {

int PlotSettingsTable::rowCount(const QModelIndex &parent) const {
  return Manager::GetInstance()->GetVariablesCount();
}

int PlotSettingsTable::columnCount(const QModelIndex &parent) const {
  return columns_data::kCount;
}

QVariant PlotSettingsTable::data(const QModelIndex &index, int role) const {
  auto &visual = Manager::GetInstance()->GetVariable(index.row()).visual;
  switch (role) {
    case Qt::BackgroundRole:
      if (index.column() == columns_data::kColor) return visual.color;
    case Qt::CheckStateRole:
      return index.column() == columns_data::kVisible
                 ? visual.visible ? Qt::Checked : Qt::Unchecked
                 : QVariant();
    case Qt::DisplayRole:
      switch (index.column()) {
        case columns_data::kWidth:
          return visual.width;
        case columns_data::kPointShape:
          return Variable::VisualOptions::point_shapes.value(
              visual.point_shape);
        case columns_data::kLineType:
          return Variable::VisualOptions::line_types.value(visual.line_type);
      }
    default:
      return QVariant();
  }
}

bool PlotSettingsTable::setData(const QModelIndex &index, const QVariant &value,
                                int role) {
  auto &visual = Manager::GetInstance()->GetVariable(index.row()).visual;
  switch (role) {
    case Qt::CheckStateRole:
      if (index.column() == columns_data::kVisible) {
        if (!value.canConvert<int>()) return false;
        if (value.toInt() < Qt::Unchecked || value.toInt() > Qt::Checked)
          return false;
        visual.visible =
            static_cast<Qt::CheckState>(value.toInt()) == Qt::Checked;
        return true;
      }
    case Qt::EditRole:
      switch (index.column()) {
        case columns_data::kWidth:
          if (!value.toInt()) return false;
          visual.width = value.toInt();
          emit dataChanged(index, index);
          return true;
        case columns_data::kPointShape:
          visual.point_shape =
              Variable::VisualOptions::point_shapes.key(value.toString());
          emit dataChanged(index, index);
          return true;
        case columns_data::kLineType:
          visual.line_type =
              Variable::VisualOptions::line_types.key(value.toString());
          emit dataChanged(index, index);
          return true;
        case columns_data::kColor:
          visual.color = value.value<QColor>();
          emit dataChanged(index, index);
          return true;
      }
    default:
      return false;
  }
}

QVariant PlotSettingsTable::headerData(int section, Qt::Orientation orientation,
                                       int role) const {
  switch (role) {
    case Qt::DisplayRole:
      switch (orientation) {
        case Qt::Vertical:
          return QString(
              Manager::GetInstance()->GetVariable(section).naming.title);
        case Qt::Horizontal:
          switch (section) {
            case columns_data::kVisible:
              return QString("Visible");
            case columns_data::kWidth:
              return QString("Width");
            case columns_data::kPointShape:
              return QString("Point shape");
            case columns_data::kLineType:
              return QString("Line type");
            case columns_data::kColor:
              return QString("Color");
          }
      }
    default:
      return QVariant();
  }
}

Qt::ItemFlags lib::PlotSettingsTable::flags(const QModelIndex &index) const {
  return index.column() == columns_data::kVisible
             ? Qt::ItemIsEnabled | Qt::ItemIsUserCheckable |
                   QAbstractItemModel::flags(index)
             : Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

void PlotSettingsTable::insertRow(int index) {
  beginInsertRows(QModelIndex(), index, index);
  endInsertRows();
}

void PlotSettingsTable::removeRow(int index) {
  beginRemoveRows(QModelIndex(), index, index);
  endRemoveRows();
}

}  // namespace lib

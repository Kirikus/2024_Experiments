#include "naming_table.h"

#include "QVariant"
#include "manager.h"

#define shortname 1
#define fullname 1

lib::NamingTable::NamingTable(QObject *parent) {}

int lib::NamingTable::rowCount(const QModelIndex &parent) const {
  return Manager::getInstance()->getVariablesCount();
}

int lib::NamingTable::columnCount(const QModelIndex &parent) const {
  return shortname + fullname;
}

QVariant lib::NamingTable::data(const QModelIndex &index, int role) const {
  if (role == Qt::DisplayRole) {
    if (index.column() == 0)
      return Manager::getInstance()->getVariable(index.row()).name_full;
    if (index.column() == 1)
      return Manager::getInstance()->getVariable(index.row()).name_short;
  }
  return QVariant();
}

bool lib::NamingTable::setData(const QModelIndex &index, const QVariant &value,
                               int role) {
  if (role == Qt::EditRole) {
    if (index.column() == 0)
      return (value.toString().isEmpty() == true)
                 ? false
                 : Manager::getInstance()->getVariable(index.row()).name_full ==
                       value.toString();
    if (index.column() == 1)
      return (value.toString().isEmpty() == true)
                 ? false
                 : Manager::getInstance()
                           ->getVariable(index.row())
                           .name_short == value.toString();
    if (index.column() == 0 || index.column() == 1) return true;
  }
  return false;
}

QVariant lib::NamingTable::headerData(int section, Qt::Orientation orientation,
                                      int role) const {
  if (role != Qt::DisplayRole) return QVariant();
  if (orientation == Qt::Vertical) return section + 1;
  if (section == 0) return QString("Full name");
  if (section == 1) return QString("Short name");
  return QVariant();
}

Qt::ItemFlags lib::NamingTable::flags(const QModelIndex &index) const {
  return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

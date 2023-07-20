#include "custablemodel.h"
#include "qdebug.h"

CusTableModel::CusTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    StData stData;
    stData.button_value = "Button";
    stData.spinBox_value = 20;
    stData.comboBox_value = "int";
    stData.progressBar_value = 50;
    stData.checkBox_value = false;
    stData.lineEdit_value = "LineEdit";

    m_datas << stData;
}

int CusTableModel::rowCount(const QModelIndex &parent) const
{
    return m_datas.size();
}

int CusTableModel::columnCount(const QModelIndex &parent) const
{
    return ColumnInfo::Column::Count;
}

QVariant CusTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    int column = index.column();
    StData stData = m_datas.at(index.row());
    if( role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column) {
        case ColumnInfo::Column::Number:
            return index.row() + 1;
        case ColumnInfo::Column::SpinBox:
            return stData.spinBox_value;
        case ColumnInfo::Column::ComboBox:
            return stData.comboBox_value;
        case ColumnInfo::Column::ProgressBar:
            return stData.progressBar_value;
        case ColumnInfo::Column::Button:
            return stData.button_value;
        case ColumnInfo::Column::CheckBox:
        {
            return stData.checkBox_value;
        }
        case ColumnInfo::Column::LineEdit:
            return stData.lineEdit_value;
        default:
            break;
        }
    }
//    else if(role == Qt::CheckStateRole)
//    {
//        switch(column){
//        case ColumnInfo::Column::CheckBox:
//            return stData.checkBox_value ? Qt::Checked : Qt::Unchecked;
//        default:
//            break;
//        }
//    }
    else if(role == Qt::TextAlignmentRole)
    {
        return Qt::AlignCenter;
    }
    else
    {
        return QVariant();
    }
    return QVariant();
}

QVariant CusTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Orientation::Horizontal)
    {
        if( role == Qt::DisplayRole || role == Qt::EditRole)
        {
            return ColumnInfo::getColumnName((ColumnInfo::Column)section);
        }
    }

    return QVariant();
}

bool CusTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
    {
        return false;
    }

//    if(role == Qt::CheckStateRole)
//    {
//        switch (index.column()) {
//        case ColumnInfo::Column::CheckBox:
//        {
//            m_datas[index.row()].checkBox_value = value.toBool();
//            emit dataChanged(index , index, {role});
//            return true;
//        }
//        default:
//            break;
//        }
//    }
    /*else*/ if(role == Qt::EditRole)
    {
        switch (index.column()) {
        case ColumnInfo::Column::LineEdit:
        {
            m_datas[index.row()].lineEdit_value = value.toString();
            emit dataChanged(index , index, {role});
            return true;
        }
        case ColumnInfo::Column::SpinBox:
        {
            m_datas[index.row()].spinBox_value = value.toInt();
            emit dataChanged(index, index, {role});
            return true;
        }
        case ColumnInfo::Column::ComboBox:
        {
            m_datas[index.row()].comboBox_value = value.toString();
            emit dataChanged(index, index, {role});
            return true;
        }
        case ColumnInfo::Column::CheckBox:
        {
            m_datas[index.row()].checkBox_value = value.toBool();
            emit dataChanged(index, index, {role});
            return true;
        }
        default:
            break;
        }
    }

    return false;
}

Qt::ItemFlags CusTableModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return QAbstractTableModel::flags(index);
    }

    if (index.column() == ColumnInfo::Column::LineEdit
        || index.column() == ColumnInfo::Column::SpinBox
        || index.column() == ColumnInfo::Column::ComboBox
        || index.column() == ColumnInfo::Column::CheckBox
        || index.column() == ColumnInfo::Column::ProgressBar)
    {
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }
//    else if(index.column() == ColumnInfo::Column::CheckBox)
//    {
//        return QAbstractTableModel::flags(index) | Qt::ItemIsUserCheckable;
//    }

    return QAbstractTableModel::flags(index) | Qt::ItemIsSelectable;
}

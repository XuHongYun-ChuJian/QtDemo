#include "cusdelegate.h"
#include "custablemodel.h"

#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
//////////////////////////////////////////////////////////////////////////////////
///             CusDelegate1 implement
/////////////////////////////////////////////////////////////////////////////////
CusDelegate1::CusDelegate1(QObject *parent): QStyledItemDelegate(parent)
{

}

QWidget *CusDelegate1::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int column = index.column();
    if(column == ColumnInfo::Column::SpinBox)
    {
        QSpinBox* spinBox = new QSpinBox(parent);
        spinBox->setMinimum(0);
        spinBox->setMaximum(99999);
        return spinBox;
    }
    else if(column == ColumnInfo::Column::ComboBox)
    {
        QComboBox* comboBox = new QComboBox(parent);
        comboBox->addItems(QStringList{"int" , "unsigned short" , "short" , "float" , "double"});
        return comboBox;
    }
    else if(column == ColumnInfo::Column::CheckBox)
    {
        QCheckBox* checkBox = new QCheckBox(parent);
//        connect(checkBox , &QCheckBox::clicked, this , [&](){
//            setModelData(checkBox, index.model(), index);
//        });
        return checkBox;
    }
    else
    {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void CusDelegate1::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int column = index.column();
    if(column == ColumnInfo::Column::SpinBox)
    {
        QSpinBox* spinBox = static_cast<QSpinBox*>(editor);
        if(spinBox)
        {
            spinBox->setValue(index.data(Qt::EditRole).toInt());
        }
    }
    else if(column == ColumnInfo::Column::ComboBox)
    {
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        if(comboBox)
        {
            const int cbx_index = index.data(Qt::EditRole).toInt();
            if(cbx_index >=0 && cbx_index < comboBox->count())
            {
                comboBox->setCurrentIndex(cbx_index);
            }
        }
    }
    else if(column == ColumnInfo::Column::CheckBox)
    {
        QCheckBox* checkBox = static_cast<QCheckBox*>(editor);
        if(checkBox)
        {
            checkBox->setChecked(index.data(Qt::EditRole).toBool());
        }
    }
}

void CusDelegate1::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int column = index.column();
    if(column == ColumnInfo::Column::SpinBox)
    {
        QSpinBox* spinBox = static_cast<QSpinBox*>(editor);
        if(spinBox)
        {
            spinBox->interpretText();
            model->setData(index, spinBox->value(), Qt::EditRole);
        }
    }
    else if(column == ColumnInfo::Column::ComboBox)
    {
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        if(comboBox)
        {
            model->setData(index, comboBox->currentText() , Qt::EditRole);
        }
    }
    else if(column == ColumnInfo::Column::CheckBox)
    {
        QCheckBox* checkBox = static_cast<QCheckBox*>(editor);
        if(checkBox)
        {
            model->setData(index, checkBox->isChecked() , Qt::EditRole);
        }
    }
}

void CusDelegate1::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

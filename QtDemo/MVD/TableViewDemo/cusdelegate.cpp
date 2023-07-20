#include "cusdelegate.h"
#include "custablemodel.h"
#include "qdebug.h"

#include <QApplication>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QProgressBar>
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
        spinBox->setFrame(false);
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
    else if(column == ColumnInfo::Column::ProgressBar)
    {
        QProgressBar* progressBar = new QProgressBar(parent);
        progressBar->setMinimum(0);
        progressBar->setMaximum(100);
        return progressBar;
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
    else if(column == ColumnInfo::Column::ProgressBar)
    {
        QProgressBar* progress = static_cast<QProgressBar*>(editor);
        if(progress)
        {
            progress->setValue(index.data(Qt::EditRole).toInt());
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

//////////////////////////////////////////////////////////////////////////////////
///             CusDelegate2 implement
/////////////////////////////////////////////////////////////////////////////////
CusDelegate2::CusDelegate2(QObject *parent): QStyledItemDelegate(parent)
{

}

void CusDelegate2::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int column = index.column();
    if(column == ColumnInfo::Column::CheckBox)
    {
        QStyleOptionButton checkBox;
        QRect checkBoxRect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkBox);
        checkBox.rect = option.rect;
        checkBox.rect.setX( (option.rect.x() + (option.rect.width() - checkBoxRect.width()) / 2));
        checkBox.rect.setY( (option.rect.y() + (option.rect.height() - checkBoxRect.height()) / 2));
        checkBox.state = index.data(Qt::EditRole).toBool() ? QStyle::State_On : QStyle::State_Off;
        checkBox.state |= QStyle::State_Enabled;
        QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkBox, painter);
    }
    else if(column == ColumnInfo::Column::ProgressBar)
    {
        QStyleOptionProgressBar progressBar;
        progressBar.rect = option.rect;
        progressBar.minimum = 0;
        progressBar.maximum = 100;
        progressBar.progress = index.data(Qt::EditRole).toInt();
        progressBar.text = QString("%1%").arg(progressBar.progress % progressBar.maximum);
        progressBar.textVisible = true;
        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBar, painter);
    }
    else if(column == ColumnInfo::Column::ComboBox)
    {
        QStyleOptionComboBox comboBox;
        comboBox.rect = option.rect;
        comboBox.currentText = index.data(Qt::EditRole).toString();
        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &comboBox, painter);
    }
    else if(column == ColumnInfo::Column::SpinBox)
    {
        QStyleOptionSpinBox spinBox;
        spinBox.rect = option.rect;
        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &spinBox, painter);
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

bool CusDelegate2::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(event->type() == QEvent::MouseButtonDblClick)//禁止双击编辑
        return true;

    int column = index.column();
    if(column == ColumnInfo::Column::CheckBox)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            model->setData(index, !index.data(Qt::EditRole).toBool(), Qt::EditRole);
            return true;
        }
    }
    else
    {
        return QStyledItemDelegate::editorEvent(event, model, option, index);
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

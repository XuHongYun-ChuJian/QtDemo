#ifndef CUSDELEGATE_H
#define CUSDELEGATE_H

#include <QStyledItemDelegate>
//////////////////////////////////////////////////////////////////////////////////
///             CusDelegate1 Define
/////////////////////////////////////////////////////////////////////////////////
class CusDelegate1 : public QStyledItemDelegate
{
    Q_OBJECT
public:
     CusDelegate1(QObject* parent = nullptr);

    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // CUSDELEGATE_H

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

//////////////////////////////////////////////////////////////////////////////////
///             CusDelegate2 Define
/////////////////////////////////////////////////////////////////////////////////
class CusDelegate2: public QStyledItemDelegate
{
    Q_OBJECT
public:
    CusDelegate2(QObject* parent = nullptr);

    // QAbstractItemDelegate interface
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};

#endif // CUSDELEGATE_H

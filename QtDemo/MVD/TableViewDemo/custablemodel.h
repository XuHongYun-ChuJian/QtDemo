#ifndef CUSTABLEMODEL_H
#define CUSTABLEMODEL_H

#include <QAbstractTableModel>

struct ColumnInfo
{
    enum Column
    {
        Number,
        SpinBox,
        ComboBox,
        ProgressBar,
        Button,
        CheckBox,
        LineEdit,
        Count
    };

    static QString getColumnName(Column c)
    {
        QMap<Column,QString> names = {
            {Number , QStringLiteral("序号")},
            {SpinBox, QStringLiteral("SpinBox")},
            {ComboBox, QStringLiteral("ComboBox")},
            {ProgressBar , QStringLiteral("ProgressBar")},
            {Button , QStringLiteral("Button")},
            {CheckBox , QStringLiteral("CheckBox")},
            {LineEdit , QStringLiteral("LineEdit")}
            };

        return names.value(c , "undefine");
    }
};

struct StData
{
    int spinBox_value;
    QString comboBox_value;
    int progressBar_value;
    QString button_value;
    bool checkBox_value;
    QString lineEdit_value;
};

class CusTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CusTableModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    QList<StData> m_datas;

};

#endif // CUSTABLEMODEL_H

#include "widget.h"
#include "qdebug.h"
#include "ui_widget.h"
#include "custablemodel.h"
#include "cusdelegate.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    auto model = new CusTableModel(this);
    ui->tableView->setModel(model);

    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setItemDelegate(new CusDelegate1());

    //保持Item为编辑状态，不用双击就可以显示代理控件
//    ui->tableView->openPersistentEditor( model->index(0 , ColumnInfo::Column::ComboBox) );
//    ui->tableView->openPersistentEditor( model->index(0 , ColumnInfo::Column::SpinBox) );
}

Widget::~Widget()
{
    delete ui;
}


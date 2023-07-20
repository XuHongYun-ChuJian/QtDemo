#include "widget.h"
#include "../../log.h"

#include <QDebug>
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("windowsvista"));
    Log::getInstance().initLog();
    Widget w;
    w.show();

    qDebug()<< QStyleFactory::keys();
    qDebug()<< "测试";
    qWarning()<< "测试";
    return a.exec();
}

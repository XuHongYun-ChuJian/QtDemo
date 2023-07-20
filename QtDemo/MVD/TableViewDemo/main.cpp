#include "widget.h"
#include "../../log.h"

#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Log::getInstance().initLog();
    Widget w;
    w.show();

    qDebug()<< "测试";
    qWarning()<< "测试";
    return a.exec();
}

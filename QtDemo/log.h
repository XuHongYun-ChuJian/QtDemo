#ifndef LOG_H
#define LOG_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMutex>

class Log
{
public:
    static Log& getInstance();
    void initLog();
    void setOutput();
    void write(QtMsgType type, const QMessageLogContext &context, const QString &msg);
private:
    Log();

private:
    QFile   logFile;
    QTextStream textStream;
    QString logName;        //日志名
    QString logDir;         //日志目录
    int     logMaxCount;    //日志最大条数
    int     logMaxSize;     //日志文件大小
    QMutex mutex;
};

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);

#endif // LOG_H

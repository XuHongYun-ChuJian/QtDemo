#include <QCoreApplication>
#include <QDir>
#include <QDateTime>
#include <QThread>
#include <QChar>
#include <QDir>

#include "log.h"

#define DT_YMD_HMS "yyyy-MM-dd hh:mm:ss"
#define DT_YMD "yyyy-MM-dd"
Log::Log()
{
}

Log &Log::getInstance()
{
    static Log instance;
    return instance;
}

void Log::initLog()
{
    logDir = QCoreApplication::applicationDirPath() + "/" + "log";
    logMaxCount = 1000;
    logMaxSize = 1024 * 1024;   //1MB = 1024 * 1024;
    if( !QDir().exists(logDir) )
    {
        QDir().mkpath(logDir);
    }

    setOutput();
}

void Log::setOutput()
{
    qInstallMessageHandler(outputMessage);
    setbuf(stdout, nullptr);
    setbuf(stderr, nullptr);
}

void Log::write(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QMutexLocker locker(&mutex);
    QString dt = QDateTime::currentDateTime().toString(DT_YMD_HMS);
    FILE *stream = stdout;
    QString levelStr;
    switch (type) {
    case QtDebugMsg:
        levelStr = "[Debug]";
        break;
    case QtWarningMsg:
        levelStr = "[Warn]";
        stream = stderr;
        break;
    case QtCriticalMsg:
        levelStr = "[Criti]";
        stream = stderr;
        break;
    case QtFatalMsg:
        levelStr = "[Fatal]";
        break;
    case QtInfoMsg:
        levelStr = "[Info]";
        break;
    default:
        break;
    }

    QString message = QString("%1 [%2] %3 %4:%5 %6").arg(dt).arg((quintptr)QThread::currentThreadId())
                          .arg(levelStr , -7 , QChar(' '))
                          .arg(context.function).arg(context.line).arg(msg);

    QString logName = QString("%1/%2.log").arg(logDir).arg(QDateTime::currentDateTime().toString(DT_YMD));

    if( logFile.fileName() != logName )
    {
        if( logFile.isOpen())
        {
            logFile.close();
        }

        logFile.setFileName(logName);
        if( !logFile.open(QFile::WriteOnly | QFile::Append))
        {
            fprintf(stream , "%s\n" , logName.toLocal8Bit().constData());
            fprintf(stream, "%s\n" , logFile.errorString().toLocal8Bit().constData());
            logFile.close();
            return;
        }
        textStream.setDevice(&logFile);
        textStream.setCodec("UTF-8");
    }

    textStream << message << "\r\n";
    textStream.flush();
    fprintf(stream , "%s\n" , message.toLocal8Bit().constData());

}

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Log::getInstance().write(type , context , msg);
}

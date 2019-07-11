#include "dialog.h"
#include "decoder.h"
#include <QDebug>
#include <QApplication>

Dialog* g_mainDlg = Q_NULLPTR;
QtMessageHandler g_oldMessageHandler = Q_NULLPTR;
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    g_oldMessageHandler = qInstallMessageHandler(myMessageOutput);
    qputenv("QTSCRCPY_ADB_PATH", "..\\qtscrcpy\\QtScrcpy\\third_party\\adb\\win\\adb.exe");
    qputenv("QTSCRCPY_SERVER_PATH", "..\\qtscrcpy\\QtScrcpy\\third_party\\scrcpy-server.jar");

    Decoder::init();

    QApplication a(argc, argv);
    Dialog w;
    g_mainDlg = &w;
    w.show();

    int ret = a.exec();
    Decoder::deInit();

    return ret;
}

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if (g_oldMessageHandler)
    {
        g_oldMessageHandler(type, context, msg);
    }
    if (g_mainDlg)
    {
        g_mainDlg->outLog(msg);
    }
}

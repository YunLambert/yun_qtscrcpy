#include "dialog.h"
#include "decoder.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    qDebug()<<"current path:"<<QDir::currentPath();

    qputenv("QTSCRCPY_ADB_PATH","..\\..\\Github\\qtscrcpy\\QtScrcpy\\tools\\adb\\win\\adb.exe");
    qputenv("QTSCRCPY_SERVER_PATH","..\\..\\Github\\qtscrcpy\\QtScrcpy\\tools\\scrcpy-server.jar");

    Decoder::init();
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    //return a.exec();
    int ret=a.exec();
    Decoder::init();
    return ret;
}

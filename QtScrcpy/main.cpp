#include "dialog.h"
#include "decoder.h"
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QTSCRCPY_ADB_PATH", "..\\qtscrcpy\\QtScrcpy\\third_party\\adb\\win\\adb.exe");
    qputenv("QTSCRCPY_SERVER_PATH", "..\\qtscrcpy\\QtScrcpy\\third_party\\scrcpy-server.jar");

    Decoder::init();

    QApplication a(argc, argv);
    Dialog w;
    w.show();

    int ret = a.exec();
    Decoder::deInit();

    return ret;
}

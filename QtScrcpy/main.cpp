#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QTSCRCPY_ADB_PATH", "..\\qtscrcpy\\QtScrcpy\\third_party\\adb\\win\\adb.exe");
    qputenv("QTSCRCPY_SERVER_PATH", "..\\qtscrcpy\\QtScrcpy\\third_party\\scrcpy-server.jar");
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}

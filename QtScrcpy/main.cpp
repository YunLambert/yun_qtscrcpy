#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QTSCRCPY_ADB_PATH","..\\..\\Github\\qtscrcpy\\QtScrcpy\\tools\\adb\\win\\adb.exe");
    qputenv("QTSCRCPY_SERVER_PATH","..\\..\\Github\\qtscrcpy\\QtScrcpy\\tools\\scrcpy-server.jar");
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}

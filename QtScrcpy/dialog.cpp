#include "adbprocess.h"
#include <QDir>
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString program = "..\\third_party\\adb\\win\\adb.exe";
    QStringList arguments;
    arguments << "C:\\Users\\Administrator\\Desktop\\test.txt";

    AdbProcess *myProcess = new AdbProcess(this);
    myProcess->start(program,Q_NULLPTR);

}

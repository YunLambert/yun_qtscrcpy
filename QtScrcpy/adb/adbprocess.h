#ifndef ADBPROCESS_H
#define ADBPROCESS_H
#include <QProcess>

class AdbProcess : public QProcess
{
public:
    AdbProcess(QObject *parent =Q_NULLPTR);

    static QString getAdbPath();

private:
    void initSignals();
    static QString s_adbPath;

private:
    void execute(const QString& serial, const QStringList& args);
};

#endif // ADBPROCESS_H

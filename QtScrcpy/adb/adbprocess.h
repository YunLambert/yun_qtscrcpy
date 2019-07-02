#ifndef ADBPROCESS_H
#define ADBPROCESS_H
#include <QProcess>

class AdbProcess : public QProcess
{
    Q_OBJECT
public:
    //  启动、执行成功与失败
    enum ADB_EXEC_RESULT {
        AER_SUCCESS_START,
        AER_ERROR_START,
        AER_SUCCESS_EXEC,
        AER_ERROR_EXEC,
        AER_ERROR_MISSING_BINARY,
    };

    AdbProcess(QObject *parent =Q_NULLPTR);

    static QString getAdbPath();

signals:
    void adbProcessResult(ADB_EXEC_RESULT processResult);
private:
    void initSignals();
    static QString s_adbPath;
    QString m_standardOutput = "";
    QString m_errorOutput = "";

public:
    void execute(const QString& serial, const QStringList& args);
    void push(const QString& serial, const QString& local, const QString& remote);
    void removePath(const QString& serial, const QString& path);
    void reverse(const QString& serial, const QString& deviceSocketName, quint16 localPort);
    void reverseRemove(const QString& serial, const QString& deviceSocketName);

    QStringList getDevicesSerialFromStdOut();
    QString getDeviceIPFromStdOut();
    QString getStdOut();
    QString getErrorOut();
};

#endif // ADBPROCESS_H

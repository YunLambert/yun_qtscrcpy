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

public:
    void execute(const QString& serial, const QStringList& args);
};

#endif // ADBPROCESS_H

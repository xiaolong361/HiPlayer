#ifndef SINGLEAPP_H
#define SINGLEAPP_H


#include <QApplication>
#include <QSharedMemory>
#include <QLocalServer>

class SingleApp : public QApplication{
    Q_OBJECT
public:

    SingleApp(int &argc, char *argv[], const QString uniqueKey);
    bool isRunning();
    bool sendMessage(const QString &message);

public slots:
    void receiveMessage();

signals:
    void sigMsgAvailable(QString message);
private:
    static const int timeout = 1000;

    bool _isRunning;
    QString _uniqueKey;
    QSharedMemory _sharedMemory;
    QLocalServer * _localServer;

};
#endif // SINGLEAPP_H

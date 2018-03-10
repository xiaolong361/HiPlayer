#include "singleApp.h"
#include <QLocalSocket>

SingleApp::SingleApp(int &argc, char *argv[], const QString uniqueKey)
: QApplication(argc, argv), _uniqueKey(uniqueKey)
{
    _sharedMemory.setKey(_uniqueKey);
    if (_sharedMemory.attach())//读取数据，必须调用attach（）,绑定_uniqueKey标志的共享内存区域
        _isRunning = true;//绑定成功,证明已经有进程创建了共享内存,有进程正在运行.
    else
    {
        _isRunning = false;
        // create shared memory.
        if (!_sharedMemory.create(1))//Creates a shared memory segment of 1 byte and attaches to the new shared memory segment
        {
            qDebug()<<"Unable to create single instance:"<<_sharedMemory.errorString().toLatin1();
            return;
        }

        // create local server and listen to incomming messages from other instances.
        _localServer = new QLocalServer(this);
        connect(_localServer, SIGNAL(newConnection()), this, SLOT(receiveMessage()));
        _localServer->listen(_uniqueKey);
    }
}

// public slots.
void SingleApp::receiveMessage()
{
    QLocalSocket * localSocket = _localServer->nextPendingConnection();
    if (!localSocket->waitForReadyRead(timeout))
    {
        qDebug(localSocket->errorString().toLatin1());
        return;
    }

    QByteArray byteArray = localSocket->readAll();
    QString message = QString::fromUtf8(byteArray.constData());
    emit sigMsgAvailable(message);
    localSocket->disconnectFromServer();
    //qDebug()<<"receive message:"<<message;
}

// public functions.
bool SingleApp::isRunning()
{
    return _isRunning;
}

bool SingleApp::sendMessage(const QString &message)
{
    if (!_isRunning)
        return false;
    QLocalSocket localSocket(this);
    localSocket.connectToServer(_uniqueKey, QIODevice::WriteOnly);
    if (!localSocket.waitForConnected(timeout))
    {
        qDebug(localSocket.errorString().toLatin1());
        return false;
    }

    localSocket.write(message.toUtf8());
    if (!localSocket.waitForBytesWritten(timeout))
    {
        qDebug(localSocket.errorString().toLatin1());
        return false;
    }

    localSocket.disconnectFromServer();
    return true;
}

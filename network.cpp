#include "network.h"

class NetWorker::Private
{
public:
    Private(NetWorker * q)
        : manager(new QNetworkAccessManager(q))
    {}
    QNetworkAccessManager *manager;
};

NetWorker * NetWorker::getInstance()
{
    static NetWorker netWorker;
    return &netWorker;
}

NetWorker::NetWorker(QObject *parent )
    : QObject(parent)
    , d(new NetWorker::Private(this))
{
    connect(d->manager, &QNetworkAccessManager::finished, this,
        &NetWorker::finished);
}

NetWorker::~NetWorker()
{
    delete d;
    d = 0;
}

void NetWorker::get(const QString &url)
{
    d->manager->get(QNetworkRequest(QUrl(url)));
}

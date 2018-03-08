#ifndef NETWORK_H
#define NETWORK_H

//网络模块，实现网络功能
//使用单例模式，封装网络接口
//使用instance()获取唯一的NetWorker对象
//使用内部类Private封装私有变量

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class NetWorker : public QObject
{

    Q_OBJECT

public:

    //获取唯一实例
    static NetWorker * getInstance();

    ~NetWorker();

    //向url发送get请求
    void get(const QString &url);

signals:
    //操作完成后发射finished信号
    void finished(QNetworkReply *reply);

private:
    class Private;//在类中定义另一个类
    friend class Private;
    Private * d;

    //使用单例模式，类的构造函数，复制构造函数和赋值运算符都声明为私有
    //若编译器支持c++ 11，Q_DECL_EQ_DELETE宏替换为 =delete
    explicit NetWorker(QObject *parent = 0);
    NetWorker(const NetWorker &) Q_DECL_EQ_DELETE;
    NetWorker &operator=(NetWorker rhs) Q_DECL_EQ_DELETE;
    //对于 C++ 的类，如果程序员没有为其定义特殊成员函数，那么
    //在需要用到某个特殊成员函数的时候，编译器会隐式的自动生成一个默认的特殊成员函数，
    //比如默认的构造函数、析构函数、拷贝构造函数以及拷贝赋值运算符。
};

#endif // NETWORK_H

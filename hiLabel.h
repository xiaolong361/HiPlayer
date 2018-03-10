#ifndef HILABEL_H
#define HILABEL_H
#include <QLabel>
#include <QTimer>

//实现带有文字滚动功能的Label
class HiLabel : public QLabel
{
    Q_OBJECT
public:
    explicit HiLabel(QWidget *parent=0);
    ~HiLabel();

    //设置文本:
    //如果ms为0则文字不滚动(默认不滚动);若不为0则一定按时间间隔滚动;
    //如果调用setText()文字将不滚动(与使用QLabel相同);
    void hi_setText(const QString & context=0, const int & ms=0);

    //停止滚动
    void hi_stop();

private slots:

    void slotTimeout();

private:
    QString m_context;
    QTimer *m_timer;

    int m_ms;
    int m_pos;
};

#endif//HILABEL_H

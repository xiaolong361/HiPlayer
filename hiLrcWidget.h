#ifndef HILRCWIDGET_H
#define HILRCWIDGET_H
#include <QtWidgets>
#include "lrcLabel.h"
#include <QString>

class HiLrcWidget:public QWidget
{
public:
    HiLrcWidget(QWidget *parent = 0);
    ~HiLrcWidget();

    //开始歌词遮罩,以intervaltime为间隔时间
    void hi_startLrcMask(qint64 intervaltime);

    //停止歌词遮罩
    void hi_stopLrcMask();

    QString text()const;

    //void setText(QString t);

    void hi_setLyricText(QString t);
private:
    void enterEvent(QEvent *);
    void paintEvent(QPaintEvent * event);
    //用于窗口位置拖动
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    LrcLabel * lrcLabel;

    //用于窗口位置拖动
    bool        m_Moveing;
    QPoint      m_MovePosition;

};

#endif // HILRCWIDGET_H

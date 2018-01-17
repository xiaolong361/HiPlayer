#ifndef LRCLABEL_H
#define LRCLABEL_H

#include <QtWidgets>
#include "hiLabel.h"

class LrcLabel : public HiLabel
{

    Q_OBJECT
public:
    explicit LrcLabel(QWidget *parent = 0);

    //开始歌词遮罩
    void hi_startLrcMask(qint64 intervaltime);

    //停止歌词遮罩
    void hi_stopLrcMask();

    //调整字体大小
    void hi_setFontSize(int size);

protected:

    //绘制窗体
    void paintEvent(QPaintEvent *);

    //鼠标事件
    //void mousePressEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);

    //菜单事件
    void contextMenuEvent(QContextMenuEvent *event);

private slots:

    void slotTimeout();

private:

    QLinearGradient linearGradient;
    QLinearGradient maskLinearGradient;
    QFont lrcFont;
    QTimer * lrcTimer;
    qreal lrcMaskWidth;
    qreal lrcMaskWidthInterval;
    QPoint offSet;
};

#endif // LRCLABEL_H

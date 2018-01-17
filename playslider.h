#ifndef PLAYSLIDER_H
#define PLAYSLIDER_H

#include <QSlider>

class PlaySlider : public QSlider
{
    Q_OBJECT
public:
    explicit PlaySlider(QWidget *parent = Q_NULLPTR);
protected:
    void mousePressEvent(QMouseEvent *event);//实现鼠标点击改变滑块位置
signals:
    void sigValueClicked(int value);
public slots:
};

#endif // PLAYSLIDER_H

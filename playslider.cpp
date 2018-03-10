#include "playslider.h"
#include <QCoreApplication>
#include <QMouseEvent>

PlaySlider::PlaySlider(QWidget *parent)
    : QSlider(parent)
{

}
void PlaySlider::mousePressEvent(QMouseEvent *event)
{
    //注意应先调用父类的鼠标点击处理事件，这样可以不影响拖动的情况
    QSlider::mousePressEvent(event);
    //获取鼠标的位置，这里并不能直接从ev中取值（因为如果是拖动的话，鼠标开始点击的位置没有意义了）
    double pos = event->pos().x() / (double)width();
    double value = pos * (maximum() - minimum()) + minimum();
    //value + 0.5 四舍五入
    setValue(value + 0.5);
    emit sigValueClicked(this->value());
}

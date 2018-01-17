#ifndef HIBUTTON_H
#define HIBUTTON_H

//#include <QtGui>
#include <QIcon>
#include <QPushButton>

class HiButton : public QPushButton
{
    Q_OBJECT
public:
    HiButton(QWidget *parent = 0);
    ~HiButton();

    //设置图标
    //若只指定一个图标，则默认“进入”，按下，松开都为此图标
    void hi_setButtonIcons(const QIcon &normal, const QIcon &focus = QIcon(), const QIcon &pressed = QIcon() );

protected:

    //重载“进入”和“离开”事件，进入时切换为另一个图标，离开时还原
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

    //重载鼠标按下和松开事件 ，切换图标
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    QIcon normalIcon;
    QIcon focusIcon;
    QIcon pressedIcon;

};


#endif//HIBUTTON_H

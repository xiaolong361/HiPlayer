#include "hiButton.h"

HiButton::HiButton(QWidget *parent)
    : QPushButton(parent)
{
    //设置图标无焦点
    setFocusPolicy(Qt::NoFocus);
}

HiButton::~HiButton()
{
}

void HiButton::enterEvent(QEvent *)
{
    if( isEnabled() && !focusIcon.isNull() )
        setIcon(focusIcon);
}

void HiButton::leaveEvent(QEvent *)
{
    if( isEnabled() )
        setIcon(normalIcon);
}


void HiButton::mousePressEvent(QMouseEvent *event)
{
    if( isEnabled() && !pressedIcon.isNull() )
        setIcon(pressedIcon);
    QPushButton::mousePressEvent(event);
}

void HiButton::mouseReleaseEvent(QMouseEvent *event)
{
    if( isEnabled() && !focusIcon.isNull() )
        setIcon(focusIcon);
    QPushButton::mouseReleaseEvent(event);
}

void HiButton::hi_setButtonIcons(const QIcon &normal, const QIcon &focus, const QIcon &pressed)
{
    normalIcon = normal;
    focusIcon = focus;
    pressedIcon = pressed;
    setIcon(normalIcon);
}

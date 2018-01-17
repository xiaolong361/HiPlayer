#ifndef HIVOLBOTTON_H
#define HIVOLBOTTON_H

#include "hiButton.h"
#include <QtWidgets>

class HiVolBotton:public QWidget
{
public:
    Q_OBJECT
    Q_PROPERTY(int hi_getVolume READ hi_getVolume WRITE hi_setVolume NOTIFY hi_volumeChanged)
public:
    HiVolBotton(QWidget *parent = 0);

    //返回音量值（0~100）
    int hi_getVolume() const;

    //设置音量条是否可见
    void hi_setSliderVisiable(bool);

public slots:

    //点击音量条使音量增加一部分
    void hi_increaseVolume();

    //点击音量条使音量减少一部分
    void hi_descVolume();

    //设置音量
    void hi_setVolume(int volume);

    //按钮单击事件，弹出菜单
    void hi_buttonClicked();

signals:

    //音量改变信号（当音量条被拖动时发射）
    void hi_volumeChanged(int volume);

private:
    HiButton * volBtn;
    QSlider * volSlider;
    QMenu * menu;
    QWidgetAction * action;
};

#endif // HIVOLBOTTON_H

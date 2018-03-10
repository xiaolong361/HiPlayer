#include "hiVolBotton.h"
#include  <QDebug>

HiVolBotton::HiVolBotton(QWidget *parent )
    :QWidget(parent)
{
    volSlider = new QSlider(Qt::Horizontal, this);
    volSlider->setRange(0, 100);
    volSlider->setGeometry(QRect(26,0,75,25));

    //当音量条被拖动时发射音量改变的信号
    connect(volSlider, SIGNAL(valueChanged(int)), this, SIGNAL(hi_volumeChanged(int)));

    volSlider->setStyleSheet("QSlider::groove:horizontal{border:0px;height:4px;}"
                          "QSlider::sub-page:horizontal{background:#0096ff;}"
                          "QSlider::add-page:horizontal{background:lightgray;} "
                          "QSlider::handle:horizontal{background:white;width:10px;border:#51b5fb 10px;border-radius:5px;margin:-3px 0px -3px 0px;}");

    volBtn = new HiButton(this);

    QIcon icon_button, icon_button_focus;
    icon_button.addFile(QStringLiteral(":/hiplayer/resources/Volumn_40_40.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon_button_focus.addFile(QStringLiteral(":/hiPlayer/resources/音量调节2.png"), QSize(), QIcon::Normal, QIcon::Off);
    volBtn->hi_setButtonIcons(icon_button, icon_button);

    volBtn->setIconSize(QSize(25,25));
    volBtn->setFlat(true);
    volBtn->setFocusPolicy(Qt::NoFocus);
    volBtn->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");
    volBtn->setGeometry(QRect(0,0,25,25));

    connect(volBtn, SIGNAL(clicked()), this, SLOT(hi_buttonClicked()));

    menu = new QMenu(this);

    action = new QWidgetAction(this);
    action->setDefaultWidget(volSlider);
    menu->addAction(action);

}
void HiVolBotton::hi_setSliderVisiable(bool a)
{
    volSlider->setVisible(a);
}

void HiVolBotton::hi_buttonClicked()
{
    menu->exec(QCursor::pos());
}

void HiVolBotton::hi_increaseVolume()
{
    volSlider->triggerAction(QSlider::SliderPageStepAdd);
    qDebug()<<"hi_increaseVolume";
}

void HiVolBotton::hi_descVolume()
{
    volSlider->triggerAction(QSlider::SliderPageStepSub);
    qDebug()<<"hi_descVolume";
}

int HiVolBotton::hi_getVolume() const
{
    return volSlider->value();
}

void HiVolBotton::hi_setVolume(int volume)
{
    volSlider->setValue(volume);
}

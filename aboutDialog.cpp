#include "aboutDialog.h"
#include "hiButton.h"

#include <QPushButton>
#include <QIcon>
#include <QPalette>
#include <QPixmap>
#include <QPainter>
#include <QApplication>

AboutDialog::AboutDialog(QWidget *parent)
    :QDialog(parent)
    ,m_Moveing(false)
{
    m_exitButton = new HiButton(this);
    m_exitButton->setObjectName(QStringLiteral("exitButton"));
    m_exitButton->setGeometry(QRect(240, 14, 30, 30));
    QIcon icon_exit, icon_exit_focus;
    icon_exit.addFile(QStringLiteral(":/hiplayer/resources/关闭.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon_exit_focus.addFile(QStringLiteral(":/hiplayer/resources/关闭按钮.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_exitButton->hi_setButtonIcons(icon_exit, icon_exit);

    m_exitButton->setIconSize(QSize(20,20));
    m_exitButton->setFlat(true);
    m_exitButton->setFocusPolicy(Qt::NoFocus);
    //RGB(255,255,255)表示白色.基本语法:{color: Rgba (red, green, blue, opacity)}
    m_exitButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

    connect(m_exitButton, SIGNAL(clicked()), this, SLOT(close()));

    //去除标题栏,需要自定义窗口的拖动
    this->setWindowFlags(Qt::FramelessWindowHint);

    //设置窗体背景透明，配合paintEvent设置不规则背景图
    setAttribute(Qt::WA_TranslucentBackground);

    //半透明
    this->setWindowOpacity(0.9);

    //固定大小
    this->setFixedSize(290, 310);

    //模态窗口（即弹出后无法点击主界面）
    this->setModal(true);
}

void AboutDialog::paintEvent(QPaintEvent * )
{
    QPainter p(this);
    p.drawPixmap(0, 0 , QPixmap(":/hiplayer/resources/about.png"));
}

AboutDialog::~AboutDialog()
{}

void AboutDialog::mousePressEvent(QMouseEvent *event)
{
    m_Moveing=true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于父窗口的位置
    m_MovePosition=event->globalPos() - pos();
    return QDialog::mousePressEvent(event);
}

void AboutDialog::mouseMoveEvent(QMouseEvent *event)
{
    //(event->buttons() && Qt::LeftButton)按下是左键
    //鼠标移动事件需要移动窗口，窗口移动到哪里呢？就是要获取鼠标移动中，窗口在整个屏幕的坐标，然后move到这个坐标，怎么获取坐标？
    //通过事件event->globalPos()知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
    if (m_Moveing && (event->buttons() && Qt::LeftButton)
            && (event->globalPos()-m_MovePosition).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos()-m_MovePosition);//相对于桌面的位置.
        m_MovePosition = event->globalPos() - pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void AboutDialog::mouseReleaseEvent(QMouseEvent *)
{
    m_Moveing=false;
}

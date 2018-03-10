#include "hiLrcWidget.h"

HiLrcWidget::HiLrcWidget(QWidget *parent)
    :QWidget(parent)
{
    lrcLabel=nullptr;

    //无边界的窗口,总在最上
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    //去除窗体原背景(背景透明)
    setAttribute(Qt::WA_TranslucentBackground);

    //固定大小
    this->setFixedSize(800, 60);

    lrcLabel =new LrcLabel(this);
    lrcLabel->setGeometry(QRect(0, 6, 800, 60));
}

HiLrcWidget::~HiLrcWidget()
{
    if(lrcLabel!=nullptr)
    {
        delete lrcLabel;
    }
}

//开始歌词遮罩,以intervaltime(ms)为间隔时间
void HiLrcWidget::hi_startLrcMask(qint64 intervaltime)
{
    lrcLabel->hi_startLrcMask(intervaltime);
}

//停止歌词遮罩
void HiLrcWidget::hi_stopLrcMask()
{
    lrcLabel->hi_stopLrcMask();
}

QString HiLrcWidget::text()const
{
    return lrcLabel->text();
}

void HiLrcWidget::hi_setLyricText(QString t)//设置歌词文本(无滚动效果)
{
    lrcLabel->setText(t);
}

void HiLrcWidget::paintEvent(QPaintEvent * event)
{
    QPainter p(this);
    p.drawPixmap(0, 0, QPixmap(":/hiplayer/resources/lrc_background.png"));
    lrcLabel->raise();
    QWidget::paintEvent(event);
}

void HiLrcWidget::enterEvent(QEvent *)
{
    setCursor(Qt::PointingHandCursor);
}

void HiLrcWidget::mousePressEvent(QMouseEvent *event)
{
    m_Moveing=true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于父窗口的位置
    m_MovePosition=event->globalPos() - pos();
    event->accept();
}

void HiLrcWidget::mouseMoveEvent(QMouseEvent *event)
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
    event->accept();
}

void HiLrcWidget::mouseReleaseEvent(QMouseEvent *)
{
    m_Moveing=false;
}

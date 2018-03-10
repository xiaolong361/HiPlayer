#include "hiLabel.h"
#include <qDebug>

HiLabel::HiLabel(QWidget *parent)
    :QLabel(parent)
    ,m_context("")
    ,m_timer(NULL)
    ,m_ms(0)
    ,m_pos(0)
{
}

HiLabel::~HiLabel()
{
    hi_stop();
}

void HiLabel::hi_stop()//label停止滚动,直接从头显示文本
{
    if (m_timer)
    {
        if (m_timer->isActive())
        {
            m_timer->stop();
        }
        delete m_timer;
        m_timer = NULL;
    }
    setText(m_context);
}

void HiLabel::hi_setText(const QString &context,const int &ms)//设置label文本和滚动的时间间隔
{
    m_context = context;
    m_ms = ms;

    if (m_ms != 0 && m_timer == NULL)
    {
        m_timer = new QTimer(this);
        if (m_timer)
        {
            connect(m_timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
            m_timer->start(m_ms);
        }
       //return;
    }
    setText(m_context);
}

void HiLabel::slotTimeout()//定时器触发则显示滚动的文字
{

    QString str="";

    if (m_pos > m_context.count())
    {
        m_pos = 0;
    }

    str = m_context.mid(m_pos);


    setText(str);
    //qDebug()<<"str:"<<str;
    m_pos++;
}

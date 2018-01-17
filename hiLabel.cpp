#include "hiLabel.h"

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

//void HiLabel::hi_init(int ms)
//{
//    m_context = "";
//    m_timer = NULL;
//    m_ms = ms;//默认为0

//    m_pos = 0;
//}

void HiLabel::hi_stop()
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
}

void HiLabel::hi_setText(const QString &context,const int &ms)
{
    bool b=false;

    m_context = context;
    m_ms = ms;

    if (m_ms != 0 && m_timer == NULL)
    {
        m_timer = new QTimer(this);

        if (m_timer)
        {
            b = connect(m_timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
            m_timer->start(m_ms);
        }

    }
}

void HiLabel::slotTimeout()
{

    QString str="";

    if (m_pos > m_context.count())
    {
        m_pos = 0;
    }

    str = m_context.mid(m_pos);

    setText(str);
    m_pos++;
}

#include "miniWindow.h"
#include "hiplayer.h"

MiniWindow::MiniWindow(HiPlayer *hiplayer,QWidget *parent):QWidget(parent)
{
    mainWindow = hiplayer;

    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //半透明
    this->setWindowOpacity(0.9);

    //固定大小
    this->setFixedSize(100, 100);

    miniPlayButton = new HiButton( this);
    miniPlayButton->setObjectName(QStringLiteral("miniPlayButton"));
    miniPlayButton->setGeometry(QRect(35, 30, 33, 33));

    miniPauseButton = new HiButton( this);
    miniPauseButton->setObjectName(QStringLiteral("miniPauseButton"));
    miniPauseButton->setGeometry(QRect(31, 30, 33, 33));
    miniPauseButton->setVisible(false);

    miniNextButton = new HiButton( this);
    miniNextButton->setObjectName(QStringLiteral("nextButton"));
    miniNextButton->setGeometry(QRect(70, 64, 16, 16));

    miniLastButton = new HiButton(this);
    miniLastButton->setObjectName(QStringLiteral("lastButton"));
    miniLastButton->setGeometry(QRect(8,57,12,12));

    miniMaxButton=new HiButton(this);
    miniMaxButton->setObjectName(QStringLiteral("maxButton"));
    miniMaxButton->setGeometry(QRect(70,14,14,14));

    //设置图标
    QIcon icon_play;
    icon_play.addFile(QStringLiteral(":/hiplayer/resources/play_mini.png"));
    miniPlayButton->hi_setButtonIcons(icon_play,icon_play);

    miniPlayButton->setIconSize(QSize(36,36));
    miniPlayButton->setFlat(true);
    miniPlayButton->setFocusPolicy(Qt::NoFocus);
    miniPlayButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

    QIcon icon_pause;
    icon_pause.addFile(QStringLiteral(":/hiplayer/resources/pause_mini.png"));
    miniPauseButton->hi_setButtonIcons(icon_pause);

    miniPauseButton->setIconSize(QSize(36,36));
    miniPauseButton->setFlat(true);
    miniPauseButton->setFocusPolicy(Qt::NoFocus);
    miniPauseButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

    QIcon icon_next;
    icon_next.addFile(QStringLiteral(":/hiplayer/resources/next_mini.png"));
    miniNextButton->hi_setButtonIcons(icon_next);

    miniNextButton->setIconSize(QSize(16,16));
    miniNextButton->setFlat(true);
    miniNextButton->setFocusPolicy(Qt::NoFocus);
    miniNextButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

    QIcon icon_last;
    icon_last.addFile(QStringLiteral(":/hiplayer/resources/last_mini.png"));
    miniLastButton->hi_setButtonIcons(icon_last);

    miniLastButton->setIconSize(QSize(12,12));
    miniLastButton->setFlat(true);
    miniLastButton->setFocusPolicy(Qt::NoFocus);
    miniLastButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

    QIcon icon_max;
    icon_max.addFile(QStringLiteral(":/hiplayer/resources/max_mini.png"));
    miniMaxButton->hi_setButtonIcons(icon_max);

    miniMaxButton->setIconSize(QSize(14,14));
    miniMaxButton->setFlat(true);
    miniMaxButton->setFocusPolicy(Qt::NoFocus);
    miniMaxButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");


    hi_initMenuActions();
    connect(miniPlayButton, SIGNAL(clicked()), this, SLOT(slotPlay()));
    connect(miniPauseButton, SIGNAL(clicked()), this, SLOT(slotPause()));
    connect(miniNextButton, SIGNAL(clicked()), this, SLOT(slotNextMusic()));
    connect(miniLastButton,SIGNAL(clicked()),this,SLOT(slotLastMusic()));
    connect(miniMaxButton,SIGNAL(clicked()),this,SLOT(slotBackToMain()));
}

MiniWindow::~MiniWindow()
{

}

void MiniWindow::paintEvent(QPaintEvent *event)//绘制窗体背景
{
    qDebug()<<"paintEvent";
    QPainter p(this);
    p.drawPixmap(0, 0 , QPixmap(":/hiplayer/resources/mini_back.png"));
    QWidget::paintEvent(event);
}

void MiniWindow::hi_initMenuActions()//设置右键菜单
{
    mode0 = new QAction(QString::fromUtf8("单曲播放"), this);
    mode1 = new QAction(QString::fromUtf8("列表循环"), this);
    mode2 = new QAction(QString::fromUtf8("单曲循环"), this);
    mode3 = new QAction(QString::fromUtf8("随机播放"), this);

    modeGroup = new QActionGroup(this);
    modeGroup->addAction(mode0);
    modeGroup->addAction(mode1);
    modeGroup->addAction(mode2);
    modeGroup->addAction(mode3);

    mode0->setCheckable(true);
    mode1->setCheckable(true);
    mode2->setCheckable(true);
    mode3->setCheckable(true);
    mode0->setChecked(true);

    mainForm = new QAction(QString::fromUtf8("返回主界面"),this);
    next = new QAction(QString::fromUtf8("下一曲"),this);
    last = new QAction(QString::fromUtf8("上一曲"),this);
    lyric = new QAction(QString::fromUtf8("桌面歌词"), this);
    exit = new QAction(QString::fromUtf8("退出"),this);

    volSlider = new QSlider(Qt::Horizontal, this);
    volSlider->setRange(0, 100);
    volSlider->setGeometry(QRect(26,0,75,25));
    connect(volSlider, SIGNAL(valueChanged(int)), this, SLOT(slotUpdateVol(int)));

    volSlider->setStyleSheet("QSlider::groove:horizontal{border:0px;height:4px;}"
        "QSlider::sub-page:horizontal{background:#0096ff;}"
        "QSlider::add-page:horizontal{background:lightgray;} "
        "QSlider::handle:horizontal{background:white;width:10px;border:#51b5fb 10px;border-radius:5px;margin:-3px 0px -3px 0px;}");

    setVolumn = new QWidgetAction(this);
    setVolumn->setDefaultWidget(volSlider);

    contextMenu = new QMenu(this);
    contextMenu->addAction(mainForm);
    contextMenu->addSeparator();
    contextMenu->addAction(setVolumn);
    contextMenu->addSeparator();
    contextMenu->addAction(next);
    contextMenu->addAction(last);
    contextMenu->addSeparator();
    contextMenu->addActions(modeGroup->actions());
    contextMenu->addSeparator();
    contextMenu->addAction(lyric);
    contextMenu->addSeparator();
    contextMenu->addAction(exit);

    contextMenu->setStyleSheet(
        "QMenu{padding:5px;background:white;border:1px solid gray;}"
        "QMenu::item{padding:0px 40px 0px 30px;height:25px;}"
        "QMenu::item:selected:enabled{background:#0096ff;color:white;}"
        "QMenu::item:selected:!enabled{background:transparent;}"
        "QMenu::separator{height:1px;background:lightgray;margin:5px 0px 5px 0px;}");


    connect(mode0, SIGNAL(triggered()), this, SLOT(slotSetMode()));
    connect(mode1, SIGNAL(triggered()), this, SLOT(slotSetMode()));
    connect(mode2, SIGNAL(triggered()), this, SLOT(slotSetMode()));
    connect(mode3, SIGNAL(triggered()), this, SLOT(slotSetMode()));

    connect(mainForm, SIGNAL(triggered()), this, SLOT(slotBackToMain()));
    connect(next, SIGNAL(triggered()), this, SLOT(slotNextMusic()));
    connect(last, SIGNAL(triggered()), this, SLOT(slotLastMusic()));
    connect(lyric, SIGNAL(triggered()), this, SLOT(slotLyricAction()));
    connect(exit, SIGNAL(triggered()), this, SLOT(slotExit()));
}

void MiniWindow::hi_initPlayMode(int vol)//初始化播放模式和音量
{
    switch(mainWindow->playMode){
    case 0:
        mode0->setChecked(true);
        break;
    case 1:
        mode1->setChecked(true);
        break;
    case 2:
        mode2->setChecked(true);
        break;
    case 3:
        mode3->setChecked(true);
        break;
    }

    if(mainWindow->playButton->isVisible()){
        miniPlayButton->setVisible(true);
        miniPauseButton->setVisible(false);
    }
    else {
        miniPlayButton->setVisible(false);
        miniPauseButton->setVisible(true);
    }

    volSlider->setValue(vol);
}

void MiniWindow::contextMenuEvent(QContextMenuEvent *)//鼠标右键触发
{
    contextMenu->exec(QCursor::pos());
}

void MiniWindow::slotExit()
{
    mainWindow->close();
    this->close();
}

void MiniWindow::slotBackToMain()
{
    mainWindow->show();
    this->hide();
}

void MiniWindow::slotNextMusic()
{

    mainWindow->slotNextButtonClicked();
}

void MiniWindow::slotLastMusic()
{
    mainWindow->slotLastButtonClicked();
}

void MiniWindow::slotPlay()
{
    mainWindow->slotPlayButtonClicked();
    miniPauseButton->setVisible(true);
    miniPlayButton->setVisible(false);
}

void MiniWindow::slotPause()
{
    mainWindow->slotPauseButtonClicked();
    miniPauseButton->setVisible(false);
    miniPlayButton->setVisible(true);
}

void MiniWindow::slotSetMode()
{
    if(mode0->isChecked()) {
        mainWindow->slotSetModeFromMini(0);
    }
    else if(mode1->isChecked()) {
        mainWindow->slotSetModeFromMini(1);
    }
    else if(mode2->isChecked()) {
        mainWindow->slotSetModeFromMini(2);
    }
    else if(mode3->isChecked()) {
        mainWindow->slotSetModeFromMini(3);
    }
}

void MiniWindow::slotUpdateVol(int a)
{
    mainWindow->slotSetVolFromMini(a);
}

void MiniWindow::slotLyricAction()
{
    mainWindow->slotLyricButtonClicked();
}

void MiniWindow::mousePressEvent(QMouseEvent *event)
{
    m_Moveing=true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于父窗口的位置
    m_MovePosition=event->globalPos() - pos();
    return QWidget::mousePressEvent(event);
}

void MiniWindow::mouseMoveEvent(QMouseEvent *event)
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
    return QWidget::mouseMoveEvent(event);
}

void MiniWindow::mouseReleaseEvent(QMouseEvent *)
{
    m_Moveing=false;
}


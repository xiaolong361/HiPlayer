#include "hiplayer.h"
#include "miniWindow.h"

HiPlayer::HiPlayer(QWidget *parent)
    : QWidget(parent)
{
    hi_initUi();
    hi_initPlayer();
    hi_initConnections();
    hi_initWindows();
    hi_initMenuActions();
    hi_initNetwork();
    dirPath = QApplication::applicationDirPath();
    slotReadList();
}

HiPlayer::~HiPlayer()
{}

void HiPlayer::hi_initUi()//初始化界面
{
    picLabel = new QLabel( this);
    picLabel->setGeometry(QRect(40, 45, 100, 100));
    picLabel->setScaledContents(true);
    picLabel->setPixmap(QPixmap(":/hiplayer/resources/album.png"));

    nameLabel = new HiLabel(this);
    nameLabel->setGeometry(QRect(150, 55, 220, 20));

    musicianLabel = new QLabel(this);
    musicianLabel->setGeometry(QRect(150, 85, 220, 15));

    albumLabel = new QLabel(this);
    albumLabel->setGeometry(QRect(150, 115, 220, 15));

    playSlider = new PlaySlider(this);
    playSlider->setObjectName(QStringLiteral("playSlider"));
    playSlider->setStyleSheet("QSlider::groove:horizontal{border:0px;height:4px;}"
                              "QSlider::sub-page:horizontal{background:#0096ff;}"
                              "QSlider::add-page:horizontal{background:lightgray;} "
                              "QSlider::handle:horizontal{background:white;width:10px;border:#51b5fb 10px;border-radius:5px;margin:-3px 0px -3px 0px;}");
    playSlider->setGeometry(QRect(40, 150, 290, 20));
    playSlider->setOrientation(Qt::Horizontal);

    timeLabel = new QLabel( this);
    timeLabel->setObjectName(QStringLiteral("timeLabel"));
    timeLabel->setGeometry(QRect(340, 150, 51, 16));

    playlistTable = new QTableWidget( this);
    playlistTable->setObjectName(QStringLiteral("playlistTable"));
    playlistTable->setGeometry(QRect(25, 240, 350, 320));
    playlistTable->setItemDelegate(new NoFocusDelegate());

    addButton = new HiButton( this);
    addButton->setObjectName(QStringLiteral("addButton"));
    addButton->setGeometry(QRect(40, 190, 31, 31));
    modeButton = new HiButton( this);
    modeButton->setObjectName(QStringLiteral("modeButton"));
    modeButton->setGeometry(QRect(290, 190, 31, 31));
    lastButton = new HiButton( this);
    lastButton->setObjectName(QStringLiteral("lastButton"));
    lastButton->setGeometry(QRect(120, 185, 41, 41));
    nextButton = new HiButton( this);
    nextButton->setObjectName(QStringLiteral("nextButton"));
    nextButton->setGeometry(QRect(240, 185, 41, 41));
    lyricButton = new HiButton( this);
    lyricButton->setObjectName(QStringLiteral("lyricButton"));
    lyricButton->setGeometry(QRect(80, 190, 31, 31));
    playButton = new HiButton( this);
    playButton->setObjectName(QStringLiteral("playButton"));
    playButton->setGeometry(QRect(170, 175, 61, 61));
    pauseButton = new HiButton( this);
    pauseButton->setObjectName(QStringLiteral("pauseButton"));
    pauseButton->setGeometry(QRect(170, 175, 61, 61));
    pauseButton->setVisible(false);

    volButton = new HiVolBotton(this);
    volButton->setObjectName(QStringLiteral("volButton"));
    volButton->setGeometry(QRect(333, 193, 31, 31));
    volButton->hi_setVolume(50);

    mminButton = new HiButton( this);
    mminButton->setObjectName(QStringLiteral("mminButton"));
    mminButton->setGeometry(QRect(307, 3, 29, 31));
    minButton = new HiButton( this);
    minButton->setObjectName(QStringLiteral("minButton"));
    minButton->setGeometry(QRect(337, 3, 29, 31));
    exitButton = new HiButton( this);
    exitButton->setObjectName(QStringLiteral("exitButton"));
    exitButton->setGeometry(QRect(364, 3, 29, 31));
    logoButton = new HiButton( this);
    logoButton->setObjectName(QStringLiteral("logoButton"));
    logoButton->setGeometry(QRect(8, 8, 38, 38));

    logoButton->raise();
    picLabel->raise();
    playSlider->raise();
    timeLabel->raise();
    playlistTable->raise();
    addButton->raise();
    modeButton->raise();
    nextButton->raise();
    lyricButton->raise();
    playButton->raise();
    volButton->raise();
    mminButton->raise();
    minButton->raise();
    exitButton->raise();

    timeLabel->setText(tr("00:00"));
    nameLabel->setText(tr("Name " ));
    musicianLabel->setText(tr("Musician" ));
    albumLabel->setText(tr("Album" ));

    //设置图标
    QIcon icon_play, icon_play_focus;
    icon_play.addFile(QStringLiteral(":/hiplayer/resources/Play_100_100.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon_play_focus.addFile(QStringLiteral(":/hiPlayer/resources/播放按钮-主界面2.png"), QSize(), QIcon::Normal, QIcon::Off);
    playButton->hi_setButtonIcons(icon_play, icon_play);
    playButton->setIconSize(QSize(60,60));
    playButton->setFlat(true);
    playButton->setFocusPolicy(Qt::NoFocus);
    playButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

    QIcon icon_pause, icon_pause_focus;
    icon_pause.addFile(QStringLiteral(":/hiplayer/resources/Pause_100_100.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon_pause_focus.addFile(QStringLiteral(":/hiPlayer/resources/暂停按钮-主界面2.png"), QSize(), QIcon::Normal, QIcon::Off);
    pauseButton->hi_setButtonIcons(icon_pause, icon_pause);
    pauseButton->setIconSize(QSize(60,60));
    pauseButton->setFlat(true);
    pauseButton->setFocusPolicy(Qt::NoFocus);
    pauseButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");


    QIcon icon_lyric, icon_lyric_focus;
    icon_lyric.addFile(QStringLiteral(":/hiplayer/resources/Lyric_40_40.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon_lyric_focus.addFile(QStringLiteral(":/hiPlayer/resources/歌词按钮2.png"), QSize(), QIcon::Normal, QIcon::Off);
    lyricButton->hi_setButtonIcons(icon_lyric, icon_lyric);
    lyricButton->setIconSize(QSize(25,25));
    lyricButton->setFlat(true);
    lyricButton->setFocusPolicy(Qt::NoFocus);
    lyricButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

    QIcon icon_exit, icon_exit_focus;
    icon_exit.addFile(QStringLiteral(":/hiplayer/resources/关闭.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon_exit_focus.addFile(QStringLiteral(":/hiPlayer/resources/关闭按钮2.png"), QSize(), QIcon::Normal, QIcon::Off);
    exitButton->hi_setButtonIcons(icon_exit, icon_exit);
    exitButton->setIconSize(QSize(18,18));
    exitButton->setFlat(true);
    exitButton->setFocusPolicy(Qt::NoFocus);
    exitButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

    QIcon icon_min, icon_min_focus;
    icon_min.addFile(QStringLiteral(":/hiplayer/resources/缩小.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon_min_focus.addFile(QStringLiteral(":/hiPlayer/resources/迷你模式按钮2.png"), QSize(), QIcon::Normal, QIcon::Off);
    minButton->hi_setButtonIcons(icon_min, icon_min);
    minButton->setIconSize(QSize(18,18));
    minButton->setFlat(true);
    minButton->setFocusPolicy(Qt::NoFocus);
    minButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

    QIcon icon_mmin, icon_mmin_focus;
    icon_mmin.addFile(QStringLiteral(":/hiplayer/resources/最小化.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon_mmin_focus.addFile(QStringLiteral(":/hiPlayer/resources/缩小按钮2.png"), QSize(), QIcon::Normal, QIcon::Off);
    mminButton->hi_setButtonIcons(icon_mmin, icon_mmin);
    mminButton->setIconSize(QSize(18,18));
    mminButton->setFlat(true);
    mminButton->setFocusPolicy(Qt::NoFocus);
    mminButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

    QIcon icon_logo, icon_logo_focus;
    icon_logo.addFile(QStringLiteral(":/hiplayer/resources/HiPlayer_38_38.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon_logo_focus.addFile(QStringLiteral(":/hiPlayer/resources/左上角logo按钮2.png"), QSize(), QIcon::Normal, QIcon::Off);
    logoButton->hi_setButtonIcons(icon_logo, icon_logo);
    logoButton->setIconSize(QSize(48, 48));
    logoButton->setFlat(true);
    logoButton->setFocusPolicy(Qt::NoFocus);
    logoButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

    QIcon icon_next, icon_next_focus;
    icon_next.addFile(QStringLiteral(":/hiplayer/resources/Next_40_40.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon_next_focus.addFile(QStringLiteral(":/hiPlayer/resources/下一曲2.png"), QSize(), QIcon::Normal, QIcon::Off);
    nextButton->hi_setButtonIcons(icon_next, icon_next);
    nextButton->setIconSize(QSize(40,40));
    nextButton->setFlat(true);
    nextButton->setFocusPolicy(Qt::NoFocus);
    nextButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

    QIcon icon_last, icon_last_focus;
    icon_last.addFile(QStringLiteral(":/hiplayer/resources/Last_40_40.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon_last_focus.addFile(QStringLiteral(":/hiPlayer/resources/上一曲2.png"), QSize(), QIcon::Normal, QIcon::Off);
    lastButton->hi_setButtonIcons(icon_last, icon_last);
    lastButton->setIconSize(QSize(40,40));
    lastButton->setFlat(true);
    lastButton->setFocusPolicy(Qt::NoFocus);
    lastButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

    QIcon icon_mode, icon_mode_focus;
    icon_mode.addFile(QStringLiteral(":/hiplayer/resources/mode.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon_mode_focus.addFile(QStringLiteral(":/hiPlayer/resources/播放模式2.png"), QSize(), QIcon::Normal, QIcon::Off);
    modeButton->hi_setButtonIcons(icon_mode, icon_mode);
    modeButton->setIconSize(QSize(25,25));
    modeButton->setFlat(true);
    modeButton->setFocusPolicy(Qt::NoFocus);
    modeButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

    QIcon icon_add, icon_add_focus;
    icon_add.addFile(QStringLiteral(":/hiplayer/resources/addMusic_40_40.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon_add_focus.addFile(QStringLiteral(":/hiPlayer/resources/添加歌曲2.png"), QSize(), QIcon::Normal, QIcon::Off);
    addButton->hi_setButtonIcons(icon_add, icon_add);
    addButton->setIconSize(QSize(25,25));
    addButton->setFlat(true);
    addButton->setFocusPolicy(Qt::NoFocus);
    addButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

    //去除标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //半透明
    this->setWindowOpacity(1);
    setAttribute(Qt::WA_TranslucentBackground);

    //固定大小
    this->setFixedSize(400, 600);

    //设置音乐信息字体颜色
    QColor fontcolor(1, 149, 255);
    QPalette fontPalette;
    fontPalette.setColor(QPalette::WindowText, fontcolor);
    nameLabel->setPalette(fontPalette);
    musicianLabel->setPalette(fontPalette);
    albumLabel->setPalette(fontPalette);

    QColor timeColor(106, 182, 240);
    QPalette timePalette;
    timePalette.setColor(QPalette::WindowText, timeColor);
    timeLabel->setPalette(timePalette);

    nameLabel->setFont(QFont(QString::fromUtf8("微软雅黑"), 12));

    QFont othersfont(QString::fromUtf8("微软雅黑"), 9);
    musicianLabel->setFont(othersfont);
    albumLabel->setFont(othersfont);
    timeLabel->setFont(othersfont);

    if (playlistTable->columnCount() < 1)//列数默认为0
        playlistTable->setColumnCount(2);
    //QTableWidgetItem * __qtablewidgetitem = new QTableWidgetItem();
    //playlistTable->setHorizontalHeaderItem(0, __qtablewidgetitem);

    //设置列宽
    playlistTable->setColumnWidth(0,300);
    playlistTable->setColumnWidth(1,45);
    //禁止编辑单元格内容
    playlistTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //选中一行
    playlistTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    //去掉水平滚动条
    playlistTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //垂直滚动条按项移动
    playlistTable->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    //去除水平表头
    playlistTable->horizontalHeader()->setFixedHeight(0);
    //去除垂直表头
    playlistTable->verticalHeader()->setFixedWidth(0);
    //设置无边框
    playlistTable->setFrameShape(QFrame::NoFrame);
    //设置不显示格子线
    playlistTable->setShowGrid(false);
    //设置右键菜单
    playlistTable->setContextMenuPolicy(Qt::CustomContextMenu);
    //设置背景颜色
    QPalette pal;
    pal.setBrush(QPalette::Base, QBrush(QColor(255, 255, 255)));
    playlistTable->setPalette(pal);
    //设置竖直滚动条样式
    playlistTable->setStyleSheet("QScrollBar{background:transparent; width: 5px;}"
                                 "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
                                 "QScrollBar::handle:hover{background:gray;}"
                                 "QScrollBar::sub-line{background:transparent;}"
                                 "QScrollBar::add-line{background:transparent;}");
    //使拖动操作生效
    playlistTable->setAcceptDrops(true);
    setAcceptDrops(true);
}

void HiPlayer::hi_initPlayer()//初始化播放器,设置播放模式为单曲播放
{
    mediaPlayer = new QMediaPlayer(this);
    mediaList = new QMediaPlaylist(this);
    mediaPlayer->setPlaylist(mediaList);

    playMode = Play_Mode::SINGAL;
    //preIndex = -1;
    currentIndex = 0;

    mediaList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
}

void HiPlayer::hi_initConnections()
{
    connect(mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(slotUpdatePosition(qint64)));
    connect(mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(slotUpdateProcessbar(qint64)));
    connect(mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)),this, SLOT(slotUpdateState(QMediaPlayer::State)));
    connect(mediaPlayer, SIGNAL(metaDataChanged()), this, SLOT(slotUpdateMetaData()));
    connect(playSlider, SIGNAL(sliderMoved(int)), this, SLOT(slotSetPlayPosition(int)));
    connect(playSlider, SIGNAL(sliderReleased()), this, SLOT(slotSetPosition()));
    //connect(playSlider,SIGNAL(valueChanged(int)),this,SLOT(slotPlayValueChanged(int)));
    connect(volButton, SIGNAL(hi_volumeChanged(int)), mediaPlayer, SLOT(setVolume(int)));

    connect(playlistTable, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(slotPlaylistDoubleClicked(int, int)));
    connect(playlistTable, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(slotPlaylistMenuRequested(const QPoint &)));

    connect(addButton, SIGNAL(clicked()), this, SLOT(slotOpenMusic()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(playButton, SIGNAL(clicked()), this, SLOT(slotPlayButtonClicked()));
    connect(lyricButton, SIGNAL(clicked()), this, SLOT(slotLyricButtonClicked()));
    connect(logoButton, SIGNAL(clicked()), this, SLOT(slotLogoButtonClicked()));
    connect(modeButton, SIGNAL(clicked()), this, SLOT(slotModeButtonClicked()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(slotNextButtonClicked()));
    connect(lastButton, SIGNAL(clicked()), this, SLOT(slotLastButtonClicked()));
    connect(pauseButton, SIGNAL(clicked()), this, SLOT(slotPauseButtonClicked()));
    connect(minButton, SIGNAL(clicked()), this, SLOT(slotMinButtonClicked()));
    connect(mminButton, SIGNAL(clicked()), this, SLOT(showMinimized()));

    connect(playSlider,SIGNAL(sigValueClicked(int)),this,SLOT(slotSliderValueClicked(int)));
    //connect(this, SIGNAL(destroyed()), this, SLOT(slotClose()));
    connect(mediaList, SIGNAL(mediaInserted()), this, SLOT(slotWriteList()));
}


void HiPlayer::hi_initWindows()
{
    aboutForm = new AboutDialog();
    aboutForm->hide();
    lrcWidget = new HiLrcWidget(this);

    miniForm = new MiniWindow();
    miniForm->hi_setParent(this);
    miniForm->hide();
}

void HiPlayer::hi_initMenuActions()
{
    modeSingal = new QAction(QString::fromUtf8("单曲播放"), this);
    modeListCircle = new QAction(QString::fromUtf8("列表循环"), this);
    modeSingalCircle = new QAction(QString::fromUtf8("单曲循环"), this);
    modeRandom = new QAction(QString::fromUtf8("随机播放"), this);

    connect(modeSingal, SIGNAL(triggered()), this, SLOT(slotSetPlayMode()));
    connect(modeListCircle, SIGNAL(triggered()), this, SLOT(slotSetPlayMode()));
    connect(modeSingalCircle, SIGNAL(triggered()), this, SLOT(slotSetPlayMode()));
    connect(modeRandom, SIGNAL(triggered()), this, SLOT(slotSetPlayMode()));

    modeActionGroup = new QActionGroup(this);
    modeActionGroup->addAction(modeSingal);
    modeActionGroup->addAction(modeListCircle);
    modeActionGroup->addAction(modeSingalCircle);
    modeActionGroup->addAction(modeRandom);


    modeSingal->setCheckable(true);
    modeListCircle->setCheckable(true);
    modeSingalCircle->setCheckable(true);
    modeRandom->setCheckable(true);
    modeSingal->setChecked(true);

    playModeMenu = new QMenu(modeButton);
    playModeMenu->setStyleSheet(
                "QMenu{padding:5px;background:white;border:1px solid gray;}"
                "QMenu::item{padding:0px 40px 0px 30px;height:25px;}"
                "QMenu::item:selected:enabled{background:#0096ff;color:white;}"
                "QMenu::item:selected:!enabled{background:transparent;}"
                "QMenu::separator{height:1px;background:lightgray;margin:5px 0px 5px 0px;}");
    playModeMenu->addActions(modeActionGroup->actions());


    contextMenuLess = new QMenu(playlistTable);
    contextMenuMore = new QMenu(playlistTable);
    addMusic = new QAction(QString::fromUtf8("添加歌曲"),this);
    addFileDiv = new QAction(QString::fromUtf8("添加目录"),this);
    removeCurr = new QAction(QString::fromUtf8("移除本曲"),this);
    removeAll = new QAction(QString::fromUtf8("移除所有"),this);

    connect(addMusic, SIGNAL(triggered()), this, SLOT(slotOpenMusic()));
    connect(addFileDiv, SIGNAL(triggered()), this, SLOT(slotOpenDir()));
    connect(removeCurr, SIGNAL(triggered()), this, SLOT(slotRemoveCurrentMusic()));
    connect(removeAll, SIGNAL(triggered()), this, SLOT(slotClearList()));

    contextMenuLess->addAction(addMusic);
    contextMenuLess->addAction(addFileDiv);
    contextMenuLess->addSeparator();
    contextMenuLess->addAction(removeAll);

    contextMenuMore->addAction(addMusic);
    contextMenuMore->addAction(addFileDiv);
    contextMenuMore->addSeparator();
    contextMenuMore->addAction(removeCurr);
    contextMenuMore->addAction(removeAll);

    contextMenuLess->setStyleSheet(
                "QMenu{padding:5px;background:white;border:1px solid gray;}"
                "QMenu::item{padding:0px 40px 0px 30px;height:25px;}"
                "QMenu::item:selected:enabled{background:#0096ff;color:white;}"
                "QMenu::item:selected:!enabled{background:transparent;}"
                "QMenu::separator{height:1px;background:lightgray;margin:5px 0px 5px 0px;}");

    contextMenuMore->setStyleSheet(
                "QMenu{padding:5px;background:white;border:1px solid gray;}"
                "QMenu::item{padding:0px 40px 0px 30px;height:25px;}"
                "QMenu::item:selected:enabled{background:#0096ff;color:white;}"
                "QMenu::item:selected:!enabled{background:transparent;}"
                "QMenu::separator{height:1px;background:lightgray;margin:5px 0px 5px 0px;}");

}

void HiPlayer::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
        return;

    QStringList dropfilename;
    foreach(QUrl u, urls){
        if (u.toString().right(4) == QString(".mp3")){
            dropfilename.append(u.toLocalFile());
        }
    }

    if(!dropfilename.isEmpty()){
        hi_addList(dropfilename);
    }
    qDebug()<<"HiPlayer::dropEvent";
}

void HiPlayer::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

void HiPlayer::paintEvent(QPaintEvent * event)
{
    QPainter p(this);
    p.drawPixmap(0, 0 , QPixmap(":/hiplayer/resources/background.png"));
    logoButton->raise();
    picLabel->raise();
    playSlider->raise();
    timeLabel->raise();
    playlistTable->raise();
    addButton->raise();
    modeButton->raise();
    nextButton->raise();
    lyricButton->raise();
    playButton->raise();
    volButton->raise();
    mminButton->raise();
    minButton->raise();
    exitButton->raise();
    QWidget::paintEvent(event);
}

void HiPlayer::slotPlaylistDoubleClicked(int row, int )//双击本地歌单列表
{
    QFile file(playList.at(row));
    if (!file.open(QIODevice::ReadOnly)) {
        playlistTable->item(row,1)->setText(QString::fromUtf8("失效"));
        return;
    }
    file.close();
    mediaList->setCurrentIndex(row);
    mediaPlayer->play();
    playlistTable->item(row, 1)->setText(QString::fromUtf8(""));
}

void HiPlayer::slotRemoveCurrentMusic()
{//清除当前音乐后更新本地用于记录列表的数据文件
    playList.removeAt(currentIndex);
    playlistTable->removeRow(currentIndex);
    mediaList->removeMedia(currentIndex);
    hi_setTableColor();
    slotWriteList();
}

void HiPlayer::slotOpenMusic()//打开音乐菜单
{
    QStringList fileList = QFileDialog::getOpenFileNames(this,QString::fromUtf8("添加音乐"),QString(),QString("MP3 (*.mp3)"));
    hi_addList(fileList);
}

void HiPlayer::slotOpenDir()//打开目录菜单
{
    QString dirPath = QFileDialog::getExistingDirectory(this,QString::fromUtf8("选择目录"));
    if(dirPath.size() == 0)
        return;
    //if(QFileDialog::Reject) return;
    QDir dir(dirPath);
    QStringList fileList = dir.entryList(QStringList()<<"*.mp3",QDir::Files);
    for(int i = 0;i < fileList.size();i ++)
        fileList[i] = dir.absoluteFilePath(fileList.at(i));
    hi_addList(fileList);
}

void HiPlayer::slotClearList()
{
    mediaPlayer->stop();
    playList.clear();
    mediaList->clear();
    while(playlistTable->rowCount())
        playlistTable->removeRow(0);

    timeLabel->setText(tr("00:00"));
    nameLabel->setText(tr("Name " ));
    nameLabel->hi_stop();
    musicianLabel->setText(tr("Musician" ));
    albumLabel->setText(tr("Album" ));
}

void HiPlayer::hi_addList(QStringList list)//将文件列表list添加到界面列表上,并更新数据文件
{
    foreach(QString fileName,list)
    {
        if(playList.contains(fileName))//默认大小写敏感
            continue;
        playList.append(fileName);

        mediaList->addMedia(QUrl::fromLocalFile(fileName));
        playlistTable->insertRow(playlistTable->rowCount());//playlistTable行号包括0

        for(int i = 0;i < playlistTable->columnCount();i++){
            QTableWidgetItem *item  = new QTableWidgetItem;
            item->setFont(QFont(QString::fromUtf8("微软雅黑"), 10));

            playlistTable->setItem(playlistTable->rowCount() - 1,i,item);

        }
        playlistTable->item(playlistTable->rowCount() - 1,0)->setText(QFileInfo(fileName).baseName());
    }
    hi_setTableColor();
    slotWriteList();
}

void HiPlayer::slotPlaylistMenuRequested(const QPoint &pos)//请求右键菜单
{
    if(playlistTable->itemAt(pos))
    {
        currentIndex = playlistTable->rowAt(pos.y());
        contextMenuMore->exec(QCursor::pos());
    }
    else contextMenuLess->exec(QCursor::pos());
}

void HiPlayer::slotSetPosition()//更新播放进度
{
    int pos = slotGetPlayPosition();
    //int state = mediaPlayer->state();
    /*	if (qAbs(mediaPlayer->position() - pos) > 99)*/
    mediaPlayer->setPosition(pos);
    mediaPlayer->play();
    playButton->setVisible(false);
    pauseButton->setVisible(true);
    // 	if (state == QMediaPlayer::PlayingState)
    // 		mediaPlayer->play();
    // 	else
    // 		mediaPlayer->pause();
}

void HiPlayer::slotUpdatePosition(qint64 position)//更新歌词、时间显示
{
    if (!playSlider->isSliderDown()){//判断slider未被按下.
        playSlider->setValue(position);
    }

    //获取该音频文件的总时长参数，单位为毫秒
    qint64 total_time_value = mediaPlayer->duration();

    //这3个参数分别代表了时，分，秒；60000毫秒为1分钟，所以分钟第二个参数是先除6000,第3个参数是直接除1s
    //QTime total_time(0, (total_time_value/60000)%60, (total_time_value/1000)%60);

    //传进来的time参数代表了当前的时间
    QTime current_time(0, (position/60000)%60, (position/1000)%60);
    timeLabel->setText(current_time.toString(tr("mm:ss")));

    // 获取当期时间对应的歌词
    if(!lrcMap.isEmpty()) //QMap<qint64, QString> lrcMap;
    {
        // 获取当前时间在歌词中的前后两个时间点
        qint64 previous = 0;
        qint64 later = 0;

        //keys()方法返回lrcMap的keys列表
        foreach (qint64 value1, lrcMap.keys()) {//QMap<qint64, QString> lrcMap;
            if (position >= value1) {
                previous = value1;
            } else {
                later = value1;
                break;//获取该位置所在的歌词的前后时间点.
            }
        }

        // 到达最后一行,将later设置为歌曲总时间的值
        if (later == 0)
            later = total_time_value;

        // 获取当前时间所对应的歌词内容
        QString current_lrc = lrcMap.value(previous);

        // 如果是新的一行歌词，那么重新开始显示歌词遮罩
        QString tmp = lrcWidget->text();
        if(current_lrc != tmp)
        {
            lrcWidget->setText(current_lrc);
            tmp = lrcWidget->text();
            qint64 interval_time = later - previous;
            lrcWidget->hi_startLrcMask(interval_time);
        }
    }
}

void HiPlayer::slotUpdateProcessbar(qint64 duration)
{
    playSlider->setRange(0, duration);
    playSlider->setEnabled(duration > 0);
    playSlider->setPageStep(duration / 10);
}

void HiPlayer::slotUpdateMetaData()//更新显示在界面上的正在播放音乐的信息
{
    currentIndex = mediaList->currentIndex();
    qDebug()<<"slotUpdateMetaData()-->mediaList->currentIndex():"<<currentIndex;
    if(currentIndex>=0)//单曲播放模式下,歌曲播放结束之后mediaList->currentIndex()返回-1
    {
        playingFile = playList.at(currentIndex);
    }
    qDebug()<<"slotUpdateMetaData()-->playingFile="<<playingFile;

    songName.clear();
    songArtist.clear();
    lrcMap.clear();
    picLabel->setPixmap(QPixmap(":/hiplayer/resources/album.png"));


    songName = mediaPlayer->metaData(QMediaMetaData::Title).toString();//通过歌曲文件获取歌名
    if (songName.size() > 28)
        nameLabel->hi_setText(songName, TEXT_SPEED);
    else{
        nameLabel->hi_stop();
        nameLabel->setText(songName);
    }

    songArtist = mediaPlayer->metaData(QMediaMetaData::Author).toString();
    musicianLabel->setText(songArtist);
    albumLabel->setText(mediaPlayer->metaData(QMediaMetaData::AlbumTitle).toString());

    lrcWidget->setText(songName);

    if (!songName.isEmpty()){//若歌曲名不为空,则搜索图片和歌词
        bool pic = hi_getPicFromFile();
        bool lrc = slotResolveLrc(playingFile);
        if (!(pic && lrc)){//本地均没有找到专辑图片和歌词
            receiveState = RECEIVE_INFO;
            hi_fetchNetData();
        }
    }

    if(nameLabel->text() == "")
        nameLabel->setText(QString::fromUtf8("未知歌曲"));
    if(musicianLabel->text() == "")
        musicianLabel->setText(QString::fromUtf8("未知音乐家"));
    if(albumLabel->text() == "")
        albumLabel->setText(QString::fromUtf8("未知专辑"));

//貌似永远不会执行
//    if(playlistTable->rowCount() == 0)
//    {
//        timeLabel->setText(tr("00:00"));
//        nameLabel->setText(tr("Name " ));
//        musicianLabel->setText(tr("Musician" ));
//        albumLabel->setText(tr("Album" ));
//    }
}

void HiPlayer::slotUpdateState(QMediaPlayer::State state)//更新播放状态
{
    if (state == QMediaPlayer::PlayingState) {
        playButton->setVisible(false);
        pauseButton->setVisible(true);
    } else {
        playButton->setVisible(true);
        pauseButton->setVisible(false);
    }
    if (state != QMediaPlayer::StoppedState){
        playingFile = playList.at(mediaList->currentIndex());
        slotResolveLrc(playingFile);
    }
}

void HiPlayer::slotSliderValueClicked(int value)
{
    qDebug()<<"slotSliderValueClicked(int)";
    slotSetPlayPosition(value);
    slotSetPosition();
}

void HiPlayer::slotPlayButtonClicked()
{
    if(mediaPlayer->state() == QMediaPlayer::PausedState){
        mediaPlayer->play();
    }
}

void HiPlayer::slotPauseButtonClicked()
{

    if(mediaPlayer->state() == QMediaPlayer::PlayingState){
        mediaPlayer->pause();
    }
}

void HiPlayer::slotNextButtonClicked()//点击播放下一首按钮
{
    mediaList->setPlaybackMode(QMediaPlaylist::Loop);

    //TODO:注释掉下列代码之后不影响功能
    //    if (mediaList->currentIndex() != mediaList->nextIndex())
    //        mediaList->setCurrentIndex(mediaList->nextIndex());
    //    else if (mediaList->currentIndex() != mediaList->previousIndex())
    //        mediaList->setCurrentIndex(mediaList->previousIndex());

    mediaList->setCurrentIndex(mediaList->nextIndex());
    if (!mediaPlayer->isAudioAvailable()){
        playlistTable->item(mediaList->currentIndex(), 1)->setText(QString::fromUtf8("失效"));
    }
    mediaPlayer->play();
    playlistTable->item(mediaList->currentIndex(), 1)->setText(QString::fromUtf8(""));
    //playingFile:TODO
    slotSetPlayMode();
}

void HiPlayer::slotLastButtonClicked()//单击下一首按钮
{
    mediaList->setPlaybackMode(QMediaPlaylist::Loop);
    //TODO:注释掉下列代码之后不影响功能
    //qDebug()<<"mediaList->currentIndex()="<<mediaList->currentIndex();
    //    if(mediaList->currentIndex() != mediaList->previousIndex())
    //        mediaList->setCurrentIndex(mediaList->previousIndex());
    //    else
    //        mediaList->setCurrentIndex(mediaList->nextIndex());

    mediaList->setCurrentIndex(mediaList->previousIndex());
    if (!mediaPlayer->isAudioAvailable()){
        playlistTable->item(mediaList->currentIndex(), 1)->setText(QString::fromUtf8("失效"));
    }

    mediaPlayer->play();
    playlistTable->item(mediaList->currentIndex(), 1)->setText(QString::fromUtf8(""));
    slotSetPlayMode();
}

void HiPlayer::slotLyricButtonClicked()
{
    if(lrcWidget->isHidden())
        lrcWidget->show();
    else lrcWidget->hide();
}

void HiPlayer::slotLogoButtonClicked()
{
    aboutForm->show();
}

void HiPlayer::slotModeButtonClicked()
{
    playModeMenu->exec(QCursor::pos());
}

void HiPlayer::slotMinButtonClicked()
{
    miniForm->show();
    miniForm->hi_initPlayMode(volButton->hi_getVolume());
    this->hide();
}

void HiPlayer::slotSetPlayMode()
{
    if(modeSingal->isChecked()) {
        playMode = Play_Mode::SINGAL;
        mediaList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    }
    else if(modeListCircle->isChecked()) {
        playMode = Play_Mode::LISTCIRCLE;
        mediaList->setPlaybackMode(QMediaPlaylist::Loop);
    }
    else if(modeSingalCircle->isChecked()) {
        playMode = Play_Mode::SINGALCIRCLE;
        mediaList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }
    else if(modeRandom->isChecked()) {
        playMode = Play_Mode::RANDOM;
        mediaList->setPlaybackMode(QMediaPlaylist::Random);
    }
    qDebug()<<"playMode="<<playMode;
}

void HiPlayer::slotSetModeFromMini(int m)
{
    switch(m){
    case 0:
        playMode = Play_Mode::SINGAL;
        mediaList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        modeSingal->setChecked(true);
        break;
    case 1:
        playMode = Play_Mode::LISTCIRCLE;
        mediaList->setPlaybackMode(QMediaPlaylist::Loop);
        modeListCircle->setChecked(true);
        break;
    case 2:
        playMode = Play_Mode::SINGALCIRCLE;
        mediaList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        modeSingalCircle->setChecked(true);
        break;
    case 3:
        playMode = Play_Mode::RANDOM;
        mediaList->setPlaybackMode(QMediaPlaylist::Random);
        modeRandom->setChecked(true);
        break;

    }
}

bool HiPlayer::slotResolveLrc(const QString & source_file_name)//TODO:根据歌曲文件名解析LRC歌词
{
    lrcMap.clear();
    if(source_file_name.isEmpty())
        return false;
    QString file_name = source_file_name;
    QString lrc_file_name = file_name.remove(file_name.right(3)) + "lrc";//把音频文件的后缀改成lrc后缀

    // 打开歌词文件
    QFile file(lrc_file_name);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QByteArray temp = file.readAll();
    QByteArray hehe;
    for (int i = 0; i < temp.size(); i++)
    {
        if (temp.at(i) != 0)
            hehe.append(temp.at(i));
    }

    QString all_text;
    all_text = QString::fromUtf8(hehe);

    file.close();
    // 将歌词按行分解为歌词列表
    QStringList lines = all_text.split("\n");

    //这个是时间标签的格式[00:05.54]----[mm:ss.ff](分钟数:秒数.百分之一秒数  )
    //正则表达式\d{2}表示匹配2个数字
    QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");//实际的正则表达式为\[\d{2}:\d{2}\.\d{2}\]
    foreach(QString oneline, lines)
    {
        QString temp = oneline;
        temp.replace(rx, "");//用空字符串替换正则表达式中所匹配的地方,这样就获得了歌词文本
        // 然后依次获取当前行中的所有时间标签，并分别与歌词文本存入QMap中
        //indexIn()为返回第一个匹配的位置，如果返回为-1，则表示没有匹配成功
        //正常情况下pos后面应该对应的是歌词文件
        int pos = rx.indexIn(oneline, 0);
        while (pos != -1)
        { //表示匹配成功
            QString cap = rx.cap(0);//返回第0个表达式匹配的内容,即全部匹配内容,如[00:05.54]
            // 将时间标签转换为时间数值，以毫秒为单位
            QRegExp regexp;
            regexp.setPattern("\\d{2}(?=:)");//获取:前面的两个数字
            regexp.indexIn(cap);
            int minute = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\.)");
            regexp.indexIn(cap);
            int second = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\])");
            regexp.indexIn(cap);
            int millisecond = regexp.cap(0).toInt();
            qint64 totalTime = minute * 60000 + second * 1000 + millisecond * 10;//totalTime以毫秒为单位
            // 插入到lrc_map中
            lrcMap.insert(totalTime, temp);
            pos += rx.matchedLength();
            pos = rx.indexIn(oneline, pos);//匹配全部
        }
    }
    // 如果lrc_map为空
    if (lrcMap.isEmpty())
    {
        lrcWidget->setText(mediaPlayer->metaData(QMediaMetaData::Title).toString());
        return false;
    }

    return true;
}

void HiPlayer::slotReturnToMainwidget()
{
    this->show();
}

void HiPlayer::slotSetVolFromMini(int a)
{
    volButton->hi_setVolume(a);
}

void HiPlayer::slotReadList()
{
    QFile text(dirPath + "/HiPlayerList.list");
    QStringList inList;

    if(text.open(QIODevice::ReadOnly)){
        QDataStream in(&text);
        in.setVersion(QDataStream::Qt_5_8);
        in >> inList;
        hi_addList(inList);
        text.close();
    }else
    {
        qDebug()<<"list file open error:"<<text.errorString();
    }

}

void HiPlayer::slotWriteList()//将playList中的内容写入本地数据文件
{
    QFile text(dirPath + "/HiPlayerList.list");
    QStringList outList = playList;

    if (text.open(QIODevice::WriteOnly)){
        QDataStream out(&text);
        out.setVersion(QDataStream::Qt_5_8);
        out << outList;
        text.close();
    }
    else
    {
        qDebug()<<"list file open error:"<<text.errorString();
    }
}

void HiPlayer::hi_openMusic(const QString& filePath)
{
    QStringList name;
    name.append(filePath);

    hi_addList(name);

    if (playList.contains(filePath)){
        mediaList->setCurrentIndex(playList.indexOf(filePath));
        mediaPlayer->play();
    }
}

void HiPlayer::hi_setTableColor()//设置列表颜色交替
{
    for (int i = 0; i < playlistTable->rowCount(); i++)
    {

        if (i % 2 == 0){
            for (int j = 0; j < playlistTable->columnCount(); j++){
                QTableWidgetItem *item = playlistTable->item(i, j);
                if (item){
                    const QColor color = QColor(255, 255, 255);
                    item->setBackgroundColor(color);//设置深色背景
                }
            }
        }
        else{
            for (int j = 0; j < playlistTable->columnCount(); j++)
            {
                QTableWidgetItem *item = playlistTable->item(i, j);
                if (item){
                    const QColor color = QColor(213, 228, 242);
                    item->setBackgroundColor(color);//设置白色背景
                }
            }
        }
    }
}

void HiPlayer::hi_initNetwork()//初始化网络模块
{
    networker = NetWorker::getInstance();
    receiveState = RECEIVE_INFO;
    /*
    1.[var]表示值传递方式捕捉变量var；
    2.[=]表示值传递方式捕捉所有父作用域的变量（包括this）；
    3.[&var]表示引用传递捕捉变量var；
    4.[&]表示引用传递方式捕捉所有父作用域的变量（包括this）；
    5.[this]表示值传递方式捕捉当前的this指针。
            */
    connect(networker, &NetWorker::finished, [&](QNetworkReply *reply) {
        switch (receiveState){
        case RECEIVE_INFO:
            hi_recvInfo(reply);
            hi_fetchNetData();
            break;
        case RECEIVE_LINK:
            hi_recvLink(reply);
            hi_fetchNetData();
            break;
        case RECEIVE_PIC:
            hi_recvPic(reply);
            hi_fetchNetData();
            break;
        case RECEIVE_LRC:
            hi_recvLrc(reply);
            receiveState = RECEIVE_INFO;
            break;
        default:
            break;
        }

        //buggy there!!
        //这里应该删除上次的reply
        //reply->deleteLater();
        reply->abort();
    });
}

void HiPlayer::hi_fetchNetData()   //TODO:获取网络数据
{
    QString query = QUrl::toPercentEncoding(songName + " " + songArtist);
    switch (receiveState){
    case RECEIVE_INFO:
        networker->get(
                    QString("http://tingapi.ting.baidu.com/v1/restserver/ting?from=webapp_music&method=baidu.ting.search.catalogSug&format=json&callback=&query=" +
                            query +
                            "&_=1413017198449")
                    );
        break;
    case RECEIVE_LINK:
        networker->get(QString("http://ting.baidu.com/data/music/links?songIds=" + songId));
        break;
    case RECEIVE_PIC:
        networker->get(picUrl);
        break;
    case RECEIVE_LRC:
        lrcUrl = QString("http://qukufile2.qianqian.com") + lrcUrl;
        networker->get(lrcUrl);
        break;
    default:
        break;
    }
}

void HiPlayer::hi_recvInfo(QNetworkReply *reply)//接收歌曲信息
{
    QJsonParseError Jsonerror;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll(), &Jsonerror);
    if (Jsonerror.error == QJsonParseError::NoError)
    {
        if (!(jsonDocument.isNull() || jsonDocument.isEmpty()) && jsonDocument.isObject())
        {
            //QVariantMap----QMap<QString, QVariant>
            QVariantMap data = jsonDocument.toVariant().toMap();
            SongInfo song;
            song.set_order(data[QLatin1String("order")].toString());
            song.set_error_code(data[QLatin1String("error_code")].toString());

            //QVariantList----QList<QVariant>
            QVariantList result_list = data[QLatin1String("song")].toList();
            QVariantList album_list = data[QLatin1String("album")].toList();

            if (result_list.size() == 0){
                return;
            }

            QList<SongResult *> results;
            foreach(QVariant s, result_list){
                QVariantMap sm = s.toMap();
                SongResult *result = new SongResult;
                result->set_songid(sm[QLatin1String("songid")].toString());
                result->set_songname(sm[QLatin1String("songname")].toString());
                result->set_has_mv(sm[QLatin1String("has_mv")].toInt());
                result->set_yyr_artist(sm[QLatin1String("yyr_artist")].toInt());
                result->set_artistname(sm[QLatin1String("artistname")].toString());
                results.append(result);
            }
            song.set_song_results(results);

            QList<AlbumInfo *> album_infos;
            foreach(QVariant a, album_list)
            {
                QVariantMap ai = a.toMap();
                AlbumInfo *info = new AlbumInfo;
                info->set_albumid(ai[QLatin1String("albumid")].toString());
                info->set_albumname(ai[QLatin1String("albumname")].toString());
                info->set_artistname(ai[QLatin1String("artistname")].toString());
                info->set_artistpic(ai[QLatin1String("artistpic")].toString());
                album_infos.append(info);
            }
            song.set_album_infos(album_infos);

            if (results.count() > 0){
                SongResult *temp = new SongResult;
                temp = results[0];

                songId = temp->get_songid();
            }
            receiveState = RECEIVE_LINK;
        }
    }
    reply->deleteLater();
}

void HiPlayer::hi_recvLink(QNetworkReply *reply)//接收歌词地址
{
    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll(), &error);
    if (error.error == QJsonParseError::NoError) {
        if (!(jsonDocument.isNull() || jsonDocument.isEmpty()) && jsonDocument.isObject()) {
            QVariantMap data = jsonDocument.toVariant().toMap();

            SongLink link;
            link.set_errorcode(data[QLatin1String("errorCode")].toString());

            QVariantMap song_data_map = data[QLatin1String("data")].toMap();

            SongData sdata;
            sdata.set_xcode(song_data_map[QLatin1String("xcode")].toString());

            QList<QVariant> slist = song_data_map[QLatin1String("songList")].toList();
            QList<SongList *> slists;
            foreach(QVariant s, slist)
            {
                QVariantMap sl = s.toMap();
                SongList *list = new SongList;
                list->set_songpic_radio(sl[QLatin1String("songPicRadio")].toString());
                list->set_lrclink(sl[QLatin1String("lrcLink")].toString());
                slists.append(list);
            }
            sdata.set_song_lists(slists);
            link.set_song_data(sdata);

            SongData temp2 = link.get_song_data();
            QList<SongList *> temp3 = temp2.get_song_lists();
            if (temp3.count() > 0){
                SongList *templist = temp3[0];

                picUrl = templist->get_songpic_radio();
                lrcUrl = templist->get_lrclick();
            }
            receiveState = RECEIVE_PIC;
        }
    }
    reply->deleteLater();
}

void HiPlayer::hi_recvLrc(QNetworkReply *reply)//TODO
{
    if (reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();
        QString fileName;

        QString temp = playingFile;
        fileName = temp.remove(temp.right(3)) + "lrc";

        QFile *file = new QFile(fileName);
        if (!file->open(QIODevice::WriteOnly)) {
            delete file;
            file = 0;
            return;
        }

        QDataStream out(file);
        out << data;
        file->close();
        delete file;
        file = 0;


    }
    reply->deleteLater();

    slotResolveLrc(playingFile);
}

void HiPlayer::hi_recvPic(QNetworkReply *reply)//TODO
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        if (data.size() < 50){
            receiveState = RECEIVE_LRC;
            return;
        }
        QPixmap currentPicture;

        if (currentPicture.loadFromData(data)){
            picLabel->setPixmap(currentPicture);
        }

        receiveState = RECEIVE_LRC;

        QString fileName;
        QString temp = playingFile;
        fileName = temp.remove(temp.right(3)) + "jpg";

        QFile *file = new QFile(fileName);
        if (!file->open(QIODevice::WriteOnly)) {
            delete file;
            file = 0;
            return;
        }

        QImage image;
        QBuffer buffer(&data);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "JPG");//把图片以流方式写入文件缓存流中
        file->write(data);
        file->close();
        delete file;
        file = 0;
    }
    reply->deleteLater();
}

bool HiPlayer::hi_getPicFromFile() //TODO:从磁盘中读取专辑图片
{
    if (playingFile.isEmpty())
        return false;
    QString file_name = playingFile;
    QString pic_file_name = file_name.remove(file_name.right(3)) + "jpg";//把音频文件的后缀改成jpg后缀

    // 打开图片文件
    QFile file(pic_file_name);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    QByteArray temp = file.readAll();
    QPixmap currentPicture;

    if (currentPicture.loadFromData(temp))
    {
        picLabel->setPixmap(currentPicture);
    }
    file.close();
    return true;
}

void HiPlayer::slotClose()
{
    slotWriteList();

    SAFE_RELEASE(lrcWidget);

    SAFE_RELEASE(minButton);
    SAFE_RELEASE(exitButton);
    SAFE_RELEASE(addButton);
    SAFE_RELEASE(lyricButton);
    SAFE_RELEASE(lastButton);
    SAFE_RELEASE(nextButton);
    SAFE_RELEASE(playButton);
    SAFE_RELEASE(pauseButton);
    SAFE_RELEASE(modeButton);
    SAFE_RELEASE(mminButton);
    SAFE_RELEASE(logoButton);

    SAFE_RELEASE(nameLabel);
    SAFE_RELEASE(musicianLabel);
    SAFE_RELEASE(albumLabel);
    SAFE_RELEASE(timeLabel);
    SAFE_RELEASE(picLabel);

    SAFE_RELEASE(playSlider);

    SAFE_RELEASE(playlistTable);
    SAFE_RELEASE(mediaPlayer);
    SAFE_RELEASE(mediaList);
    SAFE_RELEASE(contextMenuLess);
    SAFE_RELEASE(contextMenuMore);

    SAFE_RELEASE(modeSingal);
    SAFE_RELEASE(modeListCircle);
    SAFE_RELEASE(modeSingalCircle);
    SAFE_RELEASE(modeRandom);
    SAFE_RELEASE(addMusic);
    SAFE_RELEASE(addFileDiv);
    SAFE_RELEASE(removeCurr);
    SAFE_RELEASE(removeAll);
    SAFE_RELEASE(modeActionGroup);

    SAFE_RELEASE(volButton);
    SAFE_RELEASE(miniForm);
    SAFE_RELEASE(aboutForm);

}

void HiPlayer::slotSetPlayPosition(int pos)
{
    playPosition = pos;
}

//void HiPlayer::slotPlayValueChanged(int i)
//{
//    qDebug()<<"palyer value:"<<i;
//}

int HiPlayer::slotGetPlayPosition()
{
    return playPosition;
}

void HiPlayer::mousePressEvent(QMouseEvent *event)
{
    m_Moveing=true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于父窗口的位置
    m_MovePosition=event->globalPos() - pos();
    //event->accept();
    return QWidget::mousePressEvent(event);
}

void HiPlayer::mouseMoveEvent(QMouseEvent *event)
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
    //event->accept();
}

void HiPlayer::mouseReleaseEvent(QMouseEvent *)
{
    m_Moveing=false;
}

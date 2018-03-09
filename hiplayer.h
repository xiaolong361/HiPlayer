#ifndef HIPLAYER_H
#define HIPLAYER_H


//文字滚动速度
#define TEXT_SPEED 500

//安全回收内存
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) if(p) { delete p; p = NULL;}
#endif //SAFE_RELEASE

#include "hiLrcWidget.h"
#include "hiButton.h"
#include "aboutDialog.h"
#include "hiVolBotton.h"
#include "hiLabel.h"
#include "nofocusdelegate.h"
#include "network.h"
#include "songinfo.h"
#include "playslider.h"

#include <QString>
#include <QVector>
#include <QMap>
#include <QtWidgets>
#include <QMediaPlaylist>
#include <QMediaMetaData>
#include <QMediaPlayer>
#include <QJsonDocument>
#include <QTextCodec>
#include <QFileInfo>
#include <QCloseEvent>
#include <qDebug>

//枚举播放模式
enum Play_Mode{SINGAL, LISTCIRCLE, SINGALCIRCLE, RANDOM};

//网络音乐信息，专辑图片，歌词获取状态
//网络歌词、专辑图片获取（保存在歌曲目录下，文件名与歌曲同名）
enum { RECEIVE_INFO, RECEIVE_LINK, RECEIVE_PIC, RECEIVE_LRC };

class MiniWindow;

class HiPlayer : public QWidget
{
    //设置mini窗口类为主窗口类的友元类，从而可以调用主窗口类的私有函数和私有对象
    friend class MiniWindow;

    Q_OBJECT

public:
    explicit HiPlayer(QWidget *parent = 0);
    ~HiPlayer();

    //通过命令行打开指定音乐文件
    void hi_openMusic(const QString& filePath);

public slots:

    //接受mini窗口传来的参数设置播放模式
    void slotSetModeFromMini(int mode);

    //接受mini窗口传来的参数设置音量
    void slotSetVolFromMini(int val);

public slots:

    //访问目录结构
    void slotOpenDir();

    //添加mp3格式的文件
    void slotOpenMusic();

    //删除指定行的歌曲
    void slotRemoveCurrentMusic();

    //清空播放列表
    void slotClearList();

    //请求右键菜单
    void slotPlaylistMenuRequested(const QPoint &pos);

    //双击播放歌曲
    void slotPlaylistDoubleClicked(int row, int);

    //更新音乐信息
    void slotUpdateMetaData();

    //更新进度条
    void slotUpdateProcessbar(qint64 duration);

    //更新播放状态
    void slotUpdateState(QMediaPlayer::State state);

    //更新播放进度
    void slotSetPosition(/*int position*/);

    //更新歌词、时间显示
    void slotUpdatePosition(qint64 position);

    //设置各按钮的单击事件，激活各按钮
    void slotPlayButtonClicked();
    void slotLyricButtonClicked();
    void slotLogoButtonClicked();
    void slotModeButtonClicked();
    void slotPauseButtonClicked();
    void slotMinButtonClicked();
    void slotNextButtonClicked();
    void slotLastButtonClicked();

    //设置播放模式
    void slotSetPlayMode();

    //解析LRC歌词
    bool slotResolveLrc(const QString &source_file_name);

    //程序打开时读取播放列表文件
    void slotReadList();

    //把现有播放列表写入列表文件
    void slotWriteList();

    //设置当前播放位置
    void slotSetPlayPosition(int pos);

    //获取当前播放位置
    int slotGetPlayPosition();

    //处理鼠标点击PlaySlider的信号
    void slotSliderValueClicked(int value);
protected:
     void closeEvent(QCloseEvent *event);  //窗口关闭之前需要的操作

private:
    //绘制窗体(也用于窗口位置拖动)
    void paintEvent(QPaintEvent *event);

    //拖拽添加,拖拽加歌现在可以一次性添加多首，且可以自动识别文件类型，只添加mp3文件 .
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

    //用于窗口位置拖动
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    //初始化主界面
    void hi_initUi();

    //初始化播放模块
    void hi_initPlayer();

    //初始化信号-槽连接
    void hi_initConnections();

    //初始化窗口
    void hi_initWindows();

    //初始化菜单项
    void hi_initMenuActions();

    //添加到播放列表
    void hi_addList(QStringList list);

    //定制tablewidget外观
    void hi_setTableColor();

    //初始化网络模块
    void hi_initNetwork();

    //获取网络数据
    void hi_fetchNetData();

    //接收专辑图片
    void hi_recvPic(QNetworkReply *reply);

    //接收歌曲信息
    void hi_recvInfo(QNetworkReply *reply);

    //接收网络歌词
    void hi_recvLrc(QNetworkReply *reply);

    //接收歌词地址
    void hi_recvLink(QNetworkReply *reply);

    //从磁盘中读取专辑图片
    bool hi_getPicFromFile();
private:
    HiLrcWidget *lrcWidget;
    QMap<qint64, QString> lrcMap;

    QStringList playList;
    QString playingFile;
    QString dirPath;

    HiButton *miniButton;
    HiButton *exitButton;
    HiButton *addButton;
    HiButton *lyricButton;
    HiButton *lastButton;
    HiButton *nextButton;
    HiButton *playButton;
    HiButton *pauseButton;
    HiButton *modeButton;
    HiButton *minButton;
    HiButton *logoButton;

    HiLabel *nameLabel;
    QLabel *musicianLabel;
    QLabel *albumLabel;
    QLabel *timeLabel;
    QLabel *picLabel;

    PlaySlider *playSlider;
   // QSlider *volSlider;

    QTableWidget *playlistTable;

    QMediaPlayer *mediaPlayer;
    QMediaPlaylist *mediaList;

    QMenu *contextMenuLess;
    QMenu *contextMenuMore;
    QMenu *playModeMenu;

    QActionGroup *modeActionGroup;

    //enum ICE_Play_Mode{SINGAL, LISTCIRCLE, SINGALCIRCLE, RANDOM};
    QAction *modeSingal;
    QAction *modeListCircle;
    QAction *modeSingalCircle;
    QAction *modeRandom;
    QAction *addMusic;
    QAction *addFileDiv;
    QAction *removeCurr;
    QAction *removeAll;

    HiVolBotton *volButton;

    MiniWindow * miniForm;
    AboutDialog *aboutForm;

    NetWorker * networker;
    QString songName;
    QString songArtist;
    QString songId;
    QString picUrl;
    QString lrcUrl;

    //int preIndex;//未使用
    int currentIndex;//当前播放歌曲在列表中的index
    int playMode;//当前播放模式

    int receiveState;//接收状态
    int playPosition;//当前歌曲播放位置

    //用于窗口位置拖动
    bool        m_Moveing;
    QPoint      m_MovePosition;
};

#endif // HIPLAYER_H

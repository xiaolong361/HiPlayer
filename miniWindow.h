#ifndef MINIWINDOW_H
#define MINIWINDOW_H

#include <QtWidgets>
#include "hiButton.h"
//#include "hiplayer.h"

class HiPlayer;

class MiniWindow : public QWidget
{
    Q_OBJECT
public:
    MiniWindow(HiPlayer * hiplayer,QWidget *parent = 0);
    ~MiniWindow();

    void hi_initPlayMode(int vol);


private slots:
    void slotBackToMain();

    void slotNextMusic();

    void slotLastMusic();

    void slotPlay();

    void slotPause();

    void slotSetMode();

    void slotExit();

    void slotLyricAction();

    void slotUpdateVol(int);
private:
    void paintEvent(QPaintEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

    void hi_initMenuActions();

    //用于窗口位置拖动
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    HiButton *miniPlayButton;
    HiButton *miniPauseButton;
    HiButton *miniNextButton;
    HiButton *miniLastButton;
    HiButton *miniMaxButton;

    QMenu *contextMenu;
    QActionGroup *modeGroup;
    QAction *mode0;
    QAction *mode1;
    QAction *mode2;
    QAction *mode3;
    QAction *mainForm;
    QAction *next;
    QAction *last;
    QAction *lyric;
    QAction *exit;

    QWidgetAction *setVolumn;
    QSlider *volSlider;

    HiPlayer *mainWindow;

    //用于窗口位置拖动
    bool        m_Moveing;
    QPoint      m_MovePosition;

};
#endif // MINIWINDOW_H

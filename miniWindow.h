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
    MiniWindow(QWidget *parent = 0);
    ~MiniWindow();

    void hi_setParent(HiPlayer *parent);
    void hi_initPlayMode(int vol);

signals:
    void volumeChanged(int);
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

    HiButton *playButton;
    HiButton *pauseButton;
    HiButton *miniNextButton;

    QMenu *contextMenu;
    QActionGroup *modeGroup;

    QAction *mode0;
    QAction *mode1;
    QAction *mode2;
    QAction *mode3;
    QAction *mainForm;
    QAction *exit;
    QAction *next;
    QAction *last;
    QAction *lyric;
    QWidgetAction *setVolumn;
    QSlider *volSlider;

    HiPlayer *parentForm;

};
#endif // MINIWINDOW_H

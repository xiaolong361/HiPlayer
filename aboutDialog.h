#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QMouseEvent>

class HiButton;

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    AboutDialog(QWidget *parent = 0);
    ~AboutDialog();


protected:
    void paintEvent(QPaintEvent *event); //用窗口绘制事件来绘制背景图片

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:

private:
    HiButton *  m_exitButton;
    bool        m_Moveing;
    QPoint      m_MovePosition;

};


#endif

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "hiButton.h"

class Widget : public QWidget
{
    Q_OBJECT

public slots:
    void slotVolChange(int vol);
    void slotRecvMessage(QString message);
public:
    Widget(QWidget *parent = 0);
    ~Widget();

    HiButton * hiButton;
};

#endif // WIDGET_H

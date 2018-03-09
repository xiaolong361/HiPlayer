#include "widget.h"
#include "aboutDialog.h"
#include "hiLrcWidget.h"
#include <QApplication>
#include <QMessageBox>
#include "singleApp.h"
#include "miniWindow.h"
#include "hiplayer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    HiLrcWidget * lrc=new HiLrcWidget;
//    QString str="问君此去几时还,来时莫徘徊";
//    lrc->hi_setLyricText(str);
//    //lrc.hi_startLrcMask(1000);
//    lrc->show();

    qDebug()<<"hello";
    HiPlayer hi;
    //MiniWindow w(&hi);
    hi.show();
    //AboutDialog about;
    //about.show();
//    QDialog d;
//    d.setWindowTitle("hello");
//    d.setWindowFlags(Qt::FramelessWindowHint);
//    d.show();

    return a.exec();
}




//int main(int argc, char *argv[])
//{
//    SingleApp app(argc, argv, "hiplayer");
//    if(app.isRunning())
//    {
////        QMessageBox::warning(NULL
////                             ,QString::fromUtf8("error running")
////                             ,QString::fromUtf8("a program is running!")
////                             );
//        app.sendMessage("call you");
//        return 0;
//    }
//    Widget w;
//    QObject::connect(&app,SIGNAL(sigMsgAvailable(QString)),&w,SLOT(slotRecvMessage(QString)));
//    w.show();

//    return app.exec();
//}

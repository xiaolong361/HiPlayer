#include "widget.h"
#include "aboutDialog.h"
#include "hiLrcWidget.h"
#include <QApplication>
#include <QMessageBox>
#include "singleApp.h"
#include "miniWindow.h"
#include "hiplayer.h"
#include "hiLabel.h"

//测试用代码
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    HiLrcWidget lrc;
//    //HiLabel lrc;
//    QString str="问君此去几时还,来时莫徘徊";
//    lrc.hi_setLyricText(str);
//    lrc.hi_startLrcMask(2000);
//    lrc.show();

//    //lrc.hi_startLrcMask(1000);

//    qDebug()<<"hello";
//    //HiPlayer hi;
//    //MiniWindow w(&hi);
//    //hi.show();
////    QDialog d;
////    d.setWindowTitle("hello");
////    d.setWindowFlags(Qt::FramelessWindowHint);
////    d.show();

//    return a.exec();
//}

int main(int argc, char *argv[])
{
    SingleApp app(argc, argv, "hiplayer");
    if(app.isRunning())
    {
//        QMessageBox::warning(NULL
//                             ,QString::fromUtf8("error running")
//                             ,QString::fromUtf8("a program is running!")
//                             );
        app.sendMessage("The program is running!");
        return 0;
    }
    HiPlayer w;
    QObject::connect(&app,SIGNAL(sigMsgAvailable(QString)),&w,SLOT(slotRecvMessage(QString)));
    w.show();

    return app.exec();
}

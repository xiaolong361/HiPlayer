#include "singleApp.h"
#include "hiplayer.h"

#include <QApplication>

//已添加的歌曲列表记录在文件HiPlayerList.list中

int main(int argc, char *argv[])
{
    SingleApp app(argc, argv, "hiplayer");

    if(app.isRunning())
    {
        app.sendMessage("The program is running!");
        return 0;
    }
    HiPlayer w;
    QObject::connect(&app,SIGNAL(sigMsgAvailable(QString)),&w,SLOT(slotRecvMessage(QString)));
    w.show();

    return app.exec();
}


//#include <QtWidgets/QApplication>
//#include <QFileInfo>
//#include <QSettings>
//#include <QDir>
//#include "singleApp.h"
//#include "hiplayer.h"

////已添加的歌曲列表记录在文件HiPlayerList.list中

//static void associateFileTypes(const QStringList &fileTypes)
//{
//    QString displayName = QGuiApplication::applicationDisplayName();
//    QString filePath = QCoreApplication::applicationFilePath();
//    QString fileName = QFileInfo(filePath).fileName();

//    QSettings settings("HKEY_CURRENT_USER\\Software\\Classes\\Applications\\" + fileName, QSettings::NativeFormat);
//    settings.setValue("FriendlyAppName", displayName);

//    settings.beginGroup("SupportedTypes");
//    foreach(const QString& fileType, fileTypes)
//        settings.setValue(fileType, QString());
//    settings.endGroup();

//    settings.beginGroup("shell");
//    settings.beginGroup("open");
//    settings.setValue("FriendlyAppName", displayName);
//    settings.beginGroup("Command");
//    settings.setValue(".", QChar('"') + QDir::toNativeSeparators(filePath) + QString("\" \"%1\""));
//}

//int main(int argc, char *argv[])
//{
//    QApplication::addLibraryPath("./plugins");
//    //QApplication app(argc, argv);

//    SingleApp app(argc, argv, "hiplayer");

//    associateFileTypes(QStringList(".mp3"));

//    const QStringList arguments = QCoreApplication::arguments();

//    HiPlayer* player = NULL;

//    player = new HiPlayer;

//    if (arguments.size() > 1)
//        player->hi_openMusic(arguments.at(1));

//    player->show();


//    return app.exec();
//}

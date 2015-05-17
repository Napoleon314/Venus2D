#include "AnimationEditor.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication kApp(argc, argv);
    Q_INIT_RESOURCE(AnimationEditor);
    QSplashScreen kSplash(QPixmap("://res/splash.png"));
    kSplash.show();
    kApp.processEvents();
    QTranslator* pkTranslator = new QTranslator;
    pkTranslator->load("://trans/zh_CN.qm");
    kApp.installTranslator(pkTranslator);
    AnimationEditor kEditor;
    kEditor.show();
    kSplash.finish(&kEditor);
    return kApp.exec();
}

#include "window.h"
#include "scouttalker.h"
#include <QApplication>
#include <QFontDatabase>
//#include <QTranslator>
//#include <QLibraryInfo>
//#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Add custom font to the application database
    QFontDatabase::addApplicationFont(":/fonts/chinese-angular.ttf");

//    /* load the system translations provided by Qt */
//    QTranslator qtTranslator;
//    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
//    app.installTranslator(&qtTranslator);

//    /* load our custom translations for this application */
//    QTranslator myappTranslator;
//    myappTranslator.load("app" + QLocale::system().name());
//    app.installTranslator(&myappTranslator);

    Window window;
    window.setWindowIcon(QIcon(":/icons/logo.png"));
    window.show();

    ScoutTalker *sctlk;
    sctlk = new ScoutTalker(&window, NULL);

    return app.exec();
}

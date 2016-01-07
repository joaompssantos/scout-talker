#include "window.h"
#include "scouttalker.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Add custom font to the application database
    QFontDatabase::addApplicationFont(":/fonts/chinese-angular.ttf");

    Window window;
    window.show();

    ScoutTalker *sctlk;
    sctlk = new ScoutTalker(&window, NULL);

    return a.exec();
}

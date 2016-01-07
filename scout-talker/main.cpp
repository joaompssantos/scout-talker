#include "window.h"
#include "scouttalker.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    // Add custom font to the application database
    QFontDatabase::addApplicationFont(":/fonts/Chines&Angular.TTF");

    QApplication a(argc, argv);
    Window window;
    window.show();

    ScoutTalker *sctlk;
    sctlk = new ScoutTalker(&window, NULL);

    return a.exec();
}

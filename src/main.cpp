/* Scout Talker
 * Copyright (C) 2015 - 2017 by Diana Capela
 *                              João  Santos    (joaompssantos@gmail.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

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
    QFontDatabase::addApplicationFont(":chinese-angular.ttf");

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

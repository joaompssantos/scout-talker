/* Scout Talker - Scouting codes, ciphers and encryption program
 * Copyright (C) 2015 - 2018 by Diana Capela
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

#include "MainWindow.h"
#include "ScoutTalkerConfig.h"

#include <QApplication>
#include <QFontDatabase>

//#include <QTranslator>
//#include <QLibraryInfo>
//#include <QLocale>

int main(int argc, char *argv[]) {
    // Declaration of a new application
    QApplication application(argc, argv);
    // Set application name
    QApplication::setApplicationName("Scout Talker");
    // Set application version
    QApplication::setApplicationVersion(SCOUTTALKER_VERSION);
    // Set application organization name
    QApplication::setOrganizationName("Diana Capela & João Santos");

    // Add custom font to the Scout Talker application
    QFontDatabase::addApplicationFont(":chinese-angular.ttf");

//    /* load the system translations provided by Qt */
//    QTranslator qtTranslator;
//    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
//    app.installTranslator(&qtTranslator);

//    /* load our custom translations for this application */
//    QTranslator myappTranslator;
//    myappTranslator.load("app" + QLocale::system().name());
//    app.installTranslator(&myappTranslator);

    MainWindow mainWindow;
    mainWindow.setWindowIcon(QIcon(":scout-talker-logo.png"));
    mainWindow.show();

    return application.exec();
}

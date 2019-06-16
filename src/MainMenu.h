/* Scout Talker - Scouting codes, ciphers and encryption program
 * Copyright (C) 2015 by Diana Capela
 *                       João  Santos    (joaompssantos@gmail.com)
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

#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMenu>
#include <QTranslator>

class AboutDialog;

class QPushButton;

class QTranslator;

class MainMenu : public QMenu {

Q_OBJECT

public:
    // Methods / Functions
    explicit MainMenu(const QString *);


private:
    // Variables
    AboutDialog *aboutDialog;

    // Actions variables
    enum mainMenuActionList {
        changeFontAction = 0,
        changeFontColourAction,
        resetDefaultsAction,
        aboutScoutTalkerAction,
        aboutQtAction,
        exitAction,
        totalAction
    };

    // Menu variables
    QMenu *languageMenu;

    QVector<QAction *> mainMenuActions;

    // Translation menu variables
    QString currLang; // Contains the currently loaded language
    QString languageTranslationsPath; // Path of language files. This is always fixed to /languages. TODO: Check this.

    // Methods / Functions
    void createActions();

    void createLanguageMenu();

    void translateMainMenu();

signals:

    void changeLanguage(QAction *);

    void changeFont();

    void changeColour();

    void resetDefaults();

private slots:

    void changeLanguageSlot(QAction *);

    void changeFontSlot();

    void changeColourSlot();

    void resetDefaultsSlot();
};


#endif // MAINMENU_H

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

#include "MainMenu.h"

#include "AboutDialog.h"

#include <QApplication>
#include <QDir>
#include <QLocale>
#include <QPushButton>

#include <QDebug> // TODO: Remove

/** Constructor **/
MainMenu::MainMenu(const QString *string) {
    // Set current language
    currLang = QString(*string);

    // Enables tool tips on main menu
    this->setToolTipsVisible(true);

    // Create Scout Talker about dialog
    aboutDialog = new AboutDialog();

    // Generate actions
    createActions();

    // Generate language menu
    languageMenu = nullptr;
    createLanguageMenu();
    this->addMenu(languageMenu);

    // Add actions to the menu
    this->addActions(mainMenuActions.toList());

    // Apply initial texts to MainMenu
    translateMainMenu();
}

/** Public Methods **/

/** Protected Methods **/

/** Private Methods **/
// Method to create actions
void MainMenu::createActions() {
    // Resize action list
    mainMenuActions.resize(totalAction);

    // Change font action
    mainMenuActions[changeFontAction] = new QAction(this);
    // Connects the Change Font action to the Change Font slot
    connect(mainMenuActions[changeFontAction], SIGNAL(triggered()), this, SLOT(changeFontSlot()));

    // Change font colour action
    mainMenuActions[changeFontColourAction] = new QAction(this);
    // Connects the Change Colour action to the Change Colour slot
    connect(mainMenuActions[changeFontColourAction], SIGNAL(triggered()), this, SLOT(changeColourSlot()));

    // Reset defaults
    mainMenuActions[resetDefaultsAction] = new QAction(this);
    // Connects the Change Colour action to the Change Colour slot
    connect(mainMenuActions[resetDefaultsAction], SIGNAL(triggered()), this, SLOT(resetDefaultsSlot()));

    // About Scout Talker action
    mainMenuActions[aboutScoutTalkerAction] = new QAction(this);
    // Sets icon for the action
    mainMenuActions[aboutScoutTalkerAction]->setIcon(QIcon(":scout-talker-logo.png"));
    // Connects the action to the aboutScoutTalkerSlot
    connect(mainMenuActions[aboutScoutTalkerAction], SIGNAL(triggered()), aboutDialog, SLOT(aboutScoutTalkerSlot()));

    // About Qt action
    mainMenuActions[aboutQtAction] = new QAction(this);
    // Sets icon for the action
    mainMenuActions[aboutQtAction]->setIcon(QIcon(":qt-logo.png"));
    // Connects the action to the aboutQt slot
    connect(mainMenuActions[aboutQtAction], SIGNAL(triggered()), QApplication::instance(), SLOT(aboutQt()));

    // Exit Scout Talker action
    mainMenuActions[exitAction] = new QAction(this);
    // Sets shortcut for the exit action
    mainMenuActions[exitAction]->setShortcuts(QKeySequence::Quit);
    // Connects the exit action to the quit slot
    connect(mainMenuActions[exitAction], SIGNAL(triggered()), QApplication::instance(), SLOT(closeAllWindows()));
}

// Creates the language menu entries dynamically depending on the existing translations
void MainMenu::createLanguageMenu() {
    // Creates the language menu
    languageMenu = new QMenu(this);

    // Created the translation action group
    auto *translationActionGroup = new QActionGroup(this);

    // Connect the translation actions to the switch language slot
    connect(translationActionGroup, SIGNAL(triggered(QAction *)), this, SLOT(changeLanguageSlot(QAction *)));

    // Define translations path
    QDir dir(languageTranslationsPath);

    // Get list of translation file names
    QStringList fileNames = dir.entryList(QStringList("ScoutTalker_*.qm"));

    // Loop translation files list
    for (int i = 0; i < fileNames.size(); ++i) {
        // Get locale extracted by filename
        QString locale = fileNames[i]; // "TranslationExample_pt_PT.qm"
        locale.truncate(locale.lastIndexOf('.')); // "TranslationExample_pt_PT"
        locale.remove(0, locale.indexOf('_') + 1); // "pt"

        // Language name and flag
        QString language = QLocale::languageToString(QLocale(locale).language());
        QIcon flag(QString(":%1.png").arg(locale));

        // Create an action for each translation
        QAction *action = new QAction(flag, QString("&%1").arg(language), this); // TODO: Find how to translate this
        action->setCheckable(true);
        action->setData(locale);

        // Add action to language menu
        languageMenu->addAction(action);
        translationActionGroup->addAction(action);

        // Check the english option
        if (language == QLocale::languageToString(QLocale(currLang).language())) {
            action->setChecked(true);
        }
    }
}

// Applies text and translations to MainWindow
void MainMenu::translateMainMenu() {
    // Menus text
    languageMenu->setTitle(tr("&Language"));
    languageMenu->setToolTip(tr("Language selection menu."));

    // Actions text
    mainMenuActions[changeFontAction]->setText(tr("Change &Font"));
    mainMenuActions[changeFontAction]->setToolTip(tr("Edit application font."));

    mainMenuActions[changeFontColourAction]->setText(tr("Change Font &Colour"));
    mainMenuActions[changeFontColourAction]->setToolTip(tr("Edit application font colour."));

    mainMenuActions[resetDefaultsAction]->setText(tr("&Reset Defaults"));
    mainMenuActions[resetDefaultsAction]->setToolTip(tr("Reset application defaults."));

    mainMenuActions[aboutScoutTalkerAction]->setText(tr("About &Scout Talker"));
    mainMenuActions[aboutScoutTalkerAction]->setToolTip(tr("Show information about Scout Talker."));

    mainMenuActions[aboutQtAction]->setText(tr("About &Qt"));
    mainMenuActions[aboutQtAction]->setToolTip(tr("Show information about Qt."));

    mainMenuActions[exitAction]->setText(tr("E&xit"));
    mainMenuActions[exitAction]->setToolTip(tr("Quit Scout Talker."));
}

// Detects language change and proceeds with the translation
void MainMenu::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        translateMainMenu();
    }
}

/** Private slots **/
// Slot to emit change language signal
void MainMenu::changeLanguageSlot(QAction *action) {
    // Save language given by the action content
    currLang = action->data().toString();

    // Emit changeLanguage signal
    emit changeLanguage(action);
}

// Slot to emit edit font signal
void MainMenu::changeFontSlot() {
    emit changeFont();
}

// Slot to emit edit colour signal
void MainMenu::changeColourSlot() {
    emit changeColour();
}

// Slot to emit reset defaults signal
void MainMenu::resetDefaultsSlot() {
    emit resetDefaults();
}
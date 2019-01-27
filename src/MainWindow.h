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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>


class MainMenu;


class QGroupBox;

class QPushButton;

class QTextEdit;


class MainWindow : public QWidget {

Q_OBJECT

public:
    // Variables

    // Types of encoding available
    enum availableCodes {
        Chinese = 0,
        Angular,
        ReverseAlphabet,
        Last
    };

    // Methods / Functions
    MainWindow();

    ~MainWindow() override;

    // Getters
    QString getToEncodeString();

    // Setters
    void setEncodedString(QString string);

private:
    // Variables
    // Menu variables
    QPushButton *mainMenuButton;
    MainMenu *mainMenu;

    QGroupBox *titleGroupBox;
    QTextEdit *mainTextBox;
    QTabWidget *codecAreaBox;

    // Translation variables
    QTranslator translatorMainWindow; // Contains the translations for this application
    QTranslator translatorQt; // Contains the translations for qt
    QString m_currLang; // Contains the currently loaded language TODO: implement this

    QString diacriticLetters ;// TODO: check these;
    QStringList nonDiacriticLetters;

    // Methods / Functions
    void createTitle();

    QString removeDiacriticLetters(QString string);

    void createCodecAreaBox();

    void setTextColour(QColor colour);

    void setTextFont(QFont font);

    void translateMainWindow();

signals:

    void sendText(QString);

private slots:

    // This slot is called by the language menu actions
    void changeLanguageSlot(QAction *action);

    void changeFontSlot();

    void changeColourSlot();

    void sendTextSlot();
};

#endif

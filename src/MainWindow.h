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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class AboutDialog;

class ScoutTalker;


class QGroupBox;

class QPushButton;

class QTextEdit;

class QVBoxLayout;


class MainWindow : public QWidget {

Q_OBJECT

public:
    // Variables

    // Types of encoding available
    enum availableTabs {
        ChineseCode, AngularCode, ReverseAlphabet, Last
    };

    // File saving types
    enum savingTypes {
        All, Font, Image
    };

    // File saving formats
    enum savingFormats {
        PNG = 0,
        PDF,
        doc,
        txt
    };

    // Methods / Functions
    MainWindow();

    ~MainWindow() override;

    // Getters
    availableTabs getTab();

    QString getToEncodeString();

    // Setters
    void setEncodedString(QString string);

    void setTextColour(QColor colour);

    void setTextFont(QFont font);

private:
    // Variables
    QGroupBox *titleGroupBox;
    QPushButton *mainMenuButton;
    QTextEdit *mainTextBox;
    QTabWidget *codecAreaBox;
    QWidget *chineseCode;
    QWidget *angularCode;
    QWidget *reverseAlphabet;
    AboutDialog *m_pcAboutDialog;
    ScoutTalker *m_scoutTalker;

    // Methods / Functions
    void createTitle();

    void createMainMenu();

    void createMainTextBox();

    void createCodecAreaBox();

    QVBoxLayout *configCodecAreaWidgets(int type);

    void createChineseCodeTab();

    void createAngularCodeTab();

    void createReverseAlphabetTab();

    void saveAsPNG(QTextEdit *textEdit, QString fileName);

    void saveAsPDF(QTextEdit *textEdit, QString fileName);

    void saveAsDoc(QTextEdit *textEdit, QString fileName);

    void saveAsTxt(QTextEdit *textEdit, QString fileName);

    void saveFiles();

signals:

    void startEncode();

public slots:

    void runEncodeSlot();

private slots:

    void changeFontSlot();

    void changeColourSlot();

    void saveSlot();
};

#endif

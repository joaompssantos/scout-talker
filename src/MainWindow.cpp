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

#include "MainWindow.h"

#include "ChineseCode.h"
#include "Code.h"
#include "MainMenu.h"

#include <QApplication>
#include <QColorDialog>
#include <QFontDialog>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

#include <QDebug> // TODO: remove


/** Constructor **/
MainWindow::MainWindow() : QWidget() {
    // Install application and Qt translators
    QApplication::installTranslator(&translatorMainWindow);
    QApplication::installTranslator(&translatorQt);

    // Main layout
    auto *mainLayout = new QVBoxLayout;

    // Creates title area widget and adds it to layout
    createTitle();
    mainLayout->addWidget(titleGroupBox); // Area with Scout Talker title, logo and menu

    // Creates main text box widget and adds it to layout
    mainTextBox = new QTextEdit();
    mainLayout->addWidget(mainTextBox); // Area with text to translate

    // Creates codec area box and adds it to layout
    createCodecAreaBox();
    mainLayout->addWidget(codecAreaBox); // Area with the codes tabs

    // Sets the margins for main layout
    mainLayout->setMargin(25);
    // Sets main layout as the main window layout
    setLayout(mainLayout);

    // Set the window title
    setWindowTitle(QApplication::applicationName());

    // Apply initial texts to MainWindow
    translateMainWindow();
}

MainWindow::~MainWindow() = default;

/** Getter methods **/
// Returns the string to encode, available in the main text field of the class
QString MainWindow::getToEncodeString() {
    return mainTextBox->toPlainText();
}

/** Setter methods **/
// Sets the string for the codec area text field
void MainWindow::setEncodedString(QString string) { // TODO: check if it is used or needed
    // TODO: Confirmar (o nome do objeto a passar tem de ser definido com o método setObjectName) NOT USED??
    auto *currentTextBox = codecAreaBox->currentWidget()->findChild<QTextEdit *>();
    currentTextBox->setText(string);
}

/** Public Methods **/

/** Protected Methods **/

/** Private Methods **/
// Sets the text colour
void MainWindow::setTextColour(QColor colour) {
    // Sets text colour
    mainTextBox->setTextColor(colour);
    // Reload text to assert colour
    mainTextBox->setText(getToEncodeString());

    for (int i = 0; i < MainWindow::Last; i++) {
        auto *textBox = codecAreaBox->widget(i)->findChild<QTextEdit *>(); // TODO: check if it is correct, same for setTextFont
        // Sets text colour
        textBox->setTextColor(colour);
        // Reload text to assert colour
        textBox->setText(textBox->toPlainText());
    }
}

// Sets the text font
void MainWindow::setTextFont(QFont font) {
    // Sets text font
    mainTextBox->setFont(font);

    for (int i = 0; i < MainWindow::Last; i++) {
        auto *textBox = codecAreaBox->widget(i)->findChild<QTextEdit *>(); // TODO: check if it is correct

        // Saves current font
        QFont aux_font = QFont(font.family(), font.pointSize(), font.weight(), font.italic());

        // If a special Font is used it is kept
        if (i == MainWindow::Chinese || i == MainWindow::Angular) {
            aux_font.setFamily(textBox->font().family());
            aux_font.setCapitalization(textBox->font().capitalization());
            aux_font.setPointSize(aux_font.pointSize() + 20);
            textBox->setFont(aux_font);
        } else {
            // Sets text font
            textBox->setFont(font);
        }
    }
}

/** Private Methods **/
// Method to create the title area
void MainWindow::createTitle() {
    // Creates the group box
    titleGroupBox = new QGroupBox();

    // Creates the Horizontal Box Layout for the group box
    auto *layout = new QHBoxLayout;

    // Creates the main title of the program label
    auto *mainTitle = new QLabel(QApplication::applicationName());

    // Center aligns the label
    mainTitle->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setFamily(font.defaultFamily()); // Sets the font as the default one
    font.setPointSize(20); // Sets font size
    font.setBold(true); // Sets font as bold

    // Changes the label font
    mainTitle->setFont(font);

    // Creates the main menu
    // Creates push button that will contain the main logo
    mainMenuButton = new QPushButton();

    // Sets button size
    mainMenuButton->setFixedSize(100, 100);

    // Sets button icon and size
    mainMenuButton->setIcon(QIcon(":scout-talker-logo.png"));
    mainMenuButton->setIconSize(QSize(95, 95));

    // Changes button style sheet to remove the menu indicator and border
    mainMenuButton->setStyleSheet("QPushButton::menu-indicator {image: none;}"
                                  "QPushButton {border: 0px solid #8f8f91;}");

    // Sets hovering cursor for the button
    mainMenuButton->setCursor(Qt::PointingHandCursor);

    // Adds the main menu to the push button
    mainMenu = new MainMenu();
    mainMenuButton->setMenu(mainMenu);

    // Connects the Main Menu signals to the Main Window slots
    connect(mainMenu, SIGNAL(changeLanguage(QAction *)), this, SLOT(changeLanguageSlot(QAction *)));
    connect(mainMenu, SIGNAL(changeFont()), this, SLOT(changeFontSlot()));
    connect(mainMenu, SIGNAL(changeColour()), this, SLOT(changeColourSlot()));

    // Set alignment of the layout
    layout->setAlignment(Qt::AlignCenter);

    // Add an empty space with the size of 50
    layout->insertSpacing(0, 50);

    // Add title widget to the layout
    layout->addWidget(mainTitle);

    // Add space between widgets
    layout->addSpacing(25);

    // Add button to the layout
    layout->addWidget(mainMenuButton);

    // Add an empty space with the size of 50
    layout->addSpacing(50);

    // Sets the group box layout
    titleGroupBox->setLayout(layout);
    // Command to remove border of Group Box
    titleGroupBox->setStyleSheet("QGroupBox {border: 0px solid gray;}");
}

// Method to remove diacritic letters, such as ç or á
QString MainWindow::removeDiacriticLetters(QString string) {
    // Check if the diacritic letters string has already been created. If not the string is now populated.
    if (diacriticLetters.isEmpty()) {
        diacriticLetters = QString::fromUtf8("ŠŒŽšœžŸ¥µÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýÿ");
        nonDiacriticLetters << "S" << "OE" << "Z" << "s" << "oe" << "z" << "Y" << "Y" << "u" << "A" << "A" << "A" << "A"
                            << "A" << "A" << "AE" << "C" << "E" << "E" << "E" << "E" << "I" << "I" << "I" << "I" << "D"
                            << "N" << "O" << "O" << "O" << "O" << "O" << "O" << "U" << "U" << "U" << "U" << "Y" << "s"
                            << "a" << "a" << "a" << "a" << "a" << "a" << "ae" << "c" << "e" << "e" << "e" << "e" << "i"
                            << "i" << "i" << "i" << "o" << "n" << "o" << "o" << "o" << "o" << "o" << "o" << "u" << "u"
                            << "u" << "u" << "y" << "y";
    }

    // Creates the output string
    QString output = "";

    // Loop that iterates through the input string and replaces diacritic letters with their non-diacritic equivalent
    for (auto ch : string) {
        int dIndex = diacriticLetters.indexOf(ch);

        if (dIndex < 0) {
            output.append(ch);
        } else {
            QString replacement = nonDiacriticLetters[dIndex];
            output.append(replacement);
        }
    }

    return output;
}

// Method to create the codec area box
void MainWindow::createCodecAreaBox() {
    // Creates the tab widget
    codecAreaBox = new QTabWidget();

    // Style for the tabs and their box
    codecAreaBox->setStyleSheet("QTabWidget::pane { border: 1px solid gray;}");

    // Adds the widgets to the codec area box
    codecAreaBox->insertTab(availableCodes::Chinese, new ChineseCode(), tr("Chinese Code")); // TODO: consider adding availableCodes::Chinese to the class itself
    codecAreaBox->insertTab(availableCodes::Angular, new Code(SaveCode::savingTypes::All), tr("Angular Code"));
    codecAreaBox->insertTab(availableCodes::ReverseAlphabet, new Code(SaveCode::savingTypes::All), tr("Reverse Alphabet"));

    // Connect Code startEncoding() signal to the sendTextSlot() slot
    // then connect sendText() signal to Code encode()slot
    // TODO: apparently this way the slots from all Codes are activated (not necessarily a bad thing)
    QList<Code *> codes = codecAreaBox->findChildren<Code *>();
    for (auto i = 0; i < availableCodes::Last; i++) {
        connect(codes.at(i), SIGNAL(startEncoding()), this, SLOT(sendTextSlot()));
        connect(this, SIGNAL(sendText(QString)), codes.at(i), SLOT(encode(QString)));
    }
}

// Applies text and translations to MainWindow
void MainWindow::translateMainWindow() {
    // Main box text
    mainTextBox->setText(tr("Insert text to encode..."));

    // Tabs label
    codecAreaBox->setTabText(availableCodes::Chinese, tr("Chinese Code"));
    codecAreaBox->setTabText(availableCodes::Angular, tr("Angular Code"));
    codecAreaBox->setTabText(availableCodes::ReverseAlphabet, tr("Reverse Alphabet"));

    // Buttons text
    mainMenuButton->setToolTip(tr("Opens Scout Talker main menu."));
}

/** Public slots **/

/** Private slots **/
// Language change slot
void MainWindow::changeLanguageSlot(QAction *action) {
    // Load the language dependant on the action content
    QString locale = action->data().toString();

    // Load translators
    translatorMainWindow.load("ScoutTalker_" + locale + ".qm");
    // translatorQt.load("/usr/share/qt5/translations/qt_pt.qm"); // TODO: try to fix this or remove About Qt

    // Translate MainWindow texts to the selected language
    translateMainWindow();
}

// Slot to edit font
void MainWindow::changeFontSlot() {
    bool assert_font;

    QFont font = QFontDialog::getFont(&assert_font, mainTextBox->font(), this);

    if (assert_font) setTextFont(font);
}


// Slot to edit font
void MainWindow::changeColourSlot() {
    QColor colour = QColorDialog::getColor(mainTextBox->textColor(), this);

    if (colour.isValid()) setTextColour(colour);
}

void MainWindow::sendTextSlot() {
    QList<Code *> codes = codecAreaBox->findChildren<Code *>(); // TODO: currently unnecessary

    emit sendText(removeDiacriticLetters(getToEncodeString()));
}
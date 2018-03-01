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

#include "ScoutTalker.h"

#include "MainWindow.h"

ScoutTalker::ScoutTalker(MainWindow *w) {
    toEncodeString = new QString("");
    encodedString = new QString("");
    mainWindow = w;

    connect(mainWindow, SIGNAL(startEncode()), this, SLOT(encodeSlot()));
}

// Method that clears the class strings
void ScoutTalker::clearStrings() {
    toEncodeString->clear();
    encodedString->clear();
}

// Method to remove diacritic letters, such as ç or á
QString ScoutTalker::removeDiacriticLetters(QString string) {
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
    for (int i = 0; i < string.length(); i++) {
        QChar ch = string[i];
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

// Method that manages the encoding process
void ScoutTalker::encode() {
    // Clears the class strings
    clearStrings();

    // Read the string to encode from the window object and remove diatritic letters
    toEncodeString->append(removeDiacriticLetters(mainWindow->getToEncodeString()));

    // Gets current tab from the window object
    MainWindow::availableTabs currentTab = mainWindow->getTab();

    switch (currentTab) {
        case MainWindow::ChineseCode:
            // Do the procedures to perform the chinese code
            encodeChineseCode();
            break;
        case MainWindow::AngularCode:
            // Do the procedures to perform the angular code
            encodeAngularCode();
            break;
        case MainWindow::ReverseAlphabet:
            // Do the procedures to perform the reverse alphabet
            encodeReverseAlphabet();
            break;
        default:
            // Do the procedures to perform the chinese code
            encodeChineseCode();
            break;
    }

    // Pushes the resulting string to the window object
    mainWindow->setEncodedString(*encodedString);
}

void ScoutTalker::encodeChineseCode() {
    encodedString->append(toEncodeString);
}

void ScoutTalker::encodeAngularCode() {
    encodedString->append(toEncodeString);
}

void ScoutTalker::encodeReverseAlphabet() {
    int nChars = toEncodeString->count();
    encodedString->append(toEncodeString);

    for (int i = 0; i < nChars; i++) {
        QChar currentCharacter = (*toEncodeString)[i];

        if (currentCharacter.unicode() >= 0x41 && currentCharacter.unicode() <= 0x5A) {
            (*encodedString)[i] = (QChar) (0x9B - currentCharacter.unicode());
        } else if (currentCharacter.unicode() >= 0x61 && currentCharacter.unicode() <= 0x7A) {
            (*encodedString)[i] = (QChar) (0xDB - currentCharacter.unicode());
        }
    }
}

void ScoutTalker::encodeSlot() {
    encode();
}

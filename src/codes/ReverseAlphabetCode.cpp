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

#include "ReverseAlphabetCode.h"

#include "HelpDialog.h"

#include <QTextEdit>

/** Constructor **/
// Creates new instance of Code with the proper text
ReverseAlphabetCode::ReverseAlphabetCode() : Code(SaveCode::savingTypes::All) {
    helpTitle = tr("Reverse Alphabet code");
    helpText = tr("This cipher simply reverses the alphabet, thus A = Z, B = Y, C = X, ...");
    helpDialog->setHelpStrings(helpTitle, helpText);
}

/** Public Slots **/
void ReverseAlphabetCode::encode(QString string) {
    auto nChars = string.count();

    QString encodedString;
    encodedString.append(string);

    for (auto i = 0; i < nChars; i++) {
        auto currentCharacter = string[i];

        if (currentCharacter.unicode() >= 0x41 && currentCharacter.unicode() <= 0x5A) {
            encodedString[i] = (QChar) (0x9B - currentCharacter.unicode());
        }
        else if (currentCharacter.unicode() >= 0x61 && currentCharacter.unicode() <= 0x7A) {
            encodedString[i] = (QChar) (0xDB - currentCharacter.unicode());
        }
    }

    textBox->setText(encodedString);
}
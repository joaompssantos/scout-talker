/* Scout Talker
Copyright (C) 2017  Diana Capela & João Santos

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. */

#include "scouttalker.h"
#include "window.h"
#include <QChar>
#include <QString>
#include <QStringList>

ScoutTalker::ScoutTalker(Window *w, QObject *parent) : QObject(parent)
{
    toEncodeString = new QString("");
    encodedString = new QString("");
    window = w;

    connect(window, SIGNAL(startEncode()), this, SLOT(encodeSlot()));
}

// Method that clears the class strings
void ScoutTalker::clearStrings()
{
    toEncodeString->clear();
    encodedString->clear();
}

// Method to remove diacritic letters, such as ç or á
QString ScoutTalker::removeAccents(QString string) {
    // Check if the diacritic letters string has already been created. If not the string is now populated.
    if (diacriticLetters_.isEmpty()) {
        diacriticLetters_ = QString::fromUtf8("ŠŒŽšœžŸ¥µÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýÿ");
        noDiacriticLetters_ << "S"<<"OE"<<"Z"<<"s"<<"oe"<<"z"<<"Y"<<"Y"<<"u"<<"A"<<"A"<<"A"<<"A"<<"A"<<"A"<<"AE"<<"C"<<"E"<<"E"<<"E"<<"E"<<"I"<<"I"<<"I"<<"I"<<"D"<<"N"<<"O"<<"O"<<"O"<<"O"<<"O"<<"O"<<"U"<<"U"<<"U"<<"U"<<"Y"<<"s"<<"a"<<"a"<<"a"<<"a"<<"a"<<"a"<<"ae"<<"c"<<"e"<<"e"<<"e"<<"e"<<"i"<<"i"<<"i"<<"i"<<"o"<<"n"<<"o"<<"o"<<"o"<<"o"<<"o"<<"o"<<"u"<<"u"<<"u"<<"u"<<"y"<<"y";
    }

    // Creates the output string
    QString output = "";

    // Loop that iterates through the input string and replaces diacritic letters with their non-diacritic equivalen
    for (int i = 0; i < string.length(); i++)
    {
        QChar ch = string[i];
        int dIndex = diacriticLetters_.indexOf(ch);

        if (dIndex < 0)
        {
            output.append(ch);
        }
        else
        {
            QString replacement = noDiacriticLetters_[dIndex];
            output.append(replacement);
        }
    }

    return output;
}

// Method that manages the encoding process
void ScoutTalker::encode()
{
    // Clears the class strings
    clearStrings();

    // Read the string to encode from the window object and remove diatritic letters
    toEncodeString->append(removeAccents(window->getToEncodeString()));

    // Gets current tab from the window object
    Window::availableTabs currentTab = window->getTab();

    switch (currentTab) {
    case Window::ChineseCode:
        // Do the procedures to perform the chinese code
        encodeChineseCode();
        break;
    case Window::AngularCode:
        // Do the procedures to perform the angular code
        encodeAngularCode();
        break;
    case Window::ReverseAlphabet:
        // Do the procedures to perform the reverse alphabet
        encodeReverseAlphabet();
        break;
    default:
        // Do the procedures to perform the chinese code
        encodeChineseCode();
        break;
    }

    // Pushes the resulting string to the window object
    window->setEncodedString(*encodedString);
}

void ScoutTalker::encodeChineseCode()
{
    encodedString->append(toEncodeString);
}

void ScoutTalker::encodeAngularCode()
{
    encodedString->append(toEncodeString);
}

void ScoutTalker::encodeReverseAlphabet()
{
    int nChars = toEncodeString->count();
    encodedString->append(toEncodeString);

    for (int i = 0; i < nChars; i++)
    {
        QChar currentCharacter = (*toEncodeString)[i];

        if (currentCharacter.unicode() >= 0x41 && currentCharacter.unicode() <= 0x5A)
        {
            (*encodedString)[i] = (QChar) (0x9B - currentCharacter.unicode());
        }
        else if (currentCharacter.unicode() >= 0x61 && currentCharacter.unicode() <= 0x7A)
        {
            (*encodedString)[i] = (QChar) (0xDB - currentCharacter.unicode());
        }
    }
}

void ScoutTalker::encodeSlot()
{
    encode();
}

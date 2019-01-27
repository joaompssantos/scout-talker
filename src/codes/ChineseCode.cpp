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

#include "ChineseCode.h"

#include "HelpDialog.h"

#include <QTextEdit>

/** Constructor **/
// Creates new instance of Code with the proper text
ChineseCode::ChineseCode() : Code(SaveCode::savingTypes::Font) {
    helpTitle = tr("Chinese code");
    helpText = tr("This cipher is composed only of horizontal and vertical dashes.\n\n"
                  "The vertical dashes correspond to vowels, e.g. one dash equals 'a' and five dashes equal 'u'.\n\n"
                  "Every other letter is obtained by adding horizontal dashes, for instance 'b' is a vertical dash"
                  "crossed by a horizontal dash."); // TODO: Improve later, maybe by adding figures??

    helpDialog->setHelpStrings(helpTitle, helpText);

    // Do the configuration of the font for the chinese code text box
    QFont font;
    font.setFamily("Chines & Internacional");
    font.setCapitalization(QFont::AllUppercase);
    font.setPointSize(textBox->font().pointSize() + 20);

    // Sets the font for the text box
    textBox->setFont(font);
}
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

#include "AngularCode.h"

#include "HelpDialog.h"

#include <QTextEdit>

/** Constructor **/
// Creates new instance of Code with the proper text
AngularCode::AngularCode() : Code(SaveCode::savingTypes::Font) {
    helpTitle = tr("Angular code");
    helpText = tr("<p>The Angular cipher, also known as Pinpen, is a geometric simple substitution cipher, "
                  "which exchanges letters for symbols which are fragments of a grid.</p>"
                  "<p>For more information please refer to the Wikipedia article on "
                  "<a href=\"https://en.wikipedia.org/wiki/Pigpen_cipher\">Pigpen</a>.</p>"); // TODO: Improve later, maybe by adding figures??

    helpDialog->setHelpStrings(helpTitle, helpText);

    // Do the configuration of the font for the chinese code text box
    QFont font;
    font.setFamily("Chines & Internacional");
    font.setCapitalization(QFont::AllLowercase);
    font.setPointSize(textBox->font().pointSize() + 20);

    // Sets the font for the text box
    textBox->setFont(font);
}
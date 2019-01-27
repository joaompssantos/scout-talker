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

#include "HelpDialog.h"

// Creates new instance of AboutDialog with the proper text
HelpDialog::HelpDialog(QString const title, QString const text) : QMessageBox() {
    helpTitle = title;
    helpText = text;
}

void HelpDialog::setHelpStrings(QString const title, QString const text) {
    helpTitle = title;
    helpText = text;
}

// Shows QMessageBox with AboutDialog text
void HelpDialog::helpDialogSlot() {
    QMessageBox::about(parentWidget(), helpTitle, helpText);
}
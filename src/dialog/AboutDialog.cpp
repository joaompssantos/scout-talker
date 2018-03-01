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

#include "AboutDialog.h"

#include <QApplication>

// Creates new instance of AboutDialog with the proper text
AboutDialog::AboutDialog(QWidget *parent) : QMessageBox(parent) {
    translateAboutDialog();
}

// Translate the text of AboutDialog
void AboutDialog::translateAboutDialog() {
    aboutDefinition = tr("Qt based, open source Scout codes cipher program.");
    aboutVersion = tr("Version");

    aboutText = QString("<p><h3>%1:</h3></p>" "%2" "<p>%3: %4</p>" "<p>Copyright © 2015 - 2018, %5.</p>")
            .arg(QApplication::applicationName())
            .arg(aboutDefinition)
            .arg(aboutVersion)
            .arg(QApplication::applicationVersion())
            .arg(QApplication::organizationName());
}

// Detects language change and proceeds with the translation
void AboutDialog::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        translateAboutDialog();
    }

    QMessageBox::changeEvent(event);
}

// Shows QMessageBox with AboutDialog text
void AboutDialog::aboutScoutTalkerSlot() {
    QMessageBox::about(parentWidget(), QString("About %1").arg(QApplication::applicationName()), aboutText);
}

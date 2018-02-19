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
#include "MainWindow.h"

#include <QApplication>

AboutDialog::AboutDialog() {
    aboutText = QString(
            tr("<p><h3>%1:</h3></p>"
                       "Qt based, open source Scout codes cipher machine."
                       "<p>Version: %2</p>"
                       "<p>Copyright © 2015 - 2018, %3.</p>"))
            .arg(QApplication::applicationName())
            .arg(QApplication::applicationVersion())
            .arg(QApplication::organizationName());
}

void AboutDialog::aboutScoutTalker() {
    QMessageBox::about(parentWidget(), QString("About %1").arg(QApplication::applicationName()), aboutText);
}

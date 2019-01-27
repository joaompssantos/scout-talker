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

#ifndef SAVECODE_H
#define SAVECODE_H

#include <QObject>


class QTextEdit;


class SaveCode : public QObject {

Q_OBJECT

public:
    // Variables

    // File saving types
    enum savingTypes {
        All,
        Font,
        Image
    };

    // Stores the available saving formats for a given code
    savingTypes savingType;

    // Stores the text editor box
    QTextEdit *textEdit;
    
    // Stores filename
    QString fileName;

    // Methods
    SaveCode(savingTypes, QTextEdit *);

private:
    // Variables

    // Methods
    void saveAsPNG();

    void saveAsPDF();

    void saveAsDoc();

    void saveAsTxt();

public slots:

    void saveFile();
};


#endif //SAVECODE_H

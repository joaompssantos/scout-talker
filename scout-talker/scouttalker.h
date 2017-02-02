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

#ifndef SCOUTTALKER_H
#define SCOUTTALKER_H

#include <QObject>
#include <QStringList>

class QString;
//class QStringList;
class Window;
class ScoutTalker : public QObject
{
    Q_OBJECT
public:
    explicit ScoutTalker(Window *w, QObject *parent);

    // Methods / Functions
private:
    // Variables
    QString *toEncodeString;
    QString *encodedString;
    QString diacriticLetters_;
    QStringList noDiacriticLetters_;

    Window *window;

    // Methods / Functions
    void clearStrings();
    QString removeAccents(QString string);
    void encode();
    void encodeChineseCode();
    void encodeAngularCode();
    void encodeReverseAlphabet();

signals:

public slots:
    void encodeSlot();
};

#endif // SCOUTTALKER_H

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

#ifndef CODE_H
#define CODE_H

#include <QWidget>
#include <SaveCode.h>


class HelpDialog;


class QPushButton;

class QString;

class QTextEdit;

class QVBoxLayout;


class Code : public QWidget {

Q_OBJECT

public:
    // Variables

    // Methods / Functions
    explicit Code(SaveCode::savingTypes);

protected:
    //Variables
    // Help text
    QString helpTitle;
    QString helpText;
    HelpDialog *helpDialog;

    QTextEdit *textBox;

    // Methods

private:
    // Variables

    // Widget file save type
    SaveCode::savingTypes saveType;

    // Widget buttons
    QPushButton *encodeButton;
    QPushButton *helpButton;
    QPushButton *saveButton;

    // SaveCode
    SaveCode *saveCode;

    // Methods / Functions
    QVBoxLayout *configCodecAreaWidgets();

    void translateCodecArea();

    // TODO: check if necessary, if necessary use this model in other classes
    void changeEvent(QEvent *) override;

signals:
    void startEncoding();

protected slots:
    virtual void encode(QString);

private slots:

    void startEncodingSlot();

};


#endif // CODE_H

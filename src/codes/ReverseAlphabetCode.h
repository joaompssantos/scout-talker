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

#ifndef REVERSEALPHABETCODE_H
#define REVERSEALPHABETCODE_H

#include "Code.h"

class ReverseAlphabetCode : public Code {

Q_OBJECT

public:
    // Methods / Functions
    ReverseAlphabetCode();

private:
    // Methods
    void changeEvent(QEvent *) override;

    void translateHelpText() override ;

protected slots:

    void encode(QString) override;
};


#endif // REVERSEALPHABETCODE_H

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

#include "Code.h"

#include "HelpDialog.h"
//#include "SaveCode.h"

#include <QEvent>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>

/** Constructor **/
// Creates new instance of Code with the proper text
Code::Code(SaveCode::savingTypes sType) : QWidget(nullptr) {
    saveType = sType;

    helpTitle = tr("This is a help title!");
    helpText = tr("This is a help text!");

    helpDialog = new HelpDialog(helpTitle, helpText);

    // Sets the layout for the chinese code
    this->setLayout(configCodecAreaWidgets());

    // Apply initial texts to Code
    translateCodecArea();
}


/** Public Methods **/

/** Protected Methods **/

/** Private Methods **/
// Method to configure the codec area box widgets
QVBoxLayout *Code::configCodecAreaWidgets() {
    // Creates the main outter layout for a codec tab
    auto *mainLayout = new QVBoxLayout;


    // Text Box
    // Creates the text box
    textBox = new QTextEdit();

    // Adds the text box to the main layout
    mainLayout->addWidget(textBox);


    // Button Layout
    auto *buttonLayout = new QHBoxLayout;

    // Creates the encode button for the top box
    encodeButton = new QPushButton();
    // Connect the encode button the run encode slot, that signals that the cipher should start
    connect(encodeButton, SIGNAL(clicked()), this, SLOT(startEncodingSlot()));

    // Creates the help button for the top box
    helpButton = new QPushButton();
    connect(helpButton, &QPushButton::clicked, helpDialog, &HelpDialog::helpDialogSlot); // TODO: Consider changing all connections to this syntax

    // Create the save button of the bottom box
    saveButton = new QPushButton();
    // Connect the save button the save slot, that signals that the save procedures should start

    saveCode = new SaveCode(saveType, textBox); // TODO: check if it can be here
    connect(saveButton, &QPushButton::clicked, saveCode, &SaveCode::saveFile);

    // Add the widgets to the top box layout
    buttonLayout->addWidget(encodeButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(helpButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveButton);

    // Assign the bottom box to the main layout
    mainLayout->addLayout(buttonLayout);

    // Returns the main layout
    return mainLayout;
}

// Translate the text of AboutDialog
void Code::translateCodecArea() {
    // Adds cipher button text
    encodeButton->setText(tr("Cipher"));
    // Adds tooltip to the encode button
    encodeButton->setToolTip(tr("Push to execute the ciphering process."));
    // Add help button text
    helpButton->setText(tr("Help"));
    // Adds tooltip to the help button
    helpButton->setToolTip(tr("Push to show help for the current cipher."));
    // Adds save button text
    saveButton->setText(tr("Save"));
    // Adds tooltip to the save button
    saveButton->setToolTip(tr("Push to save the result of the ciphering process."));
}

// Detects language change and proceeds with the translation
void Code::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        translateCodecArea();
    }
}

/** Public Slots **/
void Code::encode(QString string) {
    textBox->setText(string);
}

/** Private Slots **/
void Code::startEncodingSlot() {
    emit startEncoding();
}
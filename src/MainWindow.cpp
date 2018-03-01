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

#include "MainWindow.h"

#include "AboutDialog.h"
#include "ScoutTalker.h"

#include <QApplication>
#include <QCheckBox>
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QGroupBox>
#include <QLabel>
#include <QMenu>
#include <QPainter>
#include <QPrinter>
#include <QPushButton>
#include <QTextDocumentWriter>
#include <QTextEdit>
#include <QTextStream>
#include <QVBoxLayout>

MainWindow::MainWindow() : scoutTalker(NULL) {
    // Initiate ScoutTalker instance
    scoutTalker = new ScoutTalker(this);

    qApp->installTranslator(&translatorMainWindow);
    qApp->installTranslator(&translatorQt);

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // Create Scout Talker about dialog
    aboutDialog = new AboutDialog(this);

    // Creates title area widget
    createTitle();
    // Creates main text box widget
    createMainTextBox();
    // Creates codec area box
    createCodecAreaBox();

    // Add the widgets to the main layout
    mainLayout->addWidget(titleGroupBox);
    mainLayout->addWidget(mainTextBox);
    mainLayout->addWidget(codecAreaBox);

    // Sets the margins for main layout
    mainLayout->setMargin(25);
    // Sets main layout as the main window layout
    setLayout(mainLayout);

    // Set the window title
    setWindowTitle(QApplication::applicationName());

    // Apply initial texts to MainWindow
    translateMainWindow();
}

MainWindow::~MainWindow() {}

/** Getter methods **/
// Returns the current selected tab
MainWindow::availableTabs MainWindow::getTab() {
    return availableTabs(codecAreaBox->currentIndex());
}

// Returns the string to encode, available in the main text field of the class
QString MainWindow::getToEncodeString() {
    return mainTextBox->toPlainText();
}

/** Setter methods **/
// Sets the string for the codec area text field
void MainWindow::setEncodedString(QString string) {
    // TODO: Confirmar (o nome do objeto a passar tem de ser definido com o método setObjectName)
    QTextEdit *currentTextBox = codecAreaBox->currentWidget()->findChild<QTextEdit *>();
    currentTextBox->setText(string);
}

// Sets the text colour
void MainWindow::setTextColour(QColor colour) {
    // Sets text colour
    mainTextBox->setTextColor(colour);
    // Reload text to assert colour
    mainTextBox->setText(getToEncodeString());

    for (int i = 0; i < MainWindow::Last; i++) {
        QTextEdit *textBox = codecAreaBox->widget(i)->findChild<QTextEdit *>();
        // Sets text colour
        textBox->setTextColor(colour);
        // Reload text to assert colour
        textBox->setText(textBox->toPlainText());
    }
}

// Sets the text font
void MainWindow::setTextFont(QFont font) {
    // Sets text font
    mainTextBox->setFont(font);

    for (int i = 0; i < MainWindow::Last; i++) {
        QTextEdit *textBox = codecAreaBox->widget(i)->findChild<QTextEdit *>();

        // Saves current font
        QFont aux_font = QFont(font.family(), font.pointSize(), font.weight(), font.italic());

        // If a special Font is used it is kept
        if (i == MainWindow::ChineseCode || i == MainWindow::AngularCode) {
            aux_font.setFamily(textBox->font().family());
            aux_font.setCapitalization(textBox->font().capitalization());
            aux_font.setPointSize(aux_font.pointSize() + 20);
            textBox->setFont(aux_font);
        } else {
            // Sets text font
            textBox->setFont(font);
        }
    }
}

/** Private Methods **/
// Method to create the title area
void MainWindow::createTitle() {
    // Creates the group box
    titleGroupBox = new QGroupBox();

    // Creates the Horizontal Box Layout for the group box
    QHBoxLayout *layout = new QHBoxLayout;

    // Creates the main title of the program label
    QLabel *mainTitle = new QLabel(QApplication::applicationName());

    // Center aligns the label
    mainTitle->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setFamily(font.defaultFamily()); // Sets the font as the default one
    font.setPointSize(20); // Sets font size
    font.setBold(true); // Sets font as bold

    // Changes the label font
    mainTitle->setFont(font);

    // Create Main Window actions
    createActions();

    // Creates the main menu
    createMainMenu();

    // Set alignment of the layout
    layout->setAlignment(Qt::AlignCenter);

    // Add an empty space with the size of 50
    layout->insertSpacing(0, 50);

    // Add title widget to the layout
    layout->addWidget(mainTitle);

    // Add space between widgets
    layout->addSpacing(25);

    // Add button to the layout
    layout->addWidget(mainMenuButton);

    // Add an empty space with the size of 50
    layout->addSpacing(50);

    // Sets the group box layout
    titleGroupBox->setLayout(layout);
    // Command to remove border of Group Box
    titleGroupBox->setStyleSheet("QGroupBox {border: 0px solid gray;}");
}

void MainWindow::createActions() {
    // Resize action list
    mainWindowActions.resize(totalAction);

    // Change font action
    mainWindowActions[changeFontAction] = new QAction(this);
    // Connects the Change Font action to the Change Font slot
    connect(mainWindowActions[changeFontAction], SIGNAL(triggered()), this, SLOT(changeFontSlot()));

    // Change font colour action
    mainWindowActions[changeFontColourAction] = new QAction(this);
    // Connects the Change Colour action to the Change Colour slot
    connect(mainWindowActions[changeFontColourAction], SIGNAL(triggered()), this, SLOT(changeColourSlot()));

    // About Scout Talker action
    mainWindowActions[aboutScoutTalkerAction] = new QAction(this);
    // Sets icon for the action
    mainWindowActions[aboutScoutTalkerAction]->setIcon(QIcon(":scout-talker-logo.png"));
    // Connects the action to the aboutScoutTalkerSlot
    connect(mainWindowActions[aboutScoutTalkerAction], SIGNAL(triggered()), aboutDialog, SLOT(aboutScoutTalkerSlot()));

    // About Qt action
    mainWindowActions[aboutQtAction] = new QAction(this);
    // Sets icon for the action
    mainWindowActions[aboutQtAction]->setIcon(QIcon(":qt-logo.png"));
    // Connects the action to the aboutQt slot
    connect(mainWindowActions[aboutQtAction], SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    // Exit Scout Talker action
    mainWindowActions[exitAction] = new QAction(this);
    // Sets shortcut for the exit action
    mainWindowActions[exitAction]->setShortcuts(QKeySequence::Quit);
    // Connects the exit action to the quit slot
    connect(mainWindowActions[exitAction], SIGNAL(triggered()), qApp, SLOT(quit()));
}

// Method to create the main menu
void MainWindow::createMainMenu() {
    // Creates the push button main menu
    QMenu *mainMenu = new QMenu();
    // Enables tool tips on main menu
    mainMenu->setToolTipsVisible(true);

    // Add actions to the menu
    // Add Change Font action to the menu
    mainMenu->addAction(mainWindowActions[changeFontAction]);
    // Add Change Colour action to the menu
    mainMenu->addAction(mainWindowActions[changeFontColourAction]);

    // Create and add change language action to the menu
    createLanguageMenu();
    mainMenu->addMenu(changeLanguageMenu);

    //Add About Scout Talker action to the menu
    mainMenu->addAction(mainWindowActions[aboutScoutTalkerAction]);
    // Add About Qt action to the menu
    mainMenu->addAction(mainWindowActions[aboutQtAction]);
    // Add Exit action to the menu
    mainMenu->addAction(mainWindowActions[exitAction]);


    // Creates push button that will contain the main logo
    mainMenuButton = new QPushButton();

    // Sets button size
    mainMenuButton->setFixedSize(100, 100);

    // Sets button icon and size
    mainMenuButton->setIcon(QIcon(":scout-talker-logo.png"));
    mainMenuButton->setIconSize(QSize(95, 95));

    // Changes button style sheet to remove the menu indicator and border
    mainMenuButton->setStyleSheet("QPushButton::menu-indicator {image: none;}"
                                          "QPushButton {border: 0px solid #8f8f91;}");

    // Sets hovering cursor for the button
    mainMenuButton->setCursor(Qt::PointingHandCursor);

    // Adds the main menu to the push button
    mainMenuButton->setMenu(mainMenu);
}

// Method to create and customise the main text box
void MainWindow::createMainTextBox() {
    mainTextBox = new QTextEdit();
    mainTextBox->setText(tr("Insert text to encode..."));
}

// Method to create the codec area box
void MainWindow::createCodecAreaBox() {
    // Creates the tab widget
    codecAreaBox = new QTabWidget();

    // Style for the tabs --> VERIFICAR SE É PARA MANTER
    codecAreaBox->setStyleSheet("QTabWidget::pane { border: 1px solid gray;}");

    // Configure the widgets of each code
    createChineseCodeTab();
    createAngularCodeTab();
    createReverseAlphabetTab();

    // Adds the widgets to the codec area box
    codecAreaBox->addTab(chineseCode, tr("Chinese Code"));
    codecAreaBox->addTab(angularCode, tr("Angular Code"));
    codecAreaBox->addTab(reverseAlphabet, tr("Reverse Alphabet"));
}

// Method to configure the codec area box widgets
QVBoxLayout *MainWindow::configCodecAreaWidgets(int type) {
    // Creates the main outter layout for a codec tab
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // Top Box
    QGroupBox *topBox = new QGroupBox;
    // Top box layout
    QHBoxLayout *topBoxLayout = new QHBoxLayout;

    // Creates the encode button for the top box
    QPushButton *encodeButton = new QPushButton(tr("Cipher"));
    // Connect the encode button the run encode slot, that signals that the cipher should start
    connect(encodeButton, SIGNAL(clicked()), this, SLOT(runEncodeSlot()));
    // Adds tooltip to the encode button
    encodeButton->setToolTip(tr("Push to execute the ciphering process."));

    // Creates the help button for the top box
    helpButton = new QPushButton(tr("Help")); // TODO: Implement help dialogs.
    // Adds tooltip to the help button
    helpButton->setToolTip(tr("Push to show help for the current cipher (NOT IMPLEMENTED)."));

    // Add the widgets to the top box layout
    topBoxLayout->addWidget(encodeButton);
    topBoxLayout->addStretch();
    topBoxLayout->addWidget(helpButton);

    // Assign top box layout to the top box
    topBox->setLayout(topBoxLayout);
    // Command to remove border of Group Box
    topBox->setStyleSheet("QGroupBox {border: 0px solid gray;}");

    // Add tob box to the main layout
    mainLayout->addWidget(topBox);


    // Middle Box
    // Creates the text box
    QTextEdit *codecTextBox = new QTextEdit();

    // Adds the text box to the main layout
    mainLayout->addWidget(codecTextBox);


    // Bottom Box
    QGroupBox *bottomBox = new QGroupBox(tr("Save options"));
    // Bottom box layout
    QHBoxLayout *bottomBoxLayout = new QHBoxLayout;

    // Creates the label for the saving options of the bottom box
    QLabel *formatLabel = new QLabel(tr("Format:"));

    // Creates saving options checkboxes for the bottom box
    QCheckBox *pngButton = new QCheckBox("PNG");
    QCheckBox *pdfButton = new QCheckBox("PDF");
    QCheckBox *wordButton = new QCheckBox("Doc");
    QCheckBox *txtButton = new QCheckBox("txt");

    // Create the save button of the bottom box
    QPushButton *saveButton = new QPushButton(tr("Save"));
    // Connect the save button the save slot, that signals that the save procedures should start
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveSlot()));
    // Adds tooltip to the save button
    saveButton->setToolTip(tr("Push to save the result of the ciphering process."));

    // Add the widgets to the bottom box layout
    bottomBoxLayout->addWidget(formatLabel);
    bottomBoxLayout->addWidget(pngButton);
    bottomBoxLayout->addWidget(pdfButton);

    if (type != MainWindow::Image) bottomBoxLayout->addWidget(wordButton);
    if (type == MainWindow::All) bottomBoxLayout->addWidget(txtButton);

    bottomBoxLayout->addStretch();
    bottomBoxLayout->addWidget(saveButton);

    // Assign bottom box layout to the bottom box
    bottomBox->setLayout(bottomBoxLayout);


    // Assign the bottom box to the main layout
    mainLayout->addWidget(bottomBox);

    // Returns the main layout
    return mainLayout;
}

void MainWindow::createChineseCodeTab() {
    // Create chinese code widget
    chineseCode = new QWidget;

    // Sets the layout for the chinese code
    chineseCode->setLayout(configCodecAreaWidgets(MainWindow::Image));

    // Do the configuration of the font for the chinese code text box
    QFont font;
    font.setFamily("Chines & Internacional");
    font.setCapitalization(QFont::AllUppercase);
    font.setPointSize(mainTextBox->font().pointSize() + 20);

    // Recovers the text box for the chinese code widget
    QTextEdit *currentTextBox = chineseCode->findChild<QTextEdit *>();

    // Sets the font for the text box
    currentTextBox->setFont(font);
}

void MainWindow::createAngularCodeTab() {
    // Create angular code widget
    angularCode = new QWidget;

    // Sets the layout for the angular code
    angularCode->setLayout(configCodecAreaWidgets(MainWindow::Image));

    // Do the configuration of the font for the angular code text box
    QFont font;
    font.setFamily("Chines & Internacional");
    font.setCapitalization(QFont::AllLowercase);
    font.setPointSize(mainTextBox->font().pointSize() + 20);

    // Recovers the text box for the angular code widget
    QTextEdit *currentTextBox = angularCode->findChild<QTextEdit *>();

    // Sets the font for the text box
    currentTextBox->setFont(font);
}

void MainWindow::createReverseAlphabetTab() {
    // Create chinese code widget
    reverseAlphabet = new QWidget;

    // Sets the layout for the chinese code
    reverseAlphabet->setLayout(configCodecAreaWidgets(MainWindow::All));
}

void MainWindow::saveAsPNG(QTextEdit *textEdit, QString fileName) {
    // Set text width
    textEdit->document()->setTextWidth(580);

    // Store original font size
    int fontSize = textEdit->font().pointSize();

    // Copy original font
    QFont aux_font = textEdit->font();

    // Add 10pt to original font size
    aux_font.setPointSize(fontSize + 15);
    textEdit->setFont(aux_font);

    // Create image by calculating the size from QTextEdit
    QImage *code = new QImage(
            QSize(textEdit->document()->size().width() * 1.05, textEdit->document()->size().height() * 1.05),
            QImage::Format_ARGB32_Premultiplied);

    // Fill image with white
    code->fill(Qt::white);

    // Initialise QPainter
    QPainter *painter = new QPainter(code);

    // Set QPainter font
    painter->setFont(textEdit->font());
    // Set text colour
    painter->setPen(mainTextBox->textColor());

    // Draw text with painter to image (The text is justified, vertically centred and using word wrap to code->rect())
    painter->drawText(
            QRect(textEdit->document()->size().width() * 0.05 / 2, textEdit->document()->size().height() * 0.05 / 2,
                  textEdit->document()->size().width(), textEdit->document()->size().height()),
            Qt::AlignJustify | Qt::AlignVCenter | Qt::TextWordWrap, textEdit->toPlainText());

    // Save image to file
    code->save(fileName + ".png", "PNG");

    // Restore original font size
    aux_font.setPointSize(fontSize);
    textEdit->setFont(aux_font);
}

void MainWindow::saveAsPDF(QTextEdit *textEdit, QString fileName) {
    QTextDocument document;
    document.setPlainText(textEdit->toPlainText());

    // Set document size
//        textEdit->document()->setTextWidth(580);
    // TODO: PASSAR PARA TAMANHOS A4 (WIDTH) ESPECIALMENTE SE O TEXTO FOR MUITO GRANDE (HEIGHT)

    // Store original font size
    int fontSize = textEdit->font().pointSize();

    // Copy original font
    QFont aux_font = textEdit->font();

    // Add 10pt to original font size
    aux_font.setPointSize(textEdit->font().pointSize());
    aux_font.setPointSize(15);
    textEdit->setFont(aux_font);

    // Calculate paper sizes
    QSizeF pageSize = textEdit->document()->size();
    pageSize.setWidth(pageSize.width() * 1.05);
    pageSize.setHeight(pageSize.height() * 1.05);


    pageSize.setWidth(QPrinter::A4);
    pageSize.setHeight(QPrinter::A4);
//        textEdit->document()->setTextWidth(pageSize.width() * 0.95);
    // Set document size
//        textEdit->document()->setPageSize(pageSize);

    // Printer options
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName + ".pdf");
    printer.setFullPage(true);
    printer.setPageSize(QPrinter::A4);
    printer.setPageMargins(20, 20, 20, 20, QPrinter::Millimeter);
//        printer.setPageSize(QPageSize(pageSize, QPageSize::Point, QString(), QPageSize::ExactMatch));
    printer.setOutputFileName(fileName + ".pdf");

    // Print PDF file
//        textEdit->document()->setPageSize(printer.pageRect().size()); // To ignore page numbers
//        textEdit->document()->print(&printer);

//        document.setPageSize(printer.pageRect().size() * 0.5); // To ignore page numbers
//        document.setPageSize(printer.paperRect().size());
    document.setDefaultFont(textEdit->font());
    printf("%d\n", textEdit->font().pointSize());
    document.setPageSize(QPageSize::definitionSize(QPageSize::A4));
//        document.setPageSize(QSizeF(QSize(210, 297, QPrinter::Millimeter)));
    document.print(&printer);

    // Restore original font size
    aux_font.setPointSize(fontSize);
    textEdit->setFont(aux_font);
}

void MainWindow::saveAsDoc(QTextEdit *textEdit, QString fileName) {
    QTextDocument *textDocument = textEdit->document();

    QTextDocumentWriter writer;
    writer.setFormat("ODT");
    writer.setFileName(fileName + ".odt");
    writer.write(textDocument);
}

void MainWindow::saveAsTxt(QTextEdit *textEdit, QString fileName) {
    // Open file to write
    QFile file(fileName + ".txt");
    file.open(QFile::WriteOnly);

    // Initialise text stream
    QTextStream write(&file);

    // Write to file
    write << textEdit->toPlainText();
    write.flush();

    // Close file
    file.close();
}

// TODO: if file exists ask to replace; Create protections and checks (ex: check if file was successfully saved)
void MainWindow::saveFiles() {
    // Create new file dialog, named "Save as" and starting at the home directory
    QFileDialog *saveDialog = new QFileDialog(this, tr("Save as..."), QDir::homePath(), "");

    saveDialog->setAcceptMode(QFileDialog::AcceptSave);
    saveDialog->setFileMode(QFileDialog::AnyFile);

    QStringList formats;
    formats << "Any file (*.*)";
    //            << "Portable Network Graphics (*.png)"
    //            << "Portable Document Format (*.pdf)"
    //            << "Word Document (*.doc, *.docx)"
    //            << "Text file (*.txt)";

    //saveDialog->setNameFilters(formats);

    // Force use of OS native file dialog
    saveDialog->setOption(QFileDialog::DontUseNativeDialog, false);

    // Get intended name of file
    QString fileName;
    if (saveDialog->exec()) {
        fileName = saveDialog->selectedFiles().at(0);
    }

    // TODO: Confirmar (o nome do objeto a passar tem de ser definido com o método setObjectName)
    QList<QCheckBox *> savingOptionsCheckBoxes = codecAreaBox->currentWidget()->findChildren<QCheckBox *>();

    // Get QTextEdit box
    QTextEdit *textEdit = codecAreaBox->currentWidget()->findChild<QTextEdit *>();

    // Save as PNG
    if (savingOptionsCheckBoxes.at(savingFormats::PNG)->checkState() == Qt::Checked) {
        saveAsPNG(textEdit, fileName);
    }

    // Save as PDF
    if (savingOptionsCheckBoxes.at(savingFormats::PDF)->checkState() == Qt::Checked) {
        saveAsPDF(textEdit, fileName);
    }

    // Save as odt
    if (savingOptionsCheckBoxes.size() >= 3 &&
        savingOptionsCheckBoxes.at(savingFormats::doc)->checkState() == Qt::Checked) {
        saveAsDoc(textEdit, fileName);
    }

    // Save as txt
    if (savingOptionsCheckBoxes.size() == 4 &&
        savingOptionsCheckBoxes.at(savingFormats::txt)->checkState() == Qt::Checked) {
        saveAsTxt(textEdit, fileName);
    }
}

/** Public slots **/
void MainWindow::runEncodeSlot() {
    emit startEncode();
}

/** Private slots **/
// Slot to edit font
void MainWindow::changeFontSlot() {
    bool assert_font;

    QFont font = QFontDialog::getFont(&assert_font, mainTextBox->font(), this);

    if (assert_font) setTextFont(font);
}


// Slot to edit font
void MainWindow::changeColourSlot() {
    QColor colour = QColorDialog::getColor(mainTextBox->textColor(), this);

    if (colour.isValid()) setTextColour(colour);
}

// Slot to run the save procedures
void MainWindow::saveSlot() {
    saveFiles();
}

// Creates the language menu entries dynamically depending on the existing translations
void MainWindow::createLanguageMenu() {
    // Creates the language menu
    changeLanguageMenu = new QMenu(this);

    // Created the translation action group
    QActionGroup *translationActionGroup = new QActionGroup(this);

    // Connect the translation actions to the switch language slot
    connect(translationActionGroup, SIGNAL(triggered(QAction * )), this, SLOT(switchLanguageSlot(QAction * )));

    // Define translations path
    languageTranslationsPath = QApplication::applicationDirPath();
    QDir dir(languageTranslationsPath);

    // Get list of translation file names
    QStringList fileNames = dir.entryList(QStringList("ScoutTalker_*.qm"));

    // Loop translation files list
    for (int i = 0; i < fileNames.size(); ++i) {
        // Get locale extracted by filename
        QString locale = fileNames[i]; // "TranslationExample_pt_PT.qm"
        locale.truncate(locale.lastIndexOf('.')); // "TranslationExample_pt_PT"
        locale.remove(0, locale.indexOf('_') + 1); // "pt"

        // Language name and flag
        QString language = QLocale::languageToString(QLocale(locale).language());
        QIcon flag(QString(":%1.png").arg(locale));

        QAction *action = new QAction(flag, QString("&%1").arg(language), this); // TODO: Find how to translate this
        action->setCheckable(true);
        action->setData(locale);

        changeLanguageMenu->addAction(action);
        translationActionGroup->addAction(action);

        if (language == "English") {
            action->setChecked(true);
        }
    }
}

// Language switch slot
void MainWindow::switchLanguageSlot(QAction *action) {
    // Load the language dependant on the action content
    QString locale = action->data().toString();

    // Load translators
    translatorMainWindow.load("ScoutTalker_" + locale + ".qm");
    translatorQt.load("qt_" + locale + ".qm");

    // Translate MainWindow texts to the selected language
    translateMainWindow();
}

// Applies text and translations to MainWindow
void MainWindow::translateMainWindow() {
    // Menus text
    changeLanguageMenu->setTitle(tr("&Language"));
    changeLanguageMenu->setToolTip(tr("Language selection menu."));

    // Actions text
    mainWindowActions[changeFontAction]->setText(tr("Change &Font"));
    mainWindowActions[changeFontAction]->setToolTip(tr("Edit application font."));

    mainWindowActions[changeFontColourAction]->setText(tr("Change Font &Colour"));
    mainWindowActions[changeFontColourAction]->setToolTip(tr("Edit application font colour."));

    mainWindowActions[aboutScoutTalkerAction]->setText(tr("About &Scout Talker"));
    mainWindowActions[aboutScoutTalkerAction]->setToolTip(tr("Show information about Scout Talker."));

    mainWindowActions[aboutQtAction]->setText(tr("About &Qt"));
    mainWindowActions[aboutQtAction]->setToolTip(tr("Show information about Qt."));

    mainWindowActions[exitAction]->setText(tr("E&xit"));
    mainWindowActions[exitAction]->setToolTip(tr("Quit Scout Talker."));

    // Buttons text
    mainMenuButton->setToolTip(tr("Opens Scout Talker main menu."));

    helpButton->setText(tr("Help"));
    helpButton->setToolTip(tr("Push to show help for the current cipher (NOT IMPLEMENTED)."));
}
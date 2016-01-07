#include "window.h"
#include "scouttalker.h"
#include <QApplication>
#include <QPushButton>

//Verificar se é para manter
#include <QTabWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QFont>
#include <QSpacerItem>
#include <QTextEdit>
#include <QCheckBox>
#include <QMenu>
#include <QSize>
#include <QMessageBox>

Window::Window(QWidget *parent) : QWidget(parent)
{
    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // Creates titleGroupBox widget
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
    // Sets main layout as the window layout
    setLayout(mainLayout);

    // Set the window title
    setWindowTitle(tr("Scout Talker"));
}

Window::~Window()
{

}

// Method to create the main title
void Window::createTitle()
{
    // Creates the group box
    titleGroupBox = new QGroupBox();

    // Creates the Horizontal Box Layout for the group box
    QHBoxLayout *layout = new QHBoxLayout;

    // Creates the main title of the program label
    QLabel *mainTitle = new QLabel(tr("Scout Talker"));

    // Center aligns the label
    mainTitle->setAlignment(Qt::AlignCenter);

    QFont font;
    font.setFamily(font.defaultFamily()); // Sets the font as the default one
    font.setPointSize(20); // Sets font size
    font.setBold(true); // Sets font as bold

    // Changes the label font
    mainTitle->setFont(font);

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


// Method to create the Main Menu
void Window::createMainMenu()
{
    // Creates the push button main menu
    QMenu *mainMenu = new QMenu();

    //Add ABout Scout Talker action to the menu
    QAction *aboutST = mainMenu->addAction(tr("About &Scout Talker"));
    // Connects the action to the stInfo slot
    connect(aboutST, SIGNAL(triggered()), this, SLOT(stInfo()));

    // Add About Qt action to the menu
    QAction *aboutQt = mainMenu->addAction(tr("About &Qt"));
    // Sets icon for the action
    aboutQt->setIcon(QIcon(":/icons/Qt_logo_2015.png"));
    // Connects the action to the qtInfo slot
    connect(aboutQt, SIGNAL(triggered()), this, SLOT(qtInfo()));

    // Add Exit action to the menu
    QAction *exitAction = mainMenu->addAction(tr("E&xit"));
    // Sets shortcut for the exit action
    exitAction->setShortcuts(QKeySequence::Quit);
    // Connects the exit action to the quit slot
    connect(exitAction, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));


    // Creates push button that will contain the main logo
    mainMenuButton = new QPushButton();

    // Sets button size
    mainMenuButton->setFixedSize(100, 100);

    // Sets button icon and size
    mainMenuButton->setIcon(QIcon(":/icons/Qt_logo_2015.png"));
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
void Window::createMainTextBox()
{
    mainTextBox = new QTextEdit();
    mainTextBox->setText(tr("Insert text to encode..."));
}

// Method to create the codec area box
void Window::createCodecAreaBox()
{
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

QVBoxLayout* Window::configCodecAreaWidgets()
{
    // Creates the main outter layout for a codec tab
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // Top Box
    QGroupBox *topBox = new QGroupBox;
    // Top box layout
    QHBoxLayout *topBoxLayout = new QHBoxLayout;

    // Creates the encode button for the top box
    QPushButton *encodeButton = new QPushButton(tr("Cipher"));
    // Connect the encode button the run encode slot, that signals that the cipher should start
    connect(encodeButton, SIGNAL(clicked()), this, SLOT(runEncode()));

    // Creates the help button for the top box
    QPushButton *helpButton = new QPushButton(tr("Help"));

    // Add the widgets to the top box layout
    topBoxLayout->addWidget(encodeButton);
    topBoxLayout->addWidget(helpButton);

    // Assign top box layout to the top box
    topBox->setLayout(topBoxLayout);

    // Add tob box to the main layout
    mainLayout->addWidget(topBox);


    // Middle Box
    // Creates the text box
    QTextEdit *codecTextBox = new QTextEdit();

    // Adds the text box to the main layout
    mainLayout->addWidget(codecTextBox);


    // Bottom Box
    QGroupBox *bottomBox = new QGroupBox;
    // Bottom box layout
    QHBoxLayout *bottomBoxLayout = new QHBoxLayout;

    // Creates the label for the saving options of the bottom box
    QLabel *formatLabel = new QLabel(tr("Format:"));

    // Creates saving options checkboxes for the bottom box
    QCheckBox *pdfButton = new QCheckBox(tr("PDF"));
    QCheckBox *wordButton = new QCheckBox(tr("Text file"));
    QCheckBox *pngButton = new QCheckBox(tr("PNG"));

    // Create the save button of the bottom box
    QPushButton *saveButton = new QPushButton(tr("Save"));

    // Add the widgets to the bottom box layout
    bottomBoxLayout->addWidget(formatLabel);
    bottomBoxLayout->addWidget(pdfButton);
    bottomBoxLayout->addWidget(wordButton);
    bottomBoxLayout->addWidget(pngButton);
    bottomBoxLayout->addWidget(saveButton);

    // Assign bottom box layout to the bottom box
    bottomBox->setLayout(bottomBoxLayout);


    // Assign the bottom box to the main layout
    mainLayout->addWidget(bottomBox);

    // Returns the main layout
    return mainLayout;
}

void Window::createChineseCodeTab()
{
    // Create chinese code widget
    chineseCode = new QWidget;

    // Sets the layout for the chinese code
    chineseCode->setLayout(configCodecAreaWidgets());

    // Do the configuration of the font for the chinese code text box
    QFont font;
    font.setFamily("Chines & Internacional");
    font.setCapitalization(QFont::AllUppercase);
    font.setPointSize(20);

    // Recovers the text box for the chinese code widget
    QTextEdit *currentTextBox = chineseCode->findChild<QTextEdit *>();

    // Sets the font for the text box
    currentTextBox->setFont(font);
}

void Window::createAngularCodeTab()
{
    // Create angular code widget
    angularCode = new QWidget;

    // Sets the layout for the angular code
    angularCode->setLayout(configCodecAreaWidgets());

    // Do the configuration of the font for the angular code text box
    QFont font;
    font.setFamily("Chines & Internacional");
    font.setCapitalization(QFont::AllLowercase);
    font.setPointSize(28);

    // Recovers the text box for the angular code widget
    QTextEdit *currentTextBox = angularCode->findChild<QTextEdit *>();

    // Sets the font for the text box
    currentTextBox->setFont(font);
}

void Window::createReverseAlphabetTab()
{
    // Create chinese code widget
    reverseAlphabet = new QWidget;

    // Sets the layout for the chinese code
    reverseAlphabet->setLayout(configCodecAreaWidgets());
}

// Slot to create the about Qt window
void Window::qtInfo()
{
    QApplication::aboutQt();
}

Window::availableTabs Window::getTab()
{
    return availableTabs(codecAreaBox->currentIndex());
}

QString Window::getToEncodeString()
{
    return mainTextBox->toPlainText();
}

void Window::setEncodedString(QString string)
{
    // Confirmar (o nome do objeto a passar tem de ser definido com o método setObjectName
    QTextEdit *currentTextBox = codecAreaBox->currentWidget()->findChild<QTextEdit *>();
    currentTextBox->setText(string);
}

// Slots
void Window::runEncode()
{
    emit startEncode();
}

void Window::stInfo()
{
    QMessageBox::about(this, QString(tr("About Scout Talker")), QString("<p><b>About Scout Talker:</b></p>\n\nFeito por Diana Capela & João Santos.\nVersão 15000!"));
}

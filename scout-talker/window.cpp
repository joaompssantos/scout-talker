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
    createTitle();
    createMainTextBox();
    createCodecAreaBox();

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(titleGroupBox);
    mainLayout->addWidget(mainTextBox);
    mainLayout->addWidget(codecAreaBox);

    // Create a push button
    quitButton = new QPushButton("Quit", this);
    // Link push button to make quit
    connect(quitButton, SIGNAL (clicked(bool)), QApplication::instance(), SLOT (quit()));

    mainLayout->addWidget(quitButton);

    mainLayout->setMargin(25);
    setLayout(mainLayout);
    setWindowTitle(tr("Scout Talker"));
}

Window::~Window()
{

}

void Window::createTitle()
{
    // Creates the group box
    titleGroupBox = new QGroupBox();
    // Creates the Horizontal Box Layout for the group box
    QHBoxLayout *layout = new QHBoxLayout;

    // Creates the main title of the program label
    QLabel *mainTitle = new QLabel("Scout Talker");
    // Center aligns the label
    mainTitle->setAlignment(Qt::AlignCenter);
    // Changes the label font
    mainTitle->setFont(QFont("Calibri", 20, QFont::Bold));

    // Creates the main menu
    createMainMenu();

    // Creates push button that will contain the main logo
    QPushButton *button = new QPushButton();
    // Sets button size
    button->setFixedSize(100, 100);
    // Sets button icon and size
    button->setIcon(QIcon(":/icons/Qt_logo_2015.png"));
    button->setIconSize(QSize(95, 95));
    // Changes button style sheet to remove the menu indicator and border
    button->setStyleSheet("QPushButton::menu-indicator {image: none;}"
                          "QPushButton {border: 0px solid #8f8f91;}");
    // Sets hovering cursor for the button
    button->setCursor(Qt::PointingHandCursor);
    // Adds the main menu to the push button
    button->setMenu(mainMenu);

    // Set alignment of the layout
    layout->setAlignment(Qt::AlignCenter);
    // Add an empty space with the size of 50
    layout->insertSpacing(0, 50);
    // Add title widget to the layout
    layout->addWidget(mainTitle);
    // Add space between widgets
    layout->addSpacing(25);
    // Add button to the layout
    layout->addWidget(button);
    // Add an empty space with the size of 50
    layout->addSpacing(50);

    // Sets the group box layout
    titleGroupBox->setLayout(layout);
    // Command to remove border of Group Box
    titleGroupBox->setStyleSheet("QGroupBox {border: 0px solid gray;}");
}

void Window::createMainTextBox()
{
    mainTextBox = new QTextEdit();
    mainTextBox->setText("Insert text to encode...");
    //mainTextBox->setStyleSheet("QTextEdit {border: 0px solid gray;}");
}

void Window::createCodecAreaBox()
{
    codecAreaBox = new QTabWidget();
    // Style for the tabs
    codecAreaBox->setStyleSheet(""
                                "QTabWidget::pane { /* The tab widget frame */"
                                "border: 1px solid gray;"
                                "}"
                                "");

    QWidget *cod_chines = new QWidget;
    createChineseCodeBox();
    cod_chines->setLayout(chineseCode);
    codecAreaBox->addTab(cod_chines, tr("Alfabeto Invertido"));
}

void Window::createChineseCodeBox()
{
    chineseCode = new QVBoxLayout;

    // Top Box
    QGroupBox *top = new QGroupBox;
    QHBoxLayout *layout = new QHBoxLayout;

    // Mudar para butões universais (os mesmos em todas as tabs)
    QPushButton *encode = new QPushButton("Codificar");

    connect(encode, SIGNAL(clicked(bool)), this, SLOT(runEncode()));

    QPushButton *help = new QPushButton("Ajuda");

    layout->addWidget(encode);
    layout->addWidget(help);

    top->setLayout(layout);

    chineseCode->addWidget(top);

    // Middle Box
    // Mudar para ser universais (os mesmos em todas as tabs)
    textBox = new QTextEdit();

    QFont f;
//    f.setFamily("Chines & Internacional");
//    f.setFamily(f.defaultFamily());
    f.setPointSize(24);

    textBox->setFont(f);
    chineseCode->addWidget(textBox);

    // Bottom Box
    QGroupBox *bottom = new QGroupBox;
    layout = new QHBoxLayout;

    // Mudar para butões universais (os mesmos em todas as tabs)
    QPushButton *save = new QPushButton("Guardar");

    QCheckBox *pdfButton = new QCheckBox("PDF");
    QCheckBox *wordButton = new QCheckBox("Text file");
    QCheckBox *pngButton = new QCheckBox("PNG");

    QLabel *format = new QLabel("Formato: ");

    layout->addWidget(format);
    layout->addWidget(pdfButton);
    layout->addWidget(wordButton);
    layout->addWidget(pngButton);
    layout->addWidget(save);

    bottom->setLayout(layout);

    chineseCode->addWidget(bottom);
}

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
    textBox->setText(string);
}

void Window::runEncode()
{
    emit startEncode();
}

void Window::stInfo()
{
    QMessageBox::about(this, QString(tr("About Scout Talker")), QString("<p><b>About Scout Talker:</b></p>\n\nFeito por Diana Capela & João Santos.\nVersão 15000!"));
}

void Window::createMainMenu()
{
    // Creates the push button main menu
    mainMenu = new QMenu();
    //Add ABout Scout Talker action to the menu
    QAction *aboutST = mainMenu->addAction("About &Scout Talker");
    // Connects the action to the stInfo slot
    connect(aboutST, SIGNAL(triggered()), this, SLOT(stInfo()));
    // Add About Qt action to the menu
    QAction *aboutQt = mainMenu->addAction("About &Qt");
    // Sets icon for the action
    aboutQt->setIcon(QIcon(":/icons/Qt_logo_2015.png"));
    // Connects the action to the qtInfo slot
    connect(aboutQt, SIGNAL(triggered()), this, SLOT(qtInfo()));
    // Add Exit action to the menu
    QAction *exitAction = mainMenu->addAction("E&xit");
    // Sets shortcut for the exit action
    exitAction->setShortcuts(QKeySequence::Quit);
    // Connects the exit action to the quit slot
    connect(exitAction, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));
}

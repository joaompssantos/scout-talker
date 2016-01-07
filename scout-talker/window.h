#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "scouttalker.h"

class QPushButton;
class QLabel;
class QVBoxLayout;
class QMenuBar;
class QMenu;
class QAction;
class QGroupBox;
class QTextEdit;
class QTabWidget;
class QMenu;
class Window : public QWidget
{
    Q_OBJECT

public:
    // Variables
    enum availableTabs{Numeral, Angular, Chinese};

    // Methods / Functions
    Window(QWidget *parent = 0);
    ~Window();

    availableTabs getTab();
    QString getToEncodeString();
    void setEncodedString(QString string);
private:
    // Variables
    QPushButton *quitButton;
    QGroupBox *titleGroupBox;
    QTextEdit *mainTextBox;
    QTabWidget *codecAreaBox;
    QVBoxLayout *chineseCode, *angularCode, *numeralCode;
    QMenu *mainMenu;

    QTextEdit *textBox;

    // Methods / Functions
    void createTitle();
    void createMainTextBox();
    void createCodecAreaBox();
    void createChineseCodeBox();
    void createAngularCodeBox();
    void createNumeralCodeBox();
    void createMainMenu();
signals:
    void startEncode();
public slots:
    void runEncode();
private slots:
    void qtInfo();
    void stInfo();
};

#endif // SCOUTTALKER_H

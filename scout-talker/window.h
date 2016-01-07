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
class QCheckBox;
class Window : public QWidget
{
    Q_OBJECT

public:
    // Variables
    enum availableTabs{ChineseCode, AngularCode, ReverseAlphabet};

    // Methods / Functions
    Window(QWidget *parent = 0);
    ~Window();

    availableTabs getTab();
    QString getToEncodeString();
    void setEncodedString(QString string);
private:
    // Variables
    QGroupBox *titleGroupBox;
    QPushButton *mainMenuButton;
    QTextEdit *mainTextBox;
    QTabWidget *codecAreaBox;
    QWidget *chineseCode;
    QWidget *angularCode;
    QWidget *reverseAlphabet;

    // Methods / Functions
    void createTitle();
    void createMainMenu();
    void createMainTextBox();
    void createCodecAreaBox();
    QVBoxLayout *configCodecAreaWidgets();
    void createChineseCodeTab();
    void createAngularCodeTab();
    void createReverseAlphabetTab();
signals:
    void startEncode();
public slots:
    void runEncode();
private slots:
    void qtInfo();
    void stInfo();
};

#endif // SCOUTTALKER_H

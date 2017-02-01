#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "scouttalker.h"

class QPushButton;
class QGroupBox;
class QTextEdit;
class QVBoxLayout;
class Window : public QWidget
{
    Q_OBJECT

public:
    // Variables
    // Types of encoding available
    enum availableTabs{ChineseCode, AngularCode, ReverseAlphabet, Last};

    // File saving types
    enum savingTypes{All, Font, Image};

    // Methods / Functions
    Window(QWidget *parent = 0);
    ~Window();

    // Getters
    availableTabs getTab();
    QString getToEncodeString();

    // Setters
    void setEncodedString(QString string);
    void setTextColour(QColor colour);
    void setTextFont(QFont font);
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
    QVBoxLayout *configCodecAreaWidgets(int type);
    void createChineseCodeTab();
    void createAngularCodeTab();
    void createReverseAlphabetTab();

    void saveFiles();
signals:
    void startEncode();
public slots:
    void runEncodeSlot();
private slots:
    void qtInfoSlot();
    void stInfoSlot();
    void changeFontSlot();
    void changeColourSlot();
    void saveSlot();
};

#endif // SCOUTTALKER_H

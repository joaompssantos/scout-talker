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

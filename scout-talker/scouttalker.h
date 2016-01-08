#ifndef SCOUTTALKER_H
#define SCOUTTALKER_H

#include <QObject>

class QString;
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

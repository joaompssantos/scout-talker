#include "scouttalker.h"
#include "window.h"
#include <QChar>

ScoutTalker::ScoutTalker(Window *w, QObject *parent) : QObject(parent)
{
    toEncodeString = new QString("");
    encodedString = new QString("");
    window = w;

    connect(window, SIGNAL(startEncode()), this, SLOT(encodeSlot()));
}

void ScoutTalker::clearStrings()
{
    toEncodeString->clear();
    encodedString->clear();
}

void ScoutTalker::encode()
{
    // Clears the class strings
    clearStrings();

    // Read the string to encode from the window object
    toEncodeString->append(window->getToEncodeString());

    // Gets current tab from the window object
    Window::availableTabs currentTab = window->getTab();

    switch (currentTab) {
    case Window::ChineseCode:
        // Do the procedures to perform the chinese code
        encodeChineseCode();
        break;
    case Window::AngularCode:
        // Do the procedures to perform the angular code
        encodeAngularCode();
        break;
    case Window::ReverseAlphabet:
        // Do the procedures to perform the reverse alphabet
        encodeReverseAlphabet();
        break;
    default:
        break;
    }

    // Pushes the resulting string to the window object
    window->setEncodedString(*encodedString);
}

void ScoutTalker::encodeChineseCode()
{
    encodedString->append(toEncodeString);
}

void ScoutTalker::encodeAngularCode()
{
    encodedString->append(toEncodeString);
}

void ScoutTalker::encodeReverseAlphabet()
{
    int nChars = toEncodeString->count();
    encodedString->append(toEncodeString);

    for (int i = 0; i < nChars; i++)
    {
        QChar currentCharacter = (*toEncodeString)[i];

        if (currentCharacter.unicode() >= 0x41 && currentCharacter.unicode() <= 0x5A)
        {
            (*encodedString)[i] = (QChar) (0x9B - currentCharacter.unicode());
        }
        else if (currentCharacter.unicode() >= 0x61 && currentCharacter.unicode() <= 0x7A)
        {
            (*encodedString)[i] = (QChar) (0xDB - currentCharacter.unicode());
        }
    }
}

void ScoutTalker::encodeSlot()
{
    encode();
}

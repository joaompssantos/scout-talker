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

void ScoutTalker::encode()
{
    clearStrings();

    toEncodeString->append(window->getToEncodeString());
    Window::availableTabs currentTab = window->getTab();

    if(currentTab == Window::Numeral)
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

    window->setEncodedString(*encodedString);
}

void ScoutTalker::encodeSlot()
{
    encode();
}

void ScoutTalker::clearStrings()
{
    toEncodeString->clear();
    encodedString->clear();
}

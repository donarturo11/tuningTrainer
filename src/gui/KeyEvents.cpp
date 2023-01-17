#include <QKeySequence>
#include "gui/KeyEvents.h"
#include "MainWindow.h"

namespace GUI {

/* ------------ */
KeyEvents::KeyEvents(QWidget *parent) : QWidget(parent)
{
   // shortcut = new QKeySequence(parent);
   int keyCodes[] = {  
       Qt::Key_Q,
       Qt::Key_W,
       Qt::Key_E,
       Qt::Key_R,
       Qt::Key_5,
       Qt::Key_T,
       Qt::Key_6,
       Qt::Key_Y,
       Qt::Key_U,
       Qt::Key_8,
       Qt::Key_I,
       Qt::Key_9,
       Qt::Key_O,
       Qt::Key_0,
       Qt::Key_P,
       91 // "{" code
   };
   
   for (int code : keyCodes) {
       addShortcut(code);
       addName(code);
   }
}

KeyEvents::~KeyEvents()
{

}

void KeyEvents::addShortcut(int code)
{
    int index=KeyEvents::shortcutIndex;
    keyMap[code]=index;
    KeyEvents::shortcutIndex++;
}

void KeyEvents::addName(int code)
{
    QString keyName=QKeySequence(code).toString();
    keyNames.push_back(keyName);
}

void KeyEvents::sendKeyPressed(int code)
{
    if (keyMap.find(code)!=keyMap.end())
        emit keyPressed(keyMap[code]);
}


void KeyEvents::sendKeyReleased(int code)
{
    if (keyMap.find(code)!=keyMap.end())
        emit keyReleased(keyMap[code]);
}



} // namespace GUI


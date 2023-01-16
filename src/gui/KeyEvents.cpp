#include "gui/KeyEvents.h"
#include "MainWindow.h"

namespace GUI {

/* ------------ */
KeyEvents::KeyEvents(QWidget *parent) : QWidget(parent)
{
    shortcut = new QShortcut(parent);
    shortcut->setKey(Qt::Key_Q);
    shortcut->setContext(Qt::ApplicationShortcut);
    shortcut->setEnabled(1);
}

KeyEvents::~KeyEvents()
{

}

void KeyEvents::sendKeyPressed(int code)
{
    qDebug() << "Key " << code << " pressed ";
}


void KeyEvents::sendKeyReleased(int code)
{
    qDebug() << "Key " << code << " released";
}



} // namespace GUI


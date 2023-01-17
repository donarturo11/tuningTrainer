#include "gui/ControllerWidget.h"
#include "gui/controllerwidget/Keyboard.h"
#include "gui/controllerwidget/KeyButton.h"
#include "gui/load_style.h"

namespace GUI {
/* --------------- */
Keyboard::Keyboard(QWidget *parent) : QWidget(parent)
{
    GUI::load_style(this, ":/qss/keyboard.qss");
}

Keyboard::~Keyboard()
{
}

void Keyboard::initKey(bool semitone)
{
    _keys.push_back(new KeyButton(this, semitone));
    auto keyButton = getKeyLast();
    auto events = ((ControllerWidget*) parentWidget())->getKeyEvents();
    int index = keyButton->getIndex();
    QString keyName = events->getNameByIndex(index);
    keyButton->setText(keyName);
    connect(keyButton, &KeyButton::noteOn, this, &Keyboard::sendNoteOn );
    connect(keyButton, &KeyButton::noteOff, this, &Keyboard::sendNoteOff );
}

void Keyboard::sendNoteOn(int index)
{
    emit noteOn(index);
}   
void Keyboard::sendNoteOff(int index)
{
    emit noteOff(index);
}

/* --------------- */
} // namespace GUI

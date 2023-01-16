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
    int idx = KeyButton::index;
    keys.push_back(new KeyButton(this, semitone));
    connect(keys[idx], &KeyButton::noteOn, this, &Keyboard::keyPressed );
    connect(keys[idx], &KeyButton::noteOff, this, &Keyboard::keyReleased );
}

void Keyboard::keyPressed(int index)
{
    emit noteOn(index);
}   
void Keyboard::keyReleased(int index)
{
    emit noteOff(index);
}

/* --------------- */
} // namespace GUI

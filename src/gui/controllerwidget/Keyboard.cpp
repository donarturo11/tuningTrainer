#include "gui/controllerwidget/Keyboard.h"
#include "gui/controllerwidget/KeyButton.h"

namespace GUI {
/* --------------- */
Keyboard::Keyboard(QWidget *parent) : QWidget(parent)
{
    initKey();
    initKey(1);
    initKey(0);
    //static int KeyButton::index=0;
}

Keyboard::~Keyboard()
{
}

void Keyboard::initKey(bool semitone)
{
    int idx = KeyButton::index;
    keys.push_back(new KeyButton(this));
    //connect(keys[idx], SIGNAL(pressed(), this, SLOT(keyPressed(idx)) );
    //connect(keys[idx], SIGNAL(released(), this, SLOT(keyReleased(idx)) );
    keys[idx]->show();
    fprintf(stderr, "Key number: %i added\n", idx);
    KeyButton::index++;
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

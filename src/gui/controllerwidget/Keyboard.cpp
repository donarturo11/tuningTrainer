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
    keys.push_back(new KeyButton(this, semitone));
    fprintf(stderr, "Build key at %i\n", keys[idx]->getIndex());
    connect(keys[idx], &KeyButton::noteOn, this, &Keyboard::keyPressed );
    connect(keys[idx], &KeyButton::noteOff, this, &Keyboard::keyReleased );
    fprintf(stderr, "Key number: %i added\n", idx);
    fprintf(stderr, "Is semitone: %i\n", keys[idx]->isSemitone());
    KeyButton::index++;
}

void Keyboard::initConnections()
{
    //for (auto key : keys) {
    //    connect(key, SIGNAL(noteOff)
    //}
}

void Keyboard::keyPressed(int index)
{
    fprintf(stderr, "Key %i pressed\n", index);
    emit noteOn(index);
}   
void Keyboard::keyReleased(int index)
{
    fprintf(stderr, "Key %i released\n", index);
    emit noteOff(index);
}

/* --------------- */
} // namespace GUI

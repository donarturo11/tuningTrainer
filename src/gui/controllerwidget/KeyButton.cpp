#include "gui/controllerwidget/KeyButton.h"

namespace GUI {

//KeyButton::index = 0;
/* --------------- */
KeyButton::KeyButton(QWidget *parent, bool semitone) : QPushButton(parent)
{
    setSemitone(semitone);
    init();
    connect(this, SIGNAL(pressed()), this, SLOT(sendNoteOn()));
    connect(this, SIGNAL(released()), this, SLOT(sendNoteOff()));
    
}

KeyButton::~KeyButton()
{
}

void KeyButton::init()
{
    btn_index = index;
    int multi=1;
    if (isSemitone()) multi = 1;
    else multi=2;
    int width = 30*multi;
    int height = 240/multi;
    setGeometry(index*width, 0, width, height);
}

void KeyButton::sendNoteOn()
{
    int idx = getIndex();
    emit noteOn(idx);
}
void KeyButton::sendNoteOff()
{
    int idx = getIndex();
    emit noteOff(idx);
}

/* --------------- */

} // namespace GUI
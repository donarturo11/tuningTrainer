#include "gui/controllerwidget/KeyButton.h"
#include <iostream>
#include <QWidget>
#include <QDebug>
namespace GUI {

//KeyButton::index = 0;
/* --------------- */
KeyButton::KeyButton(QWidget *parent, bool semitone) : QPushButton(parent)
{
    
    //setAutoRepeat(1);
    setSemitone(semitone);
    init();
    connect(this, SIGNAL(pressed()), this, SLOT(sendNoteOn()));
    connect(this, SIGNAL(released()), this, SLOT(sendNoteOff()));
    qDebug() << "Created KeyButton at " << KeyButton::index;
    KeyButton::index++;
    
}

KeyButton::~KeyButton()
{
}

void KeyButton::init()
{
    btn_index = index;
    pos_x = KeyButton::position_x;
    int width, height;

    if (isSemitone()) {
        width = 20;
        height = 50;
        pos_x -= width/2;
        raise();
    } else {
        width = 30;
        height = 70;
        lower();
    }
    
    setGeometry(pos_x, 0, width, height);
    setAutoFillBackground("true");
    if (isSemitone())
        pos_x += width/2;
    else
        pos_x += width;
    KeyButton::position_x = pos_x;
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
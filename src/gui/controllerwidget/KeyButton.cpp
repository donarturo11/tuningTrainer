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
    setProperty("semitoneKey", semitone);
    connect(this, SIGNAL(pressed()), this, SLOT(sendNoteOn()));
    connect(this, SIGNAL(released()), this, SLOT(sendNoteOff()));
    qDebug() << "Created KeyButton at " << KeyButton::index;
    qDebug() << "KeyButton Geometry:  " << geometry();
    KeyButton::index++;
    
}

KeyButton::~KeyButton()
{
}

void KeyButton::init()
{
    btn_index = index;
    int pos_x = KeyButton::position_x;
    int width, height;

    if (isSemitone()) {
        width = 36;
        height = 80;
        pos_x -= width/2;
        raise();
    } else {
        width = 70;
        height = 140;
        lower();
    }
    this->pos_x = pos_x;
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
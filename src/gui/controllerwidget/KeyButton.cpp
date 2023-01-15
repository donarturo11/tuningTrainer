#include "gui/controllerwidget/KeyButton.h"
#include <iostream>
namespace GUI {

//KeyButton::index = 0;
/* --------------- */
KeyButton::KeyButton(QWidget *parent, bool semitone) : QPushButton(parent)
{
    
    //setAutoRepeat(1);
    setSemitone(semitone);
    init();
    fprintf(stderr, "\n\n==========================\n");
    fprintf(stderr, "-- Keybutton C-tor ------\n");
    fprintf(stderr, "-- Created Key number: %i\n", btn_index);
    fprintf(stderr, "-- Pos X: %i\n", pos_x);
    qDebug() << "Geometry: " << geometry();
    qDebug() << "Is semitone: " << isSemitone();
    fprintf(stderr, "\n==========================\n");
    connect(this, SIGNAL(pressed()), this, SLOT(sendNoteOn()));
    connect(this, SIGNAL(released()), this, SLOT(sendNoteOff()));
    
}

KeyButton::~KeyButton()
{
}

void KeyButton::init()
{
    btn_index = index;
    pos_x = KeyButton::position_x;
    int multi = isSemitone() ? 1 : 3;
    int width = 10*multi;
    int height = 20*multi;
    setGeometry(pos_x, 0, width, height);
    setAutoFillBackground("true");
    
    KeyButton::position_x += width;
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
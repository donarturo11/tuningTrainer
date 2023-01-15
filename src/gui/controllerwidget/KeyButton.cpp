#include "gui/controllerwidget/KeyButton.h"
#include "gui/load_style.h"
namespace GUI {

//KeyButton::index = 0;
/* --------------- */
KeyButton::KeyButton(QWidget *parent, bool semitone) : QPushButton(parent)
{
    
    setSemitone(semitone);
    init();
    connect(this, SIGNAL(pressed()), this, SLOT(sendNoteOn()));
    connect(this, SIGNAL(released()), this, SLOT(sendNoteOff()));
    fprintf(stderr, "-- Keybutton C-tor ------\n");
    fprintf(stderr, "-- Created Key number: %i\n", btn_index);
    fprintf(stderr, "-- Pos X: %i\n", pos_x);
    //qDebug() << "Geometry: " << this->geometry();
    fprintf(stderr, "---------------------\n\n");
    
}

KeyButton::~KeyButton()
{
}

void KeyButton::init()
{
    GUI::load_style(this, ":/qss/keyboard.qss");
    btn_index = index;
    pos_x = KeyButton::position_x;
    int multi = isSemitone() ? 1 : 3;
    int width = 20*multi;
    int height = 240/multi;
    setGeometry(pos_x, 0, width, height);
    
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
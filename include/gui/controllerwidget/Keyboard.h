#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <QWidget>
#include <QVector>
#include "gui/controllerwidget/KeyButton.h"

namespace GUI {

class Keyboard : public QWidget
{
Q_OBJECT
public:
    Keyboard(QWidget* parent=0);
    ~Keyboard();
    KeyButton* getKeyAt(int idx){ return _keys[idx]; };
    KeyButton* getKeyLast(){ return _keys.last(); };
    void initKey(bool semitone=false);
public slots:
    void sendNoteOn(int index);
    void sendNoteOff(int index);
    void setButtonPressed(int index);
    void setButtonReleased(int index);
signals:
    void noteOn(int index);
    void noteOff(int index);
private: 

protected:
    QVector<KeyButton*> _keys;


};

} // namespace GUI
#endif // KEYBOARD_H

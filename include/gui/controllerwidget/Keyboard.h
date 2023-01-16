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
    KeyButton* getKeyAt(int idx){ return keys[idx]; };
    void initKey(bool semitone=false);
public slots:
    void keyPressed(int index);    
    void keyReleased(int index);
signals:
    void noteOn(int index);
    void noteOff(int index);
private: 

protected:
    QVector<KeyButton*> keys;


};

} // namespace GUI
#endif // KEYBOARD_H

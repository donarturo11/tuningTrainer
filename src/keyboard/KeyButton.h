#ifndef KEYBUTTON_H
#define KEYBUTTON_H
#include <QPushButton>

class KeyButton : public QPushButton
{
Q_OBJECT
public:
    KeyButton(QWidget* parent);
    ~KeyButton();
protected:
    bool semitoneKey = false;

};

#endif // KEYBUTTON_H

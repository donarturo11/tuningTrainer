#ifndef KEYBUTTON_H
#define KEYBUTTON_H


class KeyButton : public QPushButton
{
Q_OBJECT
public:
    KeyButton(QWidget* parent);
    ~KeyButton();
protected:
    bool semitone = false;

};

#endif // KEYBUTTON_H

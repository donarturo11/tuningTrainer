#ifndef KEYBUTTON_H
#define KEYBUTTON_H
#include <QPushButton>

namespace GUI {

namespace ControllerWidget {

class KeyButton : public QPushButton
{
Q_OBJECT
public:
    KeyButton(QWidget* parent);
    ~KeyButton();
protected:
    bool semitoneKey = false;

};

} // namespace ControllerWidget

} // namespace GUI
#endif // KEYBUTTON_H

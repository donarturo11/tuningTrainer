#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <QWidget>

namespace GUI {

namespace ControllerWidget {

class Keyboard : public QWidget
{
Q_OBJECT
public:
    Keyboard(QWidget* parent);
    ~Keyboard();
protected:

};

} // namespace ControllerWidget

} // namespace GUI
#endif // KEYBOARD_H

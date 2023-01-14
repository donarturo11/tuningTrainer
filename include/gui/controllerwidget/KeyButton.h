#ifndef KEYBUTTON_H
#define KEYBUTTON_H
#include <QWidget>
#include <QPushButton>

namespace GUI {

class KeyButton : public QPushButton
{
Q_OBJECT
public:
    inline static int index = 0;
    KeyButton(QWidget* parent=0);
    ~KeyButton();
    void setSemitone(bool b){ semitoneKey = b; }
    void setIndex(int idx){ KeyButton::index=idx; }
    bool isSemitone(){ return semitoneKey; }
    int getIndex(){ return index; }
protected:
    bool semitoneKey = false;
};

} // namespace GUI
#endif // KEYBUTTON_H

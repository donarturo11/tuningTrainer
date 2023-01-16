#ifndef KEYBUTTON_H
#define KEYBUTTON_H
#include <QWidget>
#include <QPushButton>

namespace GUI {

class KeyButton : public QPushButton
{
Q_OBJECT
public:
    Q_PROPERTY(bool semitoneKey READ isSemitone)
    inline static int index = 0;
    inline static int position_x = 0;
    KeyButton(QWidget* parent=0, bool semitone=false);
    ~KeyButton();
    void init();
    void setIndex(int idx){ KeyButton::index=idx; }
    bool isSemitone(){ return semitoneKey; }
    int getIndex(){ return btn_index; }
    int getX(){ return pos_x; }
signals:
    void noteOn(int idx);
    void noteOff(int idx);
public slots:
    void sendNoteOn();
    void sendNoteOff(); 
private:
    void setSemitone(bool b){ semitoneKey = b; }
protected:
    bool semitoneKey = false;
    int btn_index;
    int pos_x;
};

} // namespace GUI
#endif // KEYBUTTON_H

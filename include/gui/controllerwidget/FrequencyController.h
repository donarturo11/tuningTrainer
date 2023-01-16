#ifndef FREQUENCYCONTROLLER_H
#define FREQUENCYCONTROLLER_H
#include <QWidget>
#include <QDial>
#include <QDoubleSpinBox>
#include <QVBoxLayout>

namespace GUI {

class FrequencyController : public QWidget
{
Q_OBJECT
public:
    inline static int index = 0;
    inline static int position_x = 0;
    FrequencyController(bool semitone = false, QWidget* parent=0);
    ~FrequencyController();
    void init();
signals:
    //frequencyChanged(double freq);
protected:
    int pos_x;
    QDial *m_dial;
    QDoubleSpinBox *m_spin;
    QVBoxLayout *m_layout;
    bool semitoneKey;
    

};

} // namespace GUI
#endif // FREQUENCYCONTROLLER_H

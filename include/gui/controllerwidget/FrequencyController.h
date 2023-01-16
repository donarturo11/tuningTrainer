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
    FrequencyController(bool semitone = false, QWidget* parent=0);
    ~FrequencyController();
    inline static int index = 0;
signals:
    //frequencyChanged(double freq);
protected:
    QDial *m_dial;
    QDoubleSpinBox *m_spin;
    QVBoxLayout *m_layout;
    bool semitoneKey;
    

};

} // namespace GUI
#endif // FREQUENCYCONTROLLER_H
